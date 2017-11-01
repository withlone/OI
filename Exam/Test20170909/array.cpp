#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstdlib>

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
inline void scanf( type &In ){
	In = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

typedef long long LL ;

static const int maxn = 1e6 + 10 ;
static const int mod = 1e9 + 7 ;

bool V[maxn] ;
int i , j , p , q , k , cnt , ans , pri[maxn] ;

LL n , m ;

LL qadd( LL x , LL y , LL mod ){
	LL res = 0 ;
	for( ; y ; y >>= 1 , x = ( x << 1 ) % mod )
		if( y & 1 )res = ( res + x ) % mod ;
	return res ;
}

LL qpow( LL x , LL y , LL mod ){
	LL res = 1 ;
	for( ; y ; y >>= 1 , x = qadd( x , x , mod ) )
		if( y & 1 )res = qadd( res , x , mod ) ;
	return res ;
}

class matrix{
	public :
		int s[2][2] ;
		
		matrix(){ s[0][0] = s[0][1] = s[1][0] = s[1][1] = 0 ; }
		matrix( int a , int b , int c , int d ){
			s[0][0] = a ; s[0][1] = b ; s[1][0] = c ; s[1][1] = d ;
		}
		
		matrix operator * ( const matrix& x ){
			matrix y ;
			y.s[0][0] =
			( qadd( s[0][0] , x.s[0][0] , mod )
			+ qadd( s[0][1] , x.s[1][0] , mod ) ) % mod ;
			y.s[0][1] =
			( qadd( s[0][0] , x.s[0][1] , mod )
			+ qadd( s[0][1] , x.s[1][1] , mod ) ) % mod ;
			y.s[1][0] =
			( qadd( s[1][0] , x.s[0][0] , mod )
			+ qadd( s[1][1] , x.s[1][0] , mod ) ) % mod ;
			y.s[1][1] =
			( qadd( s[1][0] , x.s[0][1] , mod )
			+ qadd( s[1][1] , x.s[1][1] , mod ) ) % mod ;
			return y ;
		}
		
		matrix operator ^ ( LL y ){
			matrix x = *this , res = matrix( 1 , 0 , 0 , 1 );
			for( ; y ; y >>= 1 , x = x * x )
				if( y & 1 )res = res * x ;
			return res ;
		}
};

inline void init(){
	for( i = 2 ; i <= 1e6 ; ++i ){
		if( !V[i] )pri[ ++cnt ] = i ;
		for( j = 1 ; j <= cnt && pri[j] * i <= 1e6 ; ++j ){
			V[ pri[j] * i ] = true ;
			if( !( i % pri[j] ) )break ;
		}
	}
}

bool miller_rabin( LL x ){
	if( !( x & 1 ) )return false ;
	p = 10 ;int t ;
	while( p-- )
		if( ( qpow( t = rand() % ( x - 1 ) + 1 , x - 1 , x ) )!= 1 )
			return false ;
	return true ;
}

void work( int ki ){
	matrix base = matrix( 1 , ki , 1 , 0 ) ;
	base = base ^ n ;
	ans = 1LL * ans * ( base.s[0][0] + base.s[0][1] ) % mod ;
}

void solve(){
	ans = 1 ;
	for( i = 1 ; i <= cnt ; ++i ){
		if( !( m % pri[i] ) ){
			k = 0 ;
			while( !( m % pri[i] ) )
				m /= pri[i] , ++k ;
			work( k ) ;
		}
	}
	if( m == 1 );
	else if( miller_rabin( m ) )
		work( 1 ) ;
	else if( (LL)sqrt( m ) * (LL)sqrt( m ) == m )
		work( 2 ) ;
	else work( 1 ) , work( 1 ) ;
	printf("%d\n" , ans ) ;
}

int main(){
	
	freopen( "array.in" , "r" , stdin ) ;
	freopen( "array.out" , "w" , stdout ) ;
	
	srand( 201314 ) ;
	
	init() ;
	
	scanf( q ) ;
	
	while( q-- ){
		scanf( n ) ; scanf( m ) ;
		solve() ;
	}
	
	return 0 ;
}
