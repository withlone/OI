#include<cstdio>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

static const int LEN = 1 << 15 ;
char buffer[LEN] , *S , *T ;

char Getchar(){
	if( S == T )T = ( S = buffer ) + fread( buffer , 1 , LEN , stdin ) ;
	return S == T ? EOF : *S++ ;
}

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >
inline void swap( type& x , type& y ){ type t = x ; x = y ; y = x ; }
template< typename type >
inline void scanf( type& in ){
	in = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch > '9'||ch < '0';ch = Getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch >='0'&&ch <='9';ch = Getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

typedef long long LL ;
static const int maxn = 2e5 + 10 ;
static const int maxm = maxn << 1 ;
static const int maxx = 1 << 18 | 1 ;

int n ;
int m ;
int q ;

int dep[maxn] ;
LL val[maxn] ;
LL ans[maxx] ;

int Ct = 1 ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

void ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

void dfs( int x ){
	Rep( i , Ht[x] , Nt[i] )
		if( !dep[to[i]] )
			dep[to[i]] = dep[x] + 1 , dfs( to[i] ) ;
}

int main(){
	
	freopen( "xor.in" , "r" , stdin ) ;
	freopen( "xor.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( q ) ;
	
	For( i , 1 , n - 1 ){
		int x , y ;
		scanf( x ) ; scanf( y ) ;
		ins( x , y ) ; ins( y , x ) ;
	}
	
	For( i , 1 , n )scanf( val[i] ) ;
	
	dep[1] = 1 ;
	dfs( 1 ) ;
	
	For( i , 1 , n )
		ans[dep[i] - 1] ^= val[i] ;
	
	For( j , 0 , 18 )
		For( i , 0 , 1 << 18 )
			if( !( i & ( 1 << j ) ) )
				ans[ i | ( 1 << j ) ] ^= ans[i] ;
	
	int t = ( 1 << 18 ) - 1 ;
	
	while( q-- ){
		LL x ;
		scanf( x ) ;
		printf("%lld\n" , ans[ ( ( x - 1 ) ^ t ) & t ] ) ;
	}
	
	return 0 ;
}
