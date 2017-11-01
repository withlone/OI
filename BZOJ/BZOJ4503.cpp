#include<cmath>
#include<cstdio>
#include<cstring>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; i-- )

template< typename type >
inline void swap( type &x , type &y ){ type t = x ; x = y ; y = t ; }

static const int maxn = 1e5 + 10 ;
static const int maxm = 3e5 + 10 ;

char S[maxn] ;
char T[maxn] ;

int n ;
int m ;
int L ;
int ns ;
int nt ;

int R[maxm] ;
int ans[maxm] ;

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

complex S1[maxm] ;
complex S2[maxm] ;
complex T1[maxm] ;
complex T2[maxm] ;
complex T3[maxm] ;
complex out[maxm] ;
complex base[maxm] ;

void FFT( complex *x , int f ){
	For( i , 0 , n - 1 )if( i < R[i] )swap( x[i] , x[R[i]] ) ;
	for( int i = 1 ; i < n ; i <<= 1 ){
		complex wn = complex( cos( pi / i ) , f * sin( pi / i ) ) ;
		for( int t = i << 1 , j = 0 ; j < n ; j += t ){
			complex w = complex( 1.0 , 0.0 );
			for( int k = 0 ; k < i ; ++k , w = w * wn ){
				complex p = x[j + k] , q = w * x[i + j + k] ;
				x[j + k] = p + q ; x[i + j + k] = p - q ;
			}
		}
	}
}

int Get( char ch ){ return ch == '?' ? 0 : ch - 'a' + 1 ; }

int main(){
	
	scanf( "%s%s" , S , T ) ;
	
	ns = strlen( S ) ; nt = strlen( T ) ;
	
	For( i , 0 , nt - 1 >> 1 )swap( T[i] , T[nt - i - 1] ) ;
	
	int t ;
	
	For( i , 0 , ns - 1 )
		t = Get( S[i] ) ,
		S1[i] = 2 * t ,
		S2[i] = t * t ;
	
	For( i , 0 , nt - 1 )
		t = Get( T[i] ) ,
		T1[i] = t ,
		T2[i] = t * t ,
		T3[i] = t * t * t ;
	
	for( m = ns + nt , n = 1 ; n <= m ; n <<= 1 ) ++L ;
	
	For( i , 0 , n - 1 )
		base[i] = complex( 1.0 , 0.0 ) ,
		R[i] = ( R[i >> 1] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
	
	FFT( S1 , 1 ) ; FFT( S2 , 1 ) ; FFT( base , 1 ) ;
	FFT( T1 , 1 ) ; FFT( T2 , 1 ) ; FFT( T3 , 1 ) ;
	
	For( i , 0 , n - 1 )
		out[i] = T3[i] * base[i] - S1[i] * T2[i] + S2[i] * T1[i] ;
	
	FFT( out , -1 ) ;
	
	For( i , 0 , ns - nt )
		if( !( (int)( ( out[i + nt - 1].real + 0.5 ) / n ) ) )
			ans[ ++ans[0] ] = i ;
	
	printf("%d\n" , ans[0] ) ;
	For( i , 1 , ans[0] )printf("%d\n" , ans[i] ) ;
	
	return 0 ;
}
