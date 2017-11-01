#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e2 + 10;
static const int maxm = maxn * maxn;
static const int maxx = maxn << 1;
static const int maxe = maxm << 2;
static const int mod = maxx - 1;
static const int Inf = 0x7fffffff;

int n;
int m;
int S;
int T;

int A[maxm];
int B[maxm];
char city[maxn][20];

map < string , int > mp;

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )
		scanf( "%s" , city[i] ) , mp[ city[i] ] = i;
	For( i , 1 , m ){
		char city1[20] , city2[20];
		scanf( "%s%s" , city1 , city2 );
		A[i] = mp[ city1 ] , B[i] = mp[ city2 ];
	}
}

int Ct = 1;
int Ht[maxx];
int Nt[maxe];
int to[maxe];
int Dt[maxe];
int cap[maxe];

void Ins( int x , int y , int p , int q ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = p ;	cap[Ct] = q ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; Dt[Ct] = -p; cap[Ct] = 0 ;
}

void build_edge(){
	S = 1 ; T = n << 1;
	Ins( S , S + n , 0 , 2 ) , Ins( n , T , 0 , 2 ) ;
	For( i , 2 , n - 1 )
		Ins( i , i + n , 0 , 1 ) ;
	For( i , 1 , m ){
		if( A[i] > B[i] )swap( A[i] , B[i] ) ;
		Ins( A[i] + n , B[i] , 1 , Inf ) ;
	}
}

int ans;

void EK(){
	static int que[maxx];
	static int dis[maxx];
	static int pre[maxx];
	static bool V[maxx];
	while( true ){
		memset( V , 0 , sizeof V );
		memset( dis , -0x3f , sizeof dis );
		int head = 0 , tail = -1;
		que[ ++tail ] = S ; dis[S] = 0 ;
		while( head != ( tail + 1 ) % mod ){
			int x = que[ head++ ] ; V[x] = false;
			if( head == mod )head = 0;
			Rep( i , Ht[x] , Nt[i] )
				if( dis[to[i]] < dis[x] + Dt[i] && cap[i] ){
					dis[to[i]] = dis[x] + Dt[i] ; pre[to[i]] = i;
					if( !V[to[i]] ){
						V[to[i]] = true;
						if( tail == mod - 1 )que[tail = 0] = to[i];
						else que[ ++tail ] = to[i];
					}
				}
		}
		if( dis[T] == dis[0] )break;
		int maxflow = Inf;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )maxflow = min( maxflow , cap[ pre[i] ] ) ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			cap[ pre[i] ] -= maxflow , cap[ pre[i] ^ 1 ] += maxflow ;
		ans += maxflow * dis[T];
	}
}

bool Vis[maxx];

void dfs1( int x ){
	if( x == n )return;
	Vis[x] = true;
	printf("%s\n" , city[x] );
	Rep( i , Ht[x + n] , Nt[i] )
		if( !Vis[to[i]] && cap[i] != Inf ){
			dfs1( to[i] );
			break;
		}
}

void dfs2( int x ){
	Vis[x] = true;
	printf("%s\n" , city[x] );
	Rep( i , Ht[x] , Nt[i] )
		if( !Vis[to[i] - n] && cap[i] ){
			dfs2( to[i] - n );
			break;
		}
}

void display(){
	if( !ans )return puts("No Solution!" ) , void();
	printf("%d\n" , ans );
	dfs1( 1 );
	dfs2( n );
	printf("%s\n" , city[1] );
}

int main(){
	
	read_in();
	
	build_edge();
	
	EK();
	
	display();
	
	return 0;
}
