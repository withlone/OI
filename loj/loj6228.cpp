#include<cmath>
#include<cstdio>
#include<algorithm>

using std :: swap ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )

static const int LEN = 1 << 15 ;
char buffer[LEN] , *S_T , *T_S ;

char Getchar(){
	if( S_T == T_S )
		T_S = ( S_T = buffer ) + fread( buffer , 1 , LEN , stdin ) ;
	return S_T == T_S ? EOF : *S_T++ ;
}

template< typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }

template< typename type >
inline type scanf( type &In ){
	In = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )In = In * 10 + ch - '0' ;
	return In *= f ;
}

typedef long long LL ;
static const int maxn = 1e5 + 10 ;
static const int maxm = ( 1 << 18 ) + 10 ;

int n ;
int N ;
int m ;
int L ;

int R[maxm] ;
int ai[maxn] ;
int cnt[maxn] ;

LL f[maxn] ;
LL g[maxn] ;

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

complex a[maxm] ;

#define pi acos( -1 )

void FFT( complex *x , int f ){
	For( i , 0 , n - 1 )if( i < R[i] )swap( x[i] , x[R[i]] ) ;
	for( int i = 1 ; i < n ; i <<= 1 ){
		complex wn = complex( cos( pi / i ) , f * sin( pi / i ) ) ;
		for( int t = i << 1 , j = 0 ; j < n ; j += t ){
			complex w = complex( 1.0 , 0.0 ) ;
			for( int k = 0 ; k < i ; ++k , w = w * wn ){
				complex p = x[j + k] , q = w * x[i + j + k];
				x[j + k] = p + q ; x[i + j + k] = p - q ;
			}
		}
	}
	if( f == -1 )
		For( i , 0 , n - 1 )x[i].real /= n ;
}

int main(){
	
	N = scanf( n ) ;
	For( i , 1 , n )
		scanf( ai[i] ) , ++cnt[ ai[i] ] , chkmax( m , ai[i] ) ;
	
	Lop( i , m , 1 )
		a[i] = complex( cnt[i] , 0.0 ) , g[i] = g[i + 1] + cnt[i] ;
	
	for( n = 1 ; n <= ( m << 1 ) ; n <<= 1 ) ++L ;
	For( i , 0 , n - 1 )
		R[i] = ( R[i >> 1] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
	FFT( a , 1 ) ;
	For( i , 0 , n - 1 )a[i] = a[i] * a[i] ;
	FFT( a , -1 ) ;
	
	For( i , 1 , m ){
		f[i] = (LL)( a[i].real + 0.5 ) ;
		if( !( i & 1 ) )f[i] -= cnt[i >> 1] ;
		f[i] >>= 1 ;
	}
	
	LL ans , tot ;
	ans = tot = 1LL * N * ( N - 1 ) * ( N - 2 ) / 6 ;
	
	For( i , 1 , m )
		ans -= f[i] * g[i] ;
	
	printf("%.6lf\n" , 1.0 * ans / tot ) ;
	
	return 0 ;
}
