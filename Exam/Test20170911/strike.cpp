#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

static const int LEN = 1 << 15 ;
char buffer[LEN] , *S , *T ;

inline char Getchar(){
	if( S == T )T = ( S = buffer ) + fread( buffer , 1 , LEN , stdin ) ;
	return S == T ? EOF : *S++ ;
}

template< typename type >
inline void scanf( type& in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

static const int maxn = 1e3 + 10 ;
static const int maxm = 2e4 + 10 ;
static const int inf = ~0U >> 1 ;

int n ;
int m ;
int k ;

int Fa[maxn] ;

class edge{
	public :
		int x ;
		int y ;
		int z ;
		
		edge(){ x = y = z = 0 ; }
		edge( int a , int b , int c ){ x = a ; y = b ; z = c ; }
}e[maxm];

int Ct = 1 ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

void ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ;
}

int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

bool chk( int x ){
	For( i , 1 , n )Fa[i] = i ;
	For( i , 1 , m )if( e[i].z <= x )
		Fa[ Find( e[i].x ) ] = Find( e[i].y ) ;
	Ct = 1 ; memset( Ht , 0 , sizeof Ht ) ;
	For( i , 1 , m )if( Find( e[i].x ) != Find( e[i].y ) )
		ins( Find( e[i].x ) , Find( e[i].y ) ) ;
	
	if( Find( 1 ) == Find( n ) )return true ;
	
	static int que[maxn] ;
	static int dep[maxn] ;
	memset( dep , 0 , sizeof dep ) ;
	int head = 0 , tail = 0 ;
	dep[Find( 1 )] = 1 ; que[ ++tail ] = Find( 1 ) ;
	while( head != tail ){
		int x = que[ ++head ] ;
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[to[i]] ){
				dep[to[i]] = dep[x] + 1 ;
				if( to[i] == Find( n ) )return dep[Find( n )] - 1 <= k ;
				que[ ++tail ] = to[i] ;
			}
	}
	return false ;
}

int main(){
	
	freopen( "strike.in" , "r" , stdin ) ;
	freopen( "strike.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m )  ; scanf( k ) ;
	
	For( i , 1 , m ){
		int x , y , z ;
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		e[i] = edge( x , y , z ) ;
	}
	
	int l = 0 , r = 1e6 , ans = -1 ;
	while( l <= r ){
		int mid = l + r >> 1 ;
		if( chk( mid ) )ans = mid , r = mid - 1 ;
		else l = mid + 1 ;
	}
	printf("%d\n" , ans ) ;
	return 0 ;
}
