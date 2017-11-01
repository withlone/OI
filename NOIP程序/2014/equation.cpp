#include<cstdio>
#include<cstring>

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
inline type max( const type& x , const type& y ) { return x > y ? x : y ; }
template < typename type >
inline type min( const type& x , const type& y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , const type& y ) {
	return x >= y ? false : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x <= y ? false : ( x = y , true ) ;
}

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 103 ;
static const int maxm = 1e6 + 37 ;
static const int maxx = 1e4 + 37 ;
static const int mod[] = { 94421 , 97883 , 99149 , 99991 } ;

int n ;
int m ;

int ans[maxm] ;

int ai[5][maxn] ;

int V[5][maxm] ;

char number[maxx] ;

template < typename type >
inline type scanf( type& in , char *it , const int& x ) {
	in = 0 ; char ch = *it ; type f = 1 ;
	for( ;( ch> '9'||ch< '0' ) && *it ; ch = *++it )if( ch == '-' ) f = -1 ;
	for( ;( ch>='0'&&ch<='9' ) && *it ; ch = *++it )
		in = ( in * 10 + ch - '0' ) % mod[x] ;
	if( f < 0 )
		in = -in + mod[x] ;
	return in ;
}

inline int calc( int x , int y ) {
	int t = 1 , res = 0 ;
	FOR( i , 0 , n ) {
		res = ( res + 1LL * ai[y][i] * t % mod[y] ) % mod[y] ;
		t = 1LL * x * t % mod[y] ;
	}
	return res ;
}

inline bool chk( int y ) {
	FOR( i , 0 , 3 ) {
		int x = y % mod[i] ;
		if( !V[i][x] || calc( x , i ) ) return V[i][x] = false ;
		else V[i][x] = true ;
	}
	return true ;
}

int main() {
	
	freopen( "equation.in" , "r" , stdin ) ;
	freopen( "equation.out" , "w" , stdout ) ;
	
	memset( V , -1 , sizeof V ) ;
	
	scanf( n ) ; scanf( m ) ;
	For( i , 0 , n ) {
		scanf( "%s" , number ) ;
		FOR( j , 0 , 3 ) scanf( ai[j][i] , number , j ) ;	
	}
	
	FOR( i , 1 , m )
		if( chk( i ) ) ans[ ++ans[0] ] = i ;
	
	FOR( i , 0 , ans[0] ) printf( "%d\n" , ans[i] ) ;
	
	return 0 ;
}
