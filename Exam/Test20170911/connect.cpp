#include<cstdio>
#include<algorithm>

using std :: sort ;

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

typedef long long LL ;
static const int maxn = 5e3 + 10 ;
static const int maxm = 1e5 + maxn ;

int n ;
int m ;

LL ans ;

int Fa[maxn] ;
int val[maxn] ;

class edge{
	public :
		int x ;
		int y ;
		int z ;
		
		edge(){ x = y = z = 0 ; }
		edge( int a , int b , int c ){ x = a ; y = b ; z = c ; }
		
		bool operator < ( const edge& x )
			const { return z < x.z ; }
}e[maxm] ;

int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int main(){
	
	freopen( "connect.in" , "r" , stdin ) ;
	freopen( "connect.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ;
	
	For( i , 1 , n )scanf( val[i] ) ;
	
	For( i , 1 , m )
		scanf( e[i].x ) , scanf( e[i].y ) , scanf( e[i].z ) ;
	
	For( i , 1 , n )
		e[ ++m ] = edge( 0 , i , val[i] ) ;
	
	sort( 1 + e , 1 + m + e ) ;
	
	For( i , 1 , n )Fa[i] = i ;
	
	For( i , 1 , m )
		if( Find( e[i].x ) != Find( e[i].y ) ){
			Fa[ Find( e[i].x ) ] = Find( e[i].y ) ;
			ans += e[i].z ;
		}
	
	printf("%lld\n" , ans ) ;
	
	return 0 ;
}
