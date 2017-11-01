#include<cstdio>
#include<algorithm>

using std :: reverse ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

static const int len = 1 << 15 ;
char buffer[len] , *h_t , *t_h ;

char Getchar(){
	if( h_t == t_h )t_h = ( h_t = buffer ) + fread( buffer , 1 , len , stdin ) ;
	return h_t == t_h ? EOF : *h_t++ ;
}

template< typename type >
inline void chkmin( type& x , type y ){ x < y ? x : x = y ; }
template< typename type >
inline void chkmax( type& x , type y ){ x > y ? x : x = y ; }
template< typename type >
inline void swap( type& x , type& y ){ type t = x ; x = y ; y = t ; }

template< typename type >
inline void scanf( type& in ){
	in = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' ) f = - 1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

typedef long long LL ;
static const int maxn = 5e4 + 10 ;
static const int maxm = 1 << 18 ;
static const int inf = ~0U >> 1 ;
static const int mod = 998244353 ;

int n ;
int m ;
int L ;
int ans ;
int tot ;

int R[maxm] ;
int a[maxm] ;
int b[maxm] ;

int qpow( int x , int y ) {
	int res = 1 ;
	for( ; y ; y >>= 1 , x = 1LL * x * x % mod )
		if( y & 1 )res = 1LL * res * x % mod ;
	return res ;
}

void NTT( int *x , int f ) {
	For( i , 0 , n - 1 )if( i < R[i] )swap( x[i] , x[R[i]] ) ;
	for( int i = 1 ; i < n ; i <<= 1 ) {
		int gn = qpow( 3 , ( mod - 1 ) / ( i << 1 ) ) ;
		for( int t = i << 1 , j = 0 ; j < n ; j += t ) {
			int g = 1 ;
			for( int k = 0 ; k < i ; ++k , g = 1LL * g * gn % mod ){
				int p = x[j + k] , q = 1LL * g * x[i + j + k] % mod ;
				x[j + k] = ( p + q ) % mod ;
				x[i + j + k] = ( p - q + mod ) % mod ;
			}
		}
	}
	if( f == -1 ){
		reverse( 1 + x , n + x ) ;
		int inv = qpow( n , mod - 2 ) ;
		For( i , 0 , n - 1 )
			x[i] = 1LL * x[i] * inv % mod ;
	}
}

int main() {
	
	scanf( n ) ; scanf( m ) ;
	
	For( i , 0 , n - 1 ) {
		scanf( a[i] ) ;
		ans += a[i] * a[i] ;
		tot += a[i] ;
	}
	
	Lop( i , n - 1 , 0 ) {
		scanf( b[i] ) ;
		ans += b[i] * b[i] ;
		tot -= b[i] ;
	}
	
	tot <<= 1 ;
	int mn = inf ;
	For( t , -m , m )
		chkmin( mn , n * t * t + t * tot ) ;
	
	ans += mn ;
	
	for( m = n , n = 1 ; n <= ( m << 1 ) ; n <<= 1 ) ++L ;
	For( i , 0 , n - 1 )R[i] = ( R[i >> 1] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
	
	NTT( a , 1 ) ; NTT( b , 1 ) ;
	For( i , 0 , n - 1 )a[i] = 1LL * a[i] * b[i] % mod ;
	NTT( a , -1 ) ;
	
	int mx = 0 ;
	For( i , 0 , m - 1 )
		chkmax( mx , ( a[i] + a[i + m] ) % mod ) ;
	
	printf("%d\n" , ans - ( mx << 1 ) ) ;
	
	return 0 ;
}
