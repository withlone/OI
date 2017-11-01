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
static const int maxx = maxn << 1 ;

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

class matrix{
	public :
		uint s[3][3] ;
		matrix(){
			memset( s , 0 , sizeof s ) ;
			s[0][0] = s[1][1] = s[2][2] = 1 ;
		}
		matrix operator * ( const matrix& x ){
			matrix y ;
			y.s[0][0] = y.s[1][1] = y.s[2][2] = 0 ;
			For( i , 0 , 2 )For( j , 0 , 2 )For( k , 0 , 2 )
				y.s[i][j] += s[i][k] * x.s[k][j] ;
			return y ;
		}
		inline bool chk(){ return s[0][1] + s[2][0] + s[2][1] != 0 ; }
}tag[maxx] ;

matrix base ;

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
	int mid = l + r >> 1 ;
	int rt = get( l , r ) , ls = get( l , mid ) , rs = get( mid + 1 , r ) ;
	tag[ls] = tag[ls] * tag[rt] ; tag[rs] = tag[rs] * tag[rt] ;
	tag[rt] = base ;
}

void modify( int l , int r , int L , int R , matrix d ){
	if( l >= L && r <= R )
		return tag[get( l , r )] = tag[get( l , r )] * d , void() ;
	int mid = l + r >> 1 ;
	if( tag[get( l , r )].chk() )pushdown( l , r ) ;
	if( mid >= L )modify( l , mid , L , R , d ) ;
	if( mid < R )modify( mid + 1 , r , L , R , d ) ;
}

uint query( int l , int r , int x ){
	if( l == r )return tag[get( l , r )].s[2][1] ;
	int mid = l + r >> 1;
	if( tag[get( l , r )].chk() )pushdown( l , r ) ;
	if( x <= mid )return query( l , mid , x ) ;
	return query( mid + 1 , r , x ) ;
}

int main(){
	
	freopen( "foo.in" , "r" , stdin ) ;
	freopen( "foo.out" , "w" , stdout ) ;
	
	base.s[0][0] = base.s[1][1] = base.s[2][2] = 1 ;
	
	scanf( n ) ;
	For( i , 2 , n )
		scanf( Fa[i] ) , ins( Fa[i] , i ) ;
	
	dfs1( 1 ) ;
	dfs2( 1 , 1 ) ;
	
	scanf( m ) ;
	
	register int op ;
	register int u ;
	register uint x ;
	
	matrix c = base ;
	
	while( m-- ){
		scanf( op ) ; scanf( u ) ; scanf( x ) ;
		if( op == 1 )c.s[2][0] = x , c.s[0][1] = 0 ;
		if( op == 2 )c.s[2][0] = 0 , c.s[0][1] = x ;
		for( ; u ; u = Fa[top[u]] )
			modify( 1 , n , rnk[top[u]] , rnk[u] , c ) ;
	}
	
	For( i , 1 , n )printf("%u\n" , query( 1 , n , rnk[i] ) ) ;
	
	return 0 ;
}
