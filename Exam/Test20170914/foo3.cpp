#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>

using std :: pair ;
using std :: vector ;
using std :: make_pair ;

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
static const int maxx = maxn * 20 ;

int n ;
int m ;
int cnt ;

int Fa[maxn] ;
int root[maxn] ;

int Ch[maxx][2] ;
uint val[maxx][2] ;

uint ans[maxn] ;

vector < pair< int , int > > vec1[maxn] , vec2[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxn] ;
int to[maxn] ;

inline void ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

void update( int rt ){
	val[rt][0] = val[Ch[rt][0]][0] + val[Ch[rt][1]][0] ;
	val[rt][1] = val[Ch[rt][0]][1] + val[Ch[rt][1]][1] ;
}

void modify( int& rt , int l , int r , int i , int x , int y , uint& res ){
	if( !rt )rt = ++cnt ;
	if( l == r )
		return val[rt][0] += x , val[rt][1] += y , void() ;
	int mid = l + r >> 1 ;
	if( i <= mid ){
		if( x )res += x * val[Ch[rt][1]][1] ;
		modify( Ch[rt][0] , l , mid , i , x , y , res ) ;
	}
	else{
		if( y )res += y * val[Ch[rt][0]][0] ;
		modify( Ch[rt][1] , mid + 1 , r , i , x , y , res ) ;
	}
	update( rt ) ;
}

int merge( int x , int y , uint& res ){
	if( !( x * y ) )return x ^ y ;
	res += val[Ch[x][0]][0] * val[Ch[y][1]][1] ;
	res += val[Ch[y][0]][0] * val[Ch[x][1]][1] ;
	val[x][0] += val[y][0] ; val[x][1] += val[y][1] ;
	Ch[x][0] = merge( Ch[x][0] , Ch[y][0] , res ) ;
	Ch[x][1] = merge( Ch[x][1] , Ch[y][1] , res ) ;
	return x ;
}

void dfs( int x ){
	Rep( i , Ht[x] , Nt[i] )
		dfs( to[i] ) , ans[x] += ans[to[i]] ,
		root[x] = merge( root[x] , root[to[i]] , ans[x] ) ;
	For( i , 0 , vec1[x].size() - 1 )
		modify( root[x] , 1 , m , vec1[x][i].first , vec1[x][i].second , 0 , ans[x] ) ;
	For( i , 0 , vec2[x].size() - 1 )
		modify( root[x] , 1 , m , vec2[x][i].first , 0 , vec2[x][i].second , ans[x] ) ;
}

int main(){
	
	freopen( "foo.in" , "r" , stdin ) ;
	freopen( "foo.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	For( i , 2 , n )
		scanf( Fa[i] ) , ins( Fa[i] , i ) ;
	
	scanf( m ) ;
	
	register int op ;
	register int u ;
	register uint x ;
	
	For( i , 1 , m ){
		scanf( op ) ; scanf( u ) ; scanf( x ) ;
		if( op == 1 )vec1[u].push_back( make_pair( i , x ) ) ;
		else vec2[u].push_back( make_pair( i , x ) ) ;
	}
	
	dfs( 1 ) ;
	
	For( i , 1 , n )printf("%u\n" , ans[i] ) ;
	
	return 0 ;
}
