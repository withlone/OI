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

typedef long long LL ;
static const int mod = 20170927 ;
static const int maxn = 1e6 + 37 ;
static const int maxm = 4e6 + 37 ;

int n ;
int m ;

int xi[maxn] ;
int yi[maxn] ;

int sum1[maxn] ;
int sum2[maxn] ;
int sum3[maxn] ;

inline int sqr( int x ) {
	return 1LL * x * x % mod ;
}

inline int add( int x , int y ) {
	x += y ; if( x >= mod ) x -= mod ; return x ;
}

inline int dda( int x , int y ) {
	x -= y ; if( x < 0 ) x += mod ; return x ;
}

inline int lowbit( int x ) { return x & -x ; }

inline void modify( int x , int a , int b , int c ) {
	for( ; x <= n ; x += lowbit( x ) )
		sum1[x] = add( sum1[x] , a ) ,
		sum2[x] = add( sum2[x] , b ) ,
		sum3[x] = add( sum3[x] , c ) ;
}

inline int query( int l , int r ) {
	int tot1 = 0 , tot2 = 0 , tot3 = 0 ;
	for( ; r ; r -= lowbit( r ) )
		tot1 = add( tot1 , sum1[r] ) ,
		tot2 = add( tot2 , sum2[r] ) ,
		tot3 = add( tot3 , sum3[r] ) ;
	--l ;
	for( ; l ; l -= lowbit( l ) )
		tot1 = dda( tot1 , sum1[l] ) ,
		tot2 = dda( tot2 , sum2[l] ) ,
		tot3 = dda( tot3 , sum3[l] ) ;
	return dda( 1LL * tot1 * tot2 % mod , sqr( tot3 ) ) ;
}

int main() {
	
	freopen( "kurisu.in" , "r" , stdin ) ;
	freopen( "kurisu.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ;
	FOR( i , 1 , n ) {
		scanf( xi[i] ) , scanf( yi[i] ) ;
		int a = 1LL * xi[i] * xi[i] % mod ;
		int b = 1LL * yi[i] * yi[i] % mod ;
		int c = 1LL * xi[i] * yi[i] % mod ;
		modify( i , a , b , c ) ;
	}
	
	while( m-- ) {
		int op , x , y , z ;
		scanf( op ) ;
		if( op == 1 ) {
			scanf( z ) ; scanf( x ) ; scanf( y ) ;
			int a = 1LL * xi[z] * xi[z] % mod ;
			int b = 1LL * yi[z] * yi[z] % mod ;
			int c = 1LL * xi[z] * yi[z] % mod ;
			a = dda( -a , 0 ) ; b = dda( -b , 0 ) ; c = dda( -c , 0 ) ;
			modify( z , a , b , c ) ;
			a = 1LL * x * x % mod ;
			b = 1LL * y * y % mod ;
			c = 1LL * x * y % mod ;
			modify( z , a , b , c ) ;
			xi[z] = x ; yi[z] = y ;
		} else scanf( x ) , scanf( y ) , printf( "%d\n" , query( x , y ) ) ;
	}
	
	return 0 ;
}
