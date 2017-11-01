#include<cstdio>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )

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

static const int maxn = 1e3 + 10 ;
static const int maxm = 1e4 + 10 ;
static const int mod = 1e9 + 7 ;

bool V[maxm] ;

int cnt , i , j , q , m , a , k , pri[maxn] , C[maxn * 3][maxn * 3] ;

void init(){
	for( i = 2 ; i <= maxm ; ++i ){
		if( !V[i] )pri[ ++cnt ] = i ;
		if( cnt == 1000 )break ;
		for( j = 1 ; pri[j] * i <= maxm && j <= cnt ; ++j ){
			V[ pri[j] * i ] = true ;
			if( !( i % pri[j] ) )break ;
		}
	}
	for( i = 0 ; i <= 3000 ; ++i )C[i][0] = 1 ;
	for( i = 1 ; i <= 3000 ; ++i )for( j = 1 ; j <= i ; ++j )
		C[i][j] = ( C[i - 1][j] + C[i - 1][j - 1] ) % mod ;
}

void solve(){
	int ans = 1 , t = a ;
	--k ;
	for( i = 1 ; i <= m ; ++i ){
		int last = ans , phi = pri[i] - 1 , p = ( ++t ) + k - 1 ;
		ans = C[t + k][k] ;
		for( j = 1 ; j <= t ; ++j , --p ){
			ans = ( ans + 1LL * C[p][k] * phi % mod ) % mod ;
			phi = 1LL * phi * pri[i] % mod ;
		}
		ans = 1LL * last * ans % mod ;
	}
	printf("%d\n" , ans ) ;
}

int main(){
	
	freopen( "totient.in" , "r" , stdin ) ;
	freopen( "totient.out" , "w" , stdout ) ;
	
	init() ;
	
	scanf( q ) ;
	
	while( q-- ){
		scanf( m ) ; scanf( a ) ; scanf( k ) ;
		solve() ;
	}
	
	return 0 ;
}
