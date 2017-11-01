#include<cstdio>

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
	return ( x >= y ) ? ( false ) : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return ( x <= y ) ? ( false ) : ( x = y , true ) ;
}

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int mod = 998244353 ;
static const int maxn = 3e3 + 11 ;

int n ;
int m ;

int li[maxn] ;
int ri[maxn] ;
int le[maxn] ;
int re[maxn] ;

int mul[maxn] ;
int inv[maxn] ;

int f[maxn][maxn] ;

inline void init() {
	mul[0] = 1 ;
	FOR( i , 1 , 3e3 )
		mul[i] = 1LL * mul[i - 1] * i % mod ;
	inv[0] = inv[1] = 1 ;
	FOR( i , 2 , 3e3 )
		inv[i] = 1LL * ( mod - mod / i ) * inv[ mod % i ] % mod ;
	FOR( i , 1 , 3e3 )
		inv[i] = 1LL * inv[i] * inv[i - 1] % mod ;
}

inline int A( int n , int m ) {
	return 1LL * mul[n] * inv[n - m] % mod ;
}

int main() {
	
	freopen( "matrix.in" , "r" , stdin ) ;
	freopen( "matrix.out" , "w" , stdout ) ;
	
	init() ;
	
	scanf( n ) ; scanf( m ) ;
	
	FOR( i , 1 , n )
		++le[ scanf( li[i] ) ] , ++re[ scanf( ri[i] ) ] ;
	
	FOR( i , 1 , m )
		le[i] += le[i - 1] , re[i] += re[i - 1] ;
	
	f[0][0] = 1 ;
	For( i , 1 , m ) {
		f[i][0] =
			1LL * f[i - 1][0] * A( i - le[i - 1] , le[i] - le[i - 1]  ) % mod ;
		FOR( j , 1 , min( n , i - le[i] ) )
			f[i][j] = 
			1LL * ( 1LL * f[i - 1][j - 1] * ( re[i] - j + 1 ) % mod +
			f[i - 1][j] ) * A( i - j - le[i - 1] , le[i] - le[i - 1] ) % mod ;
	}
	printf( "%d\n" , f[m][n] ) ;
	
	return 0 ;
}
