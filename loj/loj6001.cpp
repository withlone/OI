#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline bool scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
	return ch != '\n';
}

static const int maxn = 1e2 + 10;
static const int maxm = 1e6 + 10;
static const int Inf = 0x7fffffff;

int n;
int m;
int S;
int T;
int tot;
int ans;

int val[maxn];
int cost[maxn];

vector < int > G[maxn];

void read_in(){
	scanf( m ) ; scanf( n ) ;
	For( i , 1 , m ){
		bool f = 0;
		int pos = 0 , cnt = 0 , t;
		scanf( val[i] );
		while( scanf( t ) )G[i].push_back( t + m );
		G[i].push_back( t + m );
	}
	For( i , 1 , n )scanf( cost[i] ) ;
}

int Ct = 1;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
int cap[maxm];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	cap[Ct] = z;
}

void build_edge(){
	S = 0 ; T = n + m + 1 ;
	For( i , 1 , m )
		Ins( S , i , val[i] ) , Ins( i , S , 0 );
	For( i , 1 , n )
		Ins( i + m , T , cost[i] ) , Ins( T , i + m , 0 );
	For( i , 1 , m )
		For( j , 0 , G[i].size() - 1 )
			Ins( i , G[i][j] , Inf ) , Ins( G[i][j] , i , 0 ) ;
	tot = n + m + 2;
}

#define y To[i]

int cur[maxn];
int dep[maxn];

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = -1;
	memset( dep , 0 , sizeof( int ) * tot );
	que[ ++tail ] = S ; dep[S] = 1;
	while( head <= tail ){
		int x = que[ head++ ];
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[y] && cap[i] ){
				dep[y] = dep[x] + 1;
				if( y == T )return true;
				que[ ++tail ] = y;
			}
	}
	return false;
}

int Dfs( int x , int maxflow ){
	if( x == T )return maxflow ;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[y] == dep[x] + 1 && cap[i] ){
			int t = Dfs( y , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t;
		}
	return 0;
}

int Dinic(){
	int res = 0 , t;
	while( bfs() ){
		memcpy( cur , Ht , sizeof( int ) * tot );
		while( t = Dfs( S , Inf ) )res += t;
	}
	return res;
}

bool V[maxn];
vector < int > equip;

void Get_detail(){
	For( i , m + 1 << 1 , n + m << 1 ){
		if( !cap[i] )equip.push_back( To[i ^ 1] ) , V[ To[i ^ 1] ] = true;
		++i;
	}
}

bool chk( int x ){
	For( i , 0 , G[x].size() - 1 )
		if( !V[ G[x][i] ] )return false;
	return true;
}

bool Vis[maxn];

void Dfs( int x ){
	Vis[x] = true;
	Rep( i , Ht[x] , Nt[i] )
		if( !Vis[ To[i] ] && cap[i] )Dfs( To[i] );
}

void display(){
	Dfs( 0 );
	For( i , 1 , m )if( Vis[i] )printf("%d " , i ) ; putchar( '\n' );
	For( i , 1 , n )if( Vis[i + m] )printf("%d " , i ) ; putchar( '\n' );
	tot = 0;
	For( i , 1 , m )tot += val[i];
	printf("%d\n" , tot - ans );
}

int main(){
	
	read_in();
	
	build_edge();
	
	ans = Dinic();
	
	Get_detail();
	
	display();
	
	return 0;
}
