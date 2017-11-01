#include<cmath>
#include<cstdio>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )

template< typename type >
inline void swap( type &x , type &y ){ type t = x ; x = y ; y = t ; }

static const int maxn = 3e5 + 10 ;
static const int maxm = 11e5 + 10 ;

int n ;
int m ;
int L ;
int An ;
int Bn ;

int R[maxm] ;

int ans[maxn] ;

char A[maxn] ;
char B[maxn] ;

int Get( char ch ){ return ch == '*' ? 0 : ch - 'a' + 1 ; }

#define pi acos( -1 )

class complex{
	public :
		double real ;
		double image ;
		
		complex(){ real = image = 0.0 ; }
		complex( int a ){ real = 1.0 * a ; image = 0.0 ; }
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

complex A1[maxm] ;
complex A2[maxm] ;
complex A3[maxm] ;
complex B1[maxm] ;
complex B2[maxm] ;
complex B3[maxm] ;
complex out[maxm] ;

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
	
	scanf( "%d%d" , &An , &Bn ) ;
	
	scanf( "%s%s" , A , B ) ;
	
	For( i , 0 , An - 1 >> 1 )swap( A[i] , A[An - i - 1] ) ;
	
	int t ;
	For( i , 0 , An - 1 )
		t = Get( A[i] ) ,
		A1[i] = t ,
		A2[i] = t * t ,
		A3[i] = t * t * t ;
	For( i , 0 , Bn - 1 )
		t = Get( B[i] ) ,
		B1[i] = t ,
		B2[i] = t * t << 1 ,
		B3[i] = t * t * t ;
	
	for( m = An + Bn , n = 1 ; n <= m ; n <<= 1 ) ++L ;
	For( i , 0 , n - 1 )
		R[i] = ( R[i >> 1] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
	
	FFT( A1 , 1 ) ; FFT( A2 , 1 ) ; FFT( A3 , 1 ) ;
	FFT( B1 , 1 ) ; FFT( B2 , 1 ) ; FFT( B3 , 1 ) ;
	
	For( i , 0 , n - 1 )
		out[i] = ( A3[i] * B1[i] ) - ( A2[i] * B2[i] ) + ( A1[i] * B3[i] ) ;
	
	FFT( out , -1 ) ;
	
	For( i , 0 , Bn - An )
		if( !( (int)( ( out[i + An - 1].real + 0.5 ) / n ) ) )
			ans[ ++ans[0] ] = i + 1 ;
	
	printf("%d\n" , ans[0] ) ;
	
	For( i , 1 , ans[0] )printf("%d%c" , ans[i] , ans[0] == i ? '\n' : ' ' ) ;
	
	return 0 ;
}
