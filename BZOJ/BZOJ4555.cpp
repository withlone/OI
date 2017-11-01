#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )

static const int maxn = 1e5 + 10 ;
static const int maxm = 3e5 + 10 ;
static const int mod = 998244353 ;

int n ;
int m ;
int L ;

int R[maxm] ;

int F[maxm] ;
int G[maxm] ;
int inv[maxm] ;
int mul[maxm] ;

int qpow( int x , int y ){
	int res = 1 ;
	for( ; y ; y >>= 1 , x = 1LL * x * x % mod )
		if( y & 1 )res = 1LL * res * x % mod ;
	return res ;
}

void NTT( int *x , int f ){
	For( i , 0 , n - 1 )if( i < R[i] )swap( x[i] , x[R[i]] ) ;
	for( int i = 1 ; i < n ; i <<= 1 ){
		int gn = qpow( 3 , ( mod - 1 ) / ( i << 1 ) ) ;
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
		For( i , 0 , m )
			x[i] = 1LL * x[i] * inv[n] % mod ;
	}
}

int main(){
	
	scanf( "%d" , &m ) ;
	
	for( n = 1 ; n <= ( m << 1 ) ; n <<= 1 ) ++L ;
	
	For( i , 0 , n - 1 )
		R[i] = ( R[i >> 1] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
	
	inv[1] = 1 ; mul[1] = 1 ;
	For( i , 2 , n )
		inv[i] = 1LL * ( mod - mod / i ) * inv[mod % i] % mod ,
		mul[i] = 1LL * mul[i - 1] * inv[i] % mod ;
	
	F[0] = 1 ;
	For( i , 1 , m )
		F[i] = ( ( i & 1 ? -1 : 1 ) * mul[i] + mod ) % mod ;
	G[0] = 1 ; G[1] = m + 1 ;
	For( i , 2 , m )
		G[i] = 1LL * inv[i - 1] * mul[i] % mod ,
		G[i] = 1LL * G[i] * ( qpow( i , m + 1 ) - 1 + mod ) % mod ;
	
	NTT( F , 1 ) ; NTT( G , 1 ) ;
	
	For( i , 0 , n )F[i] = 1LL * F[i] * G[i] % mod ;
	
	NTT( F , -1 ) ;
	
	int ans = F[0] , t = 1 ;
	For( i , 1 , m )
		t = 1LL * t * i * 2 % mod ,
		ans = ( 1LL * t * F[i] % mod + ans ) % mod ;
	
	printf("%d\n" , ans ) ;
	
	return 0 ;
}
