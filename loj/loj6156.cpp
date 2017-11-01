#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>

using std :: swap ;

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )

static const int len = 1 << 15 ;
char buffer[len] , *s_t , *t_s ;

char Getchar(){
	if( s_t == t_s )
		t_s = ( s_t = buffer ) + fread( buffer , 1 , len , stdin ) ;
	return s_t == t_s ? EOF : *s_t++ ;
}

template< typename type >
inline type scanf( type& in ){
	in = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )in = in * 10 + ch - '0' ; in *= f ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 6e4 + 10 ;
static const int maxm = ( 1 << 17 ) + 10 ;

int cases ;
int N ;
int M ;
int n ;
int m ;
int L ;
int gm ;

int a[maxn] ;
int R[maxm] ;
int RP[maxn];
LL ans[maxn] ;
int mine[maxn] ;

int qpow( int x , int y , int mod ){
	int res = 1 ;
	for( ; y ; y >>= 1 , x = 1LL * x * x % mod )
		if( y & 1 )res = 1LL * res * x % mod ;
	return res ;
}

int get_g( int x ){
	static int pr[maxn] ;
	int tp = 0 , t = x - 1 ;
	for( register int i = 2 ; i * i <= t ; ++i )	
		if( !( t % i ) ){
			while( !( t % i ) )t /= i;
			pr[ ++tp ] = i ;
		}
	if( t != 1 )pr[ ++tp ] = t ;
	For( i , 2 , x ){
		bool f = true ;
		For( j , 1 , tp )
			if( qpow( i , ( x - 1 ) / pr[j] , x ) == 1 )
				{ f = false ; break ; }
		if( f )return i ;
	}
}

class complex{
	public :
		double real ;
		double image ;
		
		complex(){ real = image = 0.0 ; }
		complex( double a , double b ){ real = a ; image = b ; }
		
		complex operator + ( const complex& x ){
			return complex( real + x.real , image + x.image ) ;
		}
		complex operator - ( const complex& x ){
			return complex( real - x.real , image - x.image ) ;
		}
		complex operator * ( const complex& x ){
			complex res ;
			res.real = real * x.real - image * x.image ;
			res.image = real * x.image + image * x.real ;
			return res ;
		}
};

complex A[maxm] ;
complex B[maxm] ;

#define pi acos( -1 )

void FFT( complex *x , int f ){
	For( i , 0 , n - 1 )if( i < R[i] )swap( x[i] , x[R[i]] ) ;
	for( int i = 1 ; i < n ; i <<= 1 ){
		complex wn = complex( cos( pi / i ) , f * sin( pi / i ) ) ;
		for( int t = i << 1 , j = 0 ; j < n ; j += t ){
			complex w = complex( 1.0 , 0.0 ) ;
			for( int k = 0 ; k < i ; ++k , w = w * wn ){
				complex p = x[j + k] , q = w * x[i + j + k] ;
				x[j + k] = p + q ; x[i + j + k] = p - q ;
			}
		}
	}
	if( f == -1 )
		For( i , 0 , n - 1 )x[i].real /= n ;
}

int main(){
	
	scanf( cases ) ;
	
	while( cases-- ){
		L = 0 ;
		For( i , 0 , maxm - 1 )A[i] = B[i] = complex() ;
		N = scanf( n ) ; M = scanf( m ) ;
		gm = get_g( m ) ;
		int g = 1 , cnt = 0 ;
		For( i , 0 , m - 2 )
			RP[g] = i , mine[i] = g , g = 1LL * g * gm % m ;
		For( i , 1 , n ){
			scanf( a[i] ) , a[i] %= m ;
			if( !a[i] ){ ++cnt ; continue ; }
			A[ RP[a[i]] ] = A[ RP[a[i]] ] + complex( 1.0 , 0.0 ) ;
			B[ RP[a[i]] << 1 ] = B[ RP[a[i]] << 1 ] + complex( 1.0 , 0.0 ) ;
		}
		for( m = m - 1 << 1 , n = 1 ; n <= m ; n <<= 1 ) ++L ;
		memset( R , 0 , sizeof(int) * n ) ;
		For( i , 0 , n - 1 )
			R[i] = ( R[i >> 1] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
		FFT( A , 1 ) ; FFT( B , 1 ) ;
		For( i , 0 , n - 1 )
			A[i] = A[i] * A[i] - B[i] * complex( 1.0 , 0.0 ) ;
		FFT( A , -1 ) ;
		For( i , 0 , M - 2 )
			ans[mine[i]] = 
			(LL)(A[i].real + 0.5) + (LL)(A[ i + M - 1 ].real + 0.5) >> 1 ;
		ans[0] = 1LL * cnt * ( N - cnt ) + 1LL * ( cnt - 1 ) * cnt / 2 ;
		For( i , 0 , M - 1 )
			printf("%lld\n" , ans[i] ) ;
	}
	
	return 0 ;
}
