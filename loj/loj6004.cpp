#include<cstdio>
#include<vector>
#include<cstring>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e3 + 10;
static const int maxm = 1e5 + 10;
static const int Inf = 0x7fffffff;

int n;
int m;
int S;
int T;

int peo[maxn];
int val[maxn];

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

void read_in(){
	scanf( m ) ; scanf( n ) ;
	For( i , 1 , m )scanf( peo[i] ) ;
	For( i , 1 , n )scanf( val[i] ) ;
}

void build_edge(){
	S = 0 ; T = 1e3 + 9 ;
	For( i , 1 , n )
		Ins( S , i , val[i] ) , Ins( i , S , 0 ) ;
	For( i , 1 , m )
		Ins( i + n , T , peo[i] ) , Ins( T , i + n , 0 ) ;
	For( i , 1 , n )
		For( j , 1 + n , m + n )
			Ins( i , j , 1 ) , Ins( j , i , 0 ) ;
}

int dep[maxn];
int cur[maxn];

#define y To[i]

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = -1;
	que[ ++tail ] = S;
	memset( dep , 0 , sizeof dep );
	dep[S] = 1;
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
	if( x == T )return maxflow;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[y] == dep[x] + 1 && cap[i] ){
			int t = Dfs( y , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t;
		}
	return 0;
}

#undef y

bool Dinic(){
	int res = 0 , t;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = Dfs( S , Inf ) )res += t;
	}
	int tot = 0;
	For( i , 1 , m )tot += peo[i];
	return res == tot;
}

vector < int > dy[maxn];

void display(){
	bool ans = Dinic();
	printf("%d\n" , ans );
	if( !ans )return;
	For( i , 1 , n )
		Rep( j , Ht[i] , Nt[j] )
			if( To[j] != S && !cap[j] )dy[To[j] - n].push_back( i );
	For( i , 1 , m )
		For( j , 0 , dy[i].size() - 1 )
			printf("%d%c" , dy[i][j] , j == dy[i].size() - 1 ? '\n' : ' ' );
}

int main(){
	
	read_in();
	
	build_edge();
	
	display();
	
	return 0;
}
