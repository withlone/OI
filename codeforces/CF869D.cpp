#include<set>
#include<map>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )
#define FOR( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define LOP( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define REP( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename tp >
inline bool chkmax( tp& x , const tp& y ) {
	return ( x >= y ) ? false : ( x = y , true ) ;
}
template < typename tp >
inline bool chkmin( tp& x , const tp& y ) {
	return ( x <= y ) ? false : ( x = y , true ) ;
}

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 511 ;
static const int maxm = 5e5 + 11 ;
static const int mod = 1e9 + 7 ;

int n ;
int m ;
int cnt ;
int tot ;
int ans ;

int ai[7] ;
int bi[7] ;

bool V[maxn] ;

int size[maxn] ;

set < int > point ;
map < int , int > ider ;

set < int > :: iterator it ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins( int x , int y ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

inline int add( int x , int y ) {
	x += y ; if( x >= mod ) x -= mod ; return x ;
}

inline int mul( int x , int y ) {
	return 1LL * x * y % mod ;
}

inline void get_point( int x ) {
	for( ; x != 1 ; x >>= 1 )
		point.insert( x ) ;
}

inline int get_size( int x ) {
	int res = 0 , l = x , r = x ;
	for( ; l <= n ; l <<= 1 , r = r << 1 | 1 )
		res += min( r , n ) - l + 1 ;
	return res ;
}

void dfs( int x ) {
	V[x] = true ;
	tot = add( tot , size[x] ) ;
	REP( i , Ht[x] , Nt[i] )
		if( !V[to[i]] ) dfs( to[i] ) ;
	V[x] = false ;
}

int main() {
	
	point.insert( 1 ) ;
	scanf( n ) ; scanf( m ) ;
	FOR( i , 1 , m )
		get_point( scanf( ai[i] ) ) , get_point( scanf( bi[i] ) ) ;
	
	for( it = point.begin() ; it != point.end() ; it++ )
		ider[ *it ] = ++cnt ;
	
	set < int > :: iterator t1 , t2 ;
	for( it = point.begin() ; it != point.end() ; it++ ) {
		t1 = point.find( *it << 1 ) ; t2 = point.find( *it << 1 | 1 ) ;
		if( t1 == point.end() && t2 == point.end() )
			size[ ider[ *it ] ] = get_size( *it ) ;
		else if( t1 == point.end() )
			size[ ider[ *it ] ] = get_size( *it << 1 ) + 1 ;
		else if( t2 == point.end() )
			size[ ider[ *it ] ] = get_size( *it << 1 | 1 ) + 1 ;
		else
			size[ ider[ *it ] ] = 1 ;
	}
	
	for( it = point.begin() ; it!= point.end() ; it++ ) {
		if( point.find( *it << 1 ) != point.end() )
			ins( ider[ *it ] , ider[ *it << 1 ] ) ;
		if( point.find( *it << 1 | 1 ) != point.end() )
			ins( ider[ *it ] , ider[ *it << 1 | 1 ] ) ;
		if( point.find( *it >> 1 ) != point.end() )
			ins( ider[ *it ] , ider[ *it >> 1 ] ) ;
	}
	
	FOR( i , 1 , m )
		ins( ider[ ai[i] ] , ider[ bi[i] ] ) ,
		ins( ider[ bi[i] ] , ider[ ai[i] ] ) ;
	
	FOR( i , 1 , cnt )
		tot = 0 , dfs( i ) , ans = add( ans , mul( tot , size[i] ) ) ;
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
