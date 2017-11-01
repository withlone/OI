#include<cstdio>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; i-- )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template< typename type >inline void scanf( type &in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ; ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ; ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

typedef long long LL ;
static const int maxn = 1e5 + 10 ;
static const int maxm = maxn << 1 ;
static const int mod = 1e9 + 7 ;

int n ;
int T ;
int w ;

struct status_start{
	int x ;
	int c ;
	bool operator < ( const status_start &t ) const
		{ return x < t.x ; }
}st[maxn] ;

int inv[maxm] ;

LL C[maxm] ;

void debug_inv() ;

void read_in(){
	scanf( n ) ; scanf( T ) ; scanf( w ) ;
	For( i , 1 , n )
		scanf( st[i].x ) , scanf( st[i].c ) ;
}

void get_inv(){
	inv[1] = 1 ;
	For( i , 2 , T << 1 )
		inv[i] = ( - 1LL * ( mod / i ) * inv[ mod % i ] % mod + mod ) % mod ;
}

void preparation(){
	sort( 1 + st , 1 + n + st ) ;
	C[0] = 1 ;
	C[1] = T ;
	For( i , 2 , T )
		C[i] = C[i - 1] * inv[i] % mod * ( T - i + 1 ) % mod ;
}

void run(){
	LL ans = 0 , calc = 1 ;
	int pos = 1 ;
	For( i , w - T , w + T ){
		LL t = 0 ;
		while( st[pos].x < i && pos <= n )++pos ;
		while( st[pos].x == i && pos <= n )t += st[pos++].c ;
		t %= mod ;
		int j = i - ( w - T ) >> 1 ;
		ans = ( ans + t * C[j] % mod ) % mod ;
		++i ;
	}
	printf("%lld\n" , ans ) ;
}

int main(){
	
	freopen("split.in" , "r" , stdin) ;
	freopen("split.out" , "w" , stdout) ;
	
	read_in() ;
	
	get_inv() ;
	
	preparation() ;
	
	run() ;
	
	return 0 ;
}
