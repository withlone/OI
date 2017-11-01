#include<cstdio>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; i-- )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template< typename type >
inline void scanf( type &in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch > '9'||ch < '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch >='0'&&ch <='9';ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

static const int maxn = 200 + 10 ;
static const int maxm = maxn * maxn ;

int n ;
int m ;
int k ;

int Fa[maxn] ;
int D[maxn][maxn] ;

class edge{
	
	public :
		int x ;
		int y ;
		int z ;
		edge(){ x = y = z = 0 ; }
		edge( int a , int b , int c ){ x = a ; y = b ; z = c ; }
		
		bool operator < ( const edge& t )
			const { return z < t.z ; }
	
}e[maxm] ;

int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int main(){
	
	freopen("partition.in" , "r" , stdin) ;
	freopen("partition.out" , "w" , stdout) ;
	
	scanf( n ) ; scanf( k ) ;
	
	For( i , 1 , n )For( j , 1 , n ){
		scanf( D[i][j] ) ;
		if( i < j )
			e[ ++m ] = edge( i , j , D[i][j] ) ;
	}
	
	sort( 1 + e , 1 + m + e ) ;
	
	For( i , 1 , n )Fa[i] = i ;
	
	For( i , 1 , m )
		if( Find( e[i].x ) != Find( e[i].y ) ){
			if( n == k )return printf("%d\n" , e[i].z ) , 0 ;
			Fa[ Find( e[i].x ) ] = Find( e[i].y ) ;
			++k ;
		}
	
	puts("0") ;
	
	return 0 ;
}
