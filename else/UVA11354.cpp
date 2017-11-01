#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}
template< typename Type >inline void printf( Type x ){
	if( x < 0 )putchar( '-' ) , x = -x;
	if( x > 9 )printf( x / 10 );
	putchar( x % 10 + '0' );
}

static const int maxn = 5e4 + 10;
static const int maxm = 1e5 + 10;
static const int maxx = 17;

int n;
int m;
int q;

struct edge{
	int x , y , z;
	bool operator < ( edge t ) const { return z < t.z ; }
}e[maxm];

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
int Dt[maxm];

int dep[maxn];
int Fa[maxn][maxx];
int dis[maxn][maxx];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = z;
}

void init(){
	Ct = 0;
	memset( Ht , 0 , sizeof Ht );
	memset( dep , 0 , sizeof dep );
	memset( Fa , 0 , sizeof Fa );
	memset( dis , 0 , sizeof dis );
}

void read_in(){
	For( i , 1 , m )
		scanf( e[i].x ) , scanf( e[i].y ) , scanf( e[i].z );
}

int Fat[maxn];

int Find( int t ){ return t == Fat[t] ? t : Fat[t] = Find( Fat[t] ) ; }

void kruskal(){
	sort( 1 + e , 1 + m + e );
	For( i , 1 , n )Fat[i] = i;
	For( i , 1 , m )
		if( Find( e[i].x ) != Find( e[i].y ) ){
			Fat[ Find( e[i].x ) ] = Find( e[i].y ) ;
			Ins( e[i].x , e[i].y , e[i].z ) ; Ins( e[i].y , e[i].x , e[i].z ) ;
		}
}

void Dfs( int x , int f ){
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( y == f )continue;
		Fa[y][0] = x;
		dis[y][0] = Dt[i];
		dep[y] = dep[x] + 1;
		Dfs( y , x );
	}
}

void preparation(){
	dep[1] = 1;
	Dfs( 1 , 0 );
	For( j , 1 , maxx - 1 )
		For( i , 1 , n )
			Fa[i][j] = Fa[ Fa[i][j - 1] ][j - 1] ,
			dis[i][j] = max( dis[i][j - 1] , dis[ Fa[i][j - 1] ][j - 1] );
}

int query( int x , int y ){
	if( dep[x] < dep[y] )swap( x , y );
	int delta = dep[x] - dep[y] , res = 0;
	For( i , 0 , maxx - 1 )
		if( ( 1 << i ) & delta )
			res = max( res , dis[x][i] ) , x = Fa[x][i];
	if( x == y )return res;
	Lop( i , maxx - 1 , 0 )
		if( Fa[x][i] != Fa[y][i] )
			res = max( res , max( dis[x][i] , dis[y][i] ) ) ,
			x = Fa[x][i] , y = Fa[y][i];
	return max( res , max( dis[x][0] , dis[y][0] ) );
}

void display(){
	scanf( q ) ;
	For( i , 1 , q ){
		int x , y ;
		scanf( x ) ; scanf( y ) ;
		printf( query( x , y ) ) , putchar( '\n' );
	}
}

int main(){
	
	bool f = 0;
	
	while( scanf("%d%d" , &n , &m ) != EOF ){
		
		if( f )putchar( '\n' ) ; else f = true;
		
		init();
		
		read_in();
	
		kruskal();
		
		preparation();
		
		display();
		
	}
	return 0;
}
