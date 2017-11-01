#include<set>
#include<cstdio>
#include<cstring>
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

template < typename type >
inline bool chkmax( type& x , const type& y ) {
	return x > y ? false : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x < y ? false : ( x = y , true ) ;
}
template < typename type >
inline void swap( type& x , type& y ) { type t = x ; x = y ; y = t ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 500 + 3 ;
static const int maxx = 25e4 + 7 ;
static const int maxm = maxx << 1 ;

int n ;
int m ;
int cnt ;

int hi[maxn][maxn] ;

bool V[maxx] ;

int user[maxx][2] ;

int num[maxn][maxn] ;

int left[maxx] ;
int right[maxx] ;
int f[maxn] ;

int Ct ;
int Ht[maxx] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins( int x , int y ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

void dfs( int x ) {
	V[x] = true ;
	REP( i , Ht[x] , Nt[i] ) {
		if( !V[to[i]] )dfs( to[i] ) ;
		chkmin( left[x] , left[to[i]] ) ;
		chkmax( right[x] , right[to[i]] ) ;
	}
	if( x > num[n - 1][m] )
		chkmin( left[x] , x - num[n - 1][m] ) ,
		chkmax( right[x] , x - num[n - 1][m] ) ;
}

inline bool chk() {
	int res = 0 ;
	FOR( i , 1 , m )
		if( !V[ num[n][i] ] )res++ ;
	return !res ? ( true ) : ( printf( "0\n%d\n" , res ) , false ) ;
}

int main() {
	
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n ) FOR( j , 1 , m )
		scanf( hi[i][j] ) , num[i][j] = ++cnt , left[cnt] = m + 1 ;
	
	For( i , 1 , n ) FOR( j , 1 , m ) {
		if( num[i - 1][j] && hi[i][j] > hi[i - 1][j] )
			ins( num[i][j] , num[i - 1][j] ) ;
		if( num[i + 1][j] && hi[i][j] > hi[i + 1][j] )
			ins( num[i][j] , num[i + 1][j] ) ;
		if( num[i][j - 1] && hi[i][j] > hi[i][j - 1] )
			ins( num[i][j] , num[i][j - 1] ) ;
		if( num[i][j + 1] && hi[i][j] > hi[i][j + 1] )
			ins( num[i][j] , num[i][j + 1] ) ;
	}
	
	FOR( i , 1 , m )
		dfs( i ) ;
	
	if( !chk() )return 0 ;
	
	memset( f , 0x3f , sizeof f ) ;
	f[0] = 0 ;
	
	For( i , 1 , m ) FOR( j , 1 , m )
		if( left[j] <= i && i <= right[j] )
			chkmin( f[i] , f[ left[j] - 1 ] + 1 ) ;
	
	printf( "1\n%d\n" , f[m] ) ;
	
	return 0 ;
}
