#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxx = 1e5 + 10 ;
static const int maxn = 3000 + 10 ;
static const int mod = 998244353 ;

int n ;
int m ;
int A ;
int cnt ;

int pr[maxx] ;
int ki[maxx] ;

int f[maxn] ;
int g[maxn] ;

inline void get_fac( int n ) {
	for( register int i = 2 ; i * i <= n ; ++i ) if( !( n % i ) ) {
		pr[ ++cnt ] = i ;
		while( !( n % i ) )n /= i , ++ki[cnt] ;
	}
	if( n != 1 )pr[ ++cnt ] = n , ki[cnt] = 1 ;
}

inline int qpow( int x , int y ) {
	int res = 1 ;
	for( ; y ; y >>= 1 , x = 1LL * x * x % mod )
		if( y & 1 )res = 1LL * res * x % mod ;
	return res ;
}

inline int get_dp( int w ) {
	memset( f , 0 , sizeof f ) ;
	memset( g , 0 , sizeof g ) ;
	For( i , 0 , w * m )g[i] = 1 ;
	For( i , 1 , m << 1 ) {
		For( j , 0 , w * m ) {
			f[j] = ( g[j] - ( j - w > 0 ? g[j - w - 1] : 0 ) + mod ) % mod ;
		}
		memcpy( g , f , sizeof g ) ;
		For( j , 0 , w * m )g[j] = ( g[j] + g[j - 1] ) % mod ;
	}
	return f[w * m] ;
}

inline int get_num( int n ) {
	int res = 0 ;
	for( int i = 1 ; i * i <= n ; ++i )
		if( !( n % i ) )res = ( res + 1 + ( i * i != n ) ) ;
	return res ;
}

int main() {
	
	freopen( "count.in" , "r" , stdin ) ;
	freopen( "count.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ;
	
	get_fac( n ) ;
	
	A = 1 ;
	For( i , 1 , cnt )
		A = 1LL * A * get_dp( ki[i] ) % mod ;
	
	int ans = qpow( get_num( n ) , m << 1 ) ;
	
	ans = 1LL * ( ( ans - A + mod ) % mod ) * qpow( 2 , mod - 2 ) % mod ;
	ans += A ;
	
	printf("%d\n" , ans % mod ) ;
	
	return 0 ;
}
