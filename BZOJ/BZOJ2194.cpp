#include<cmath>
#include<cstdio>

using namespace std ;

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; i-- )

template< typename type >
inline void swap( type &x , type &y ){ type t = x ; x = y ; y = t ; }

static const int LEN = 1 << 15 ;
char buffer[LEN] , *S , *T ;

char Getchar(){
	if( S == T )T = ( S = buffer ) + fread( buffer , 1 , LEN , stdin ) ;
	return S == T ? EOF : *S++ ;
}

template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

static const int maxn = 3e5 + 10 ;

namespace my_fft{
	
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
		for( m += n , n = 1 ; n <= m ; n <<= 1 ) ++L ;
		For( i , 0 , n - 1 )
			R[i] = ( R[i >> 1] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
		FFT( a , 1 ) ; FFT( b , 1 ) ;
		For( i , 0 , n - 1 )a[i] = a[i] * b[i] ;
		FFT( a , -1 ) ;
	}
	
	inline void main( int n , int *x , int m , int *y , int *res ){
		my_fft :: n = n ;
		my_fft :: m = m ;
		For( i , 0 , n )a[i] = complex( x[i] * 1.0 , 0 ) ;
		For( i , 0 , m )b[i] = complex( y[i] * 1.0 , 0 ) ;
		run() ;
		For( i , 0 , my_fft :: m )
			res[i] = (int)( a[i].real / my_fft :: n + 0.5 ) ;
	}
	
}

int n ;

int a[maxn] ;
int b[maxn] ;
int c[maxn] ;

int main(){
	
	scanf( n ) ; --n ;
	For( i , 0 , n )scanf( a[n - i] ) , scanf( b[i] ) ;
	
	my_fft :: main( n , a , n , b , c ) ;
	
	Lop( i , n , 0 )
		printf("%d\n" , c[i] ) ;
	return 0 ;
}
