#include<cstdio>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

typedef long long LL ;
static const int maxn = 1e9 + 10 ;
static const int maxm = 1e5 + 10 ;

int inv[maxm] ;
int mul[maxm] ;
int muv[maxm] ;

void init( int p ){
	muv[0] = mul[0] = inv[0] = muv[1] = mul[1] = inv[1] = 1 ;
	For( i , 2 , p - 1 )
		inv[i] = 1LL * ( p - p / i ) * inv[p % i] % p ,
		muv[i] = 1LL * muv[i - 1] * inv[i] % p ,
		mul[i] = 1LL * mul[i - 1] * i % p ;
}

int C( int n , int m , int p ){
	if( n < m )return 0 ;
	return 1LL * mul[n] * muv[m] % p * muv[n - m] % p ;
}

int Lucas( int n , int m , int p ){
	if( n < m )return 0 ;
	if( n == m )return 1 ;
	return 1LL * Lucas( n / p , m / p , p ) * C( n % p , m % p , p ) % p ;
}

int n ;
int m ;
int p ;

int main(){
	
	freopen( "a.in" , "r" , stdin ) ;
	freopen( "a.out" , "w" , stdout ) ;
	
	scanf( "%d%d%d" , &n , &m , &p ) ;
	
	init( p ) ;
	
	printf("%d\n" , Lucas( n , m , p ) ) ;
	
	return 0 ;
}
