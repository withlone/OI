#include<cmath>
#include<cstdio>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )

static const int LEN = 1 << 15 ;
char buffer[LEN] , *S , *T ;

char Getchar(){
	if( S == T )T = ( S = buffer ) + fread( buffer , 1 , LEN , stdin ) ;
	return S == T ? EOF : *S++ ;
}

template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >
inline void swap( type &x , type &y ){ type t = x ; x = y ; y = t ; }
template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

typedef long long LL ;
static const int maxn = 4e4 + 10 ;
static const int maxm = 14e4 + 10 ;

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

int R[maxm] ;

complex a[maxm] ;
complex b[maxm] ;
complex c[maxm] ;

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
}

int main(){
	
	scanf( n ) ;
	For( i , 1 , n ){
		int x ;
		scanf( x ) ;
		a[x] = complex( 1.0 , 0.0 ) ;
		b[x << 1] = complex( 1.0 , 0.0 ) ;
		c[x * 3] = complex( 1.0 , 0.0 ) ;
		m = max( m , x * 3 ) ;
	}
	
	for( n = 1 ; n <= m ; n <<= 1 ) ++L ;
	For( i , 0 , n - 1 )R[i] = ( R[i >> 1] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
	
	FFT( a , 1 ) ; FFT( b , 1 ) ; FFT( c , 1 ) ;
	
	complex t1 = complex( 0.5 , 0.0 ) ;
	complex t2 = complex( 1.0 / 3.0 , 0.0 ) ;
	complex t3 = complex( 1.0 / 6.0 , 0.0 ) ;
	
	For( i , 0 , n )
		a[i] = a[i]
		+ t1 * ( a[i] * a[i] - a[i] * b[i] - b[i] )
		+ t2 * c[i]
		+ t3 * a[i] * a[i] * a[i] ;
	
	FFT( a , -1 ) ;
	
	For( i , 1 , m ){
		LL ans = (LL)( a[i].real / n + 0.5 ) ;
		if( ans )printf("%d %lld\n" , i , ans ) ;
	}
	
	return 0 ;
}
