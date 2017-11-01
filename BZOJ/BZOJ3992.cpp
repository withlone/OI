#include<cstdio>
#include<cstring>
#include<algorithm>

using std :: swap ;
using std :: reverse ;

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )

static const int len = 1 << 15 ;
char buffer[len] , *s_t , *t_s ;

char Getchar(){
	if( s_t == t_s )t_s = ( s_t = buffer ) + fread( buffer , 1 , len , stdin ) ;
	return s_t == t_s ? EOF : *s_t++ ;
}

template< typename type >
inline void scanf( type& in ){
	in = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

typedef long long LL ;
static const int maxn = 1e9 + 10 ;
static const int maxs = 8e4 + 10 ;
static const int maxm = ( 1 << 18 ) + 10 ;
static const int mod = 1004535809 ;

int n ;
int m ;
int N ;
int M ;
int L ;
int gm ;
int ls ;
int target ;

int R[maxm] ;
int a[maxm] ;
int b[maxm] ;
int RP[maxs] ;
int set[maxs] ;

inline int qpow( int x , int y , int p ){
	int res = 1 ;
	for( ; y ; y >>= 1 , x = 1LL * x * x % p )
		if( y & 1 )res = 1LL * res * x % p ;
	return res ;
}

inline int get_g( int x ){
	static int pr[maxs] ;
	int tp = 0 , t = x - 1 ;
	for( int i = 2 ; i * i <= t ; ++i )
		if( !( t % i ) ){
			while( !( t % i ) )t /= i ;
			pr[ ++tp ] = i ;
		}
	For( g , 2 , x ){
		bool f = true ;
		For( j , 1 , tp )
			if( qpow( g , ( x - 1 ) / pr[j] , x ) == 1 )
				{ f = false ; break ; }
		if( f )return g ;
	}
}

inline void get_RP(){
	int g = 1 ;
	For( i , 0 , M - 2 )
		RP[g] = i , g = 1LL * g * gm % M ;
}

inline void NTT( int *x , int f ){
	For( i , 0 , n - 1 )if( i < R[i] )swap( x[i] , x[R[i]] ) ;
	for( int i = 1 ; i < n ; i <<= 1 ){
		int gn = qpow( 3 , ( mod - 1 ) / ( i << 1 ) , mod ) ;
		for( int t = i << 1 , j = 0 ; j < n ; j += t ){
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
		int inv = qpow( n , mod - 2 , mod ) ;
		For( i , 0 , n - 1 )
			x[i] = 1LL * x[i] * inv % mod ;
	}
}

inline void mul( int *x , int *y ){
	static int z[maxm] ;
	memcpy( z , y , sizeof(int) * n ) ;
	NTT( x , 1 ) ; NTT( z , 1 ) ;
	For( i , 0 , n - 1 )x[i] = 1LL * x[i] * z[i] % mod ;
	NTT( x , -1 ) ;
	For( i , 0 , m - 1 )x[i] = ( x[i] + x[i + m] ) % mod , x[i + m] = 0 ;
}

int main(){
	
	scanf( N ) ; scanf( M ) ; scanf( target ) ; scanf( ls ) ;
	For( i , 1 , ls )scanf( set[i] ) ;
	
	gm = get_g( M ) ;
	
	get_RP() ;
	
	a[0] = 1 ;
	For( i , 1 , ls )if( set[i] )b[ RP[set[i]] ] = 1 ;
	
	for( m = M - 1 , n = 1 ; n <= ( m << 1 ) ; n <<= 1 ) ++L ;
	For( i , 0 , n - 1 )
		R[i] = ( R[i >> 1] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
	
	for( ; N ; N >>= 1 , mul( b , b ) )
		if( N & 1 )mul( a , b ) ;
	
	printf("%d\n" , a[RP[target]] ) ;
	
	return 0 ;
}
