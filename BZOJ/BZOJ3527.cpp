#include<cmath>
#include<cstdio>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )

static const int LEN = 1 << 15 ;
char buffer[LEN] , *S , *T ;

template< typename type >
inline void swap( type &x , type &y ){ type t = x ; x = y ; y = t ; }

static const int maxn = 3e5 + 10 ;

namespace fft{
	
	class complex{
		public :
			double real ;
			double image ;
			
			complex(){ real = image = 0 ; }
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
	
	#define pi acos( -1 )
	
	int n ;
	int m ;
	int L ;
	
	int R[maxn] ;
	
	complex a[maxn] ;
	complex b[maxn] ;
	
	inline void FFT( complex *x , int f ){
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
	}
	
	inline void run(){
		for( m += n , n = 1 , L = 0 ; n <= m ; n <<= 1 ) ++L ;
		For( i , 0 , n - 1 )
			R[i] = ( R[i >> 1] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
		FFT( a , 1 ) ; FFT( b , 1 ) ;
		For( i , 0 , n )a[i] = a[i] * b[i] ;
		FFT( a , -1 ) ;
	}
	
	inline void main( int n , double *x , int m , double *y , double *z ){
		For( i , 0 , fft :: n )a[i] = b[i] = complex() , R[i] = 0 ;
		fft :: n = n ;
		fft :: m = m ;
		For( i , 0 , n )a[i] = complex( x[i] , 0.0 ) ;
		For( i , 0 , m )b[i] = complex( y[i] , 0.0 ) ;
		run() ;
		For( i , 0 , fft :: m )
			z[i] = a[i].real / fft :: n ;
	}
}

int n ;

double q[maxn] ;
double g[maxn] ;
double H1[maxn] ;
double H2[maxn] ;

int main(){
	
	scanf( "%d" , &n ) ; --n ;
	For( i , 0 , n )scanf( "%lf" , &q[i] ) ;
	
	For( i , 1 , n )g[i] = 1.0 / ( 1.0 * i * i ) ;
	
	fft :: main( n , q , n , g , H1 ) ;
	
	For( i , 0 , n >> 1 )swap( q[i] , q[n - i] ) ;
	
	fft :: main( n , q , n , g , H2 ) ;
	
	For( i , 0 , n )
		printf("%.3lf\n" , H1[i] - H2[n - i] ) ;
	
	return 0 ;
}
