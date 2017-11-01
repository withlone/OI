#include<cstdio>
#include<algorithm>
using namespace std;

#define For( i , _begin , _end ) for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )
#define Lop( i , _begin , _end ) for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; i-- )

template< typename type >inline void scanf( type &in ){
	in = 0 ; char ch = getchar() ; type f = 1;
	for( ; ch > '9' || ch < '0' ; ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ; ch >='0' && ch <='9' ; ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

typedef long long LL;
static const int maxn = 5e4 + 10;
static const int maxx = 1e5 + 10;
static const int inf = ~0U >> 1 ;

int n;

struct point{
	int x;
	int y;
	int id;
	bool operator < ( point t ) const { return x == t.x ? y < t.y : x < t.x ; }
}gaz[maxn] , sta[maxn];

int A1[maxn];
int A2[maxn];
int B1[maxn];
int B2[maxn];
void read_in(){
	scanf( n ) ;
	For( i , 1 , n )
		scanf( gaz[i].x ) , scanf( gaz[i].y ) , gaz[i].id = i , A1[i] = gaz[i].x , B1[i] = gaz[i].y;
	For( i , 1 , n )
		scanf( sta[i].x ) , scanf( sta[i].y ) , sta[i].id = i , A2[i] = sta[i].x , B2[i] = sta[i].y;
}

void get_ans(){
	LL ans = 0 ;
	For( i , 1 , n )
		ans += ( sta[i].x - sta[i].y ) - ( gaz[i].x - gaz[i].y ) ;
	printf("%lld\n" , ans );
}int pos;

int num = 2;
int root;
int Sz[maxx];
int Fa[maxx];
int Ch[maxx][2];
	
int ber[maxx];
int key[maxx];

int GS( int x ){ return Ch[Fa[x]][1] == x ; }

void Up( int x ){ Sz[x] = Sz[ Ch[x][0] ] + Sz[ Ch[x][1] ] + 1 ; }

void Rotate( int x ){
	int fa = Fa[x] , gfa = Fa[fa] , t = GS( x ) ;
	Ch[fa][t] = Ch[x][t ^ 1];
	if( Ch[x][t ^ 1] )Fa[ Ch[x][t ^ 1] ] = fa;
	Ch[x][t ^ 1] = fa;
	Fa[fa] = x;
	Fa[x] = gfa;
	if( gfa )Ch[gfa][ Ch[gfa][1] == fa ] = x ;
	Up( fa ) ; Up( x ) ;
}

void Splay( int x ){
	for( int fa ; fa = Fa[x] ; Rotate( x ) )
		if( Fa[fa] )Rotate( GS( fa ) == GS( x ) ? fa : x ) ;
	root = x ;
}

void Insert( int x , int y ){
	++num;
	key[num] = x;ber[num] = y ;
	Sz[num] = 1 ;
	int p = root , fa = 0;
	while( true ){
		Sz[p]++;
		fa = p ; p = Ch[p][ key[p] <= x ] ;
		if( !p ){
			p = num;
			Fa[p] = fa ; Ch[fa][ key[fa] <= x ] = p ;
			return Splay( p ) ;
		}
	}
}

int Find( int x ){
	int p = root ;
	while( p )
		if( key[p] != x )p = Ch[p][x > key[p]] ;
		else return p ;
	throw;
}

int pre(){
	int p = Ch[root][0];
	while( Ch[p][1] ) p = Ch[p][1] ;
	return p ;
}

void del( int x ){
	int t = Find( x );
	Splay( t );
	Splay( pre() );
	Sz[root]--;
	Ch[root][1] = Ch[t][1] ;
	Fa[ Ch[t][1] ] = root ;
	ber[t] = Fa[t] = Ch[t][0] = Ch[t][1] = Sz[t] = key[t] = 0 ;
}

void preparation(){
	root = 1;
	Fa[2] = 1 ; Ch[1][1] = 2 ;
	Sz[1] = 2 ; Sz[2] = 1;
	key[1] = -inf ; key[2] = inf ;
}

int get_pre( int x ){
	Insert( x , 0 ) ;
	int res = pre();
	int t1 = ber[res] , t2 = key[res];
	del( x ) ; del( t2 ) ;
	return t1;
}

void get_solution(){
	sort( 1 + sta , 1 + n + sta ) ;
	sort( 1 + gaz , 1 + n + gaz ) ;
	preparation();
	pos = n ;int x , y;
	Lop( i , n , 1 ){
		while( pos && gaz[i].x <= sta[pos].x )
			Insert( sta[pos].y , sta[pos].id ) , pos-- ;
		printf("%d %d\n" , x = gaz[i].id , y = get_pre( gaz[i].y ) );
	}
}

int main(){
	
	freopen("gaz.in","r",stdin);
	freopen("gaz.out","w",stdout);
	
	read_in();
	
	get_ans();
	
	get_solution();
	
	return 0;
}
