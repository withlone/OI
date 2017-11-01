#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

static const int len = 1 << 15 ;
char buffer[len] , *bs , *bt ;

char Getchar(){
	if( bs == bt )bt = ( bs = buffer ) + fread( buffer , 1 , len , stdin ) ;
	return bs == bt ? EOF : *bs++ ;
}

template< typename type >
inline type scanf( type& in ){
	in = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef unsigned int uint ;
static const int maxn = 3e5 + 10 ;
static const int maxx = maxn << 2 ;

int n ;
int m ;
int cnt ;

int Fa[maxn] ;
int son[maxn] ;
int top[maxn] ;
int rnk[maxn] ;
int size[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxn] ;
int to[maxn] ;

class tager{
	public :
		uint v0 ;
		uint t0 ;
		uint t1 ;
		tager(){ v0 = t0 = t1 = 0U ; }
		tager( uint a , uint b , uint c ){ v0 = a ; t0 = b ; t1 = c ; }
}tag[maxx] ;

inline tager operator + ( const tager& x , const tager& y ){
	return tager( x.v0 + y.v0 , x.t0 + y.t0 , x.t1 + y.t1 - y.v0 * x.t0 ) ;
}

inline void ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

void dfs1( int x ){
	size[x] = 1 ;
	Rep( i , Ht[x] , Nt[i] ){
		dfs1( to[i] ) ;
		size[x] += size[to[i]] ;
		if( size[son[x]] < size[to[i]] )son[x] = to[i] ;
	}
}

void dfs2( int x , int chain ){
	rnk[x] = ++cnt ;
	top[x] = chain ;
	if( son[x] )dfs2( son[x] , chain ) ;
	Rep( i , Ht[x] , Nt[i] )
		if( to[i] != son[x] )
			dfs2( to[i] , to[i] ) ;
}

inline int get( int l , int r ){ return l + r | l != r ; }

inline void pushdown( int l , int r ){
	int rt = get( l , r ) ;
	if( !tag[rt].v0 && !tag[rt].t0 && !tag[rt].t1 )return ;
	int mid = l + r >> 1 ;
	int ls = get( l , mid ) , rs = get( mid + 1 , r ) ;
	tag[ls] = tag[ls] + tag[rt] ; tag[rs] = tag[rs] + tag[rt] ;
	tag[rt] = tager() ;
}

void modify( int l , int r , int L , int R , tager x ){
	int rt = get( l , r ) ;
	if( l >= L && r <= R )
		return tag[rt] = tag[rt] + x , void() ;
	pushdown( l , r ) ;
	int mid = l + r >> 1 ;
	if( mid >= L )modify( l , mid , L , R , x ) ;
	if( mid < R )modify( mid + 1 , r , L , R , x ) ;
}

void query( int l , int r ){
	if( l == r )return ;
	int mid = l + r >> 1 ;
	pushdown( l , r ) ;
	query( l , mid ) ; query( mid + 1 , r ) ;
}

int main(){
	
	freopen( "foo.in" , "r" , stdin ) ;
	freopen( "foo.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	For( i , 2 , n )
		scanf( Fa[i] ) , ins( Fa[i] , i ) ;
	
	dfs1( 1 ) ;
	dfs2( 1 , 1 ) ;
	
	scanf( m ) ;
	
	register int op ;
	register int u ;
	register uint x ;
	
	tager c ;
	
	while( m-- ){
		scanf( op ) ; scanf( u ) ; scanf( x ) ;
		if( op == 1 )c.v0 = x , c.t0 = 0 ;
		else c.v0 = 0 , c.t0 = x ;
		for( ; u ; u = Fa[top[u]] )
			modify( 1 , n , rnk[top[u]] , rnk[u] , c ) ;
	}
	
	query( 1 , n ) ;
	
	For( i , 1 , n )
		x = rnk[i] << 1 ,
		printf("%u\n" , tag[x].v0 * tag[x].t0 + tag[x].t1 ) ;
	
	return 0 ;
}
