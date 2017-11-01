#include<map>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

typedef long long LL ;
static const int maxn = 1e5 + 10 ;
static const int mod1 = 233 ;
static const LL mod2 = 1337006139375617 ;

int n ;
int m ;
int q ;
int root ;

int sz[maxn] ;

bool V[maxn] ;

map < LL , int > size ;

int Ct ;
int Ht[maxn] ;
int Nt[maxn] ;
int to[maxn] ;

void ins( int x , int y ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

void dfs( int x ){
	sz[x] = 1 ;
	Rep( i , Ht[x] , Nt[i] )
		dfs( to[i] ) , sz[x] += sz[to[i]] ;
}

int get_tree( bool f ){
	Ct = 0 ;
	memset( sz , 0 , sizeof(int) * (m + 1) ) ;
	memset( Ht , 0 , sizeof(int) * (m + 1) ) ;
	memset( V , 0 , sizeof(bool) * (m + 1) ) ;
	register int x , y ;
	For( i , 1 , m - 1 ) {
		scanf( "%d%d" , &x , &y ) ;
		ins( x , y ) ;
		V[y] = true ;
	}
	For( i , 1 , m )if( !V[i] ){ root = i ; break ; }
	dfs( root ) ;
	sort( 1 + sz , 1 + m + sz ) ;
	LL t = 0 ;
	For( i , 1 , m )
		t = ( 1LL * t * mod1 % mod2 + sz[i] ) % mod2 ;
	if( f )return size[t] ;
	++size[t] ;
}

int main(){
	
	freopen( "b.in" , "r" , stdin ) ;
	freopen( "b.out" , "w" , stdout ) ;
	
	scanf( "%d%d%d" , &n , &m , &q ) ;
	
	For( i , 1 , n ) 
		get_tree( 0 ) ;
	
	while( q-- )
		printf("%d\n" , get_tree( 1 ) ) ;
	
	return 0 ;
}
