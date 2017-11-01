#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 2e4 + 10;
static const int maxm = 2e5 + 10;
static const int maxe = maxm << 1;
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;
int L;

int pos;

int ans;

int cur[maxn];
int dep[maxn];

int cost[maxm];

class edge{
	public :
		int x;
		int y;
		int cost;
		
		bool operator < ( const edge &t ) const { return cost < t.cost ; }
}e[maxm];

int Ct = 1 ;
int Ht[maxn];
int Nt[maxe];
int to[maxe];
int cap[maxe];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = z ;
}

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , m )
		scanf( e[i].x ) , scanf( e[i].y ) , scanf( e[i].cost ) ;
	scanf( S ) ; scanf( T ) ; scanf( L ) ;
}

void sort_edge(){
	sort( 1 + e , 1 + m + e ) ;
}

void get_cost_of_edge_out(){
	For( i , 1 , m )
		cost[i] = e[i].cost ;
}

void get_pos1_of_L(){
	pos = lower_bound( 1 + cost , 1 + m + cost , L ) - cost - 1;
}

void get_pos2_of_L(){
	pos = upper_bound( 1 + cost , 1 + m + cost , L ) - cost ;
}

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = 0 ;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head != tail ){
		int x = que[ ++head ] ;
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[to[i]] && cap[i] ){
				dep[to[i]] = dep[x] + 1 ;
				if( to[i] == T )return true;
				que[ ++tail ] = to[i] ;
			}
	}
	return false;
}

int dfs( int x , int maxflow ){
	if( x == T )return maxflow ;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[to[i]] == dep[x] + 1 && cap[i] ){
			int t = dfs( to[i] , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0 ;
}

int dinic(){
	int res = 0 , t ;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur ) ;
		while( t = dfs( S , inf ) )res += t ;
	}
	return res ;
}

void get_edge_of_min_tree_need(){
	For( i , 1 , pos )
		Ins( e[i].x , e[i].y , 1 ) ;
	ans += dinic();
}

void preparation(){
	Ct = 1 ; memset( Ht , 0 , sizeof Ht ) ;
}

void get_edge_of_max_tree_need(){
	preparation();
	For( i , pos , m )
		Ins( e[i].x , e[i].y , 1 ) ;
	ans += dinic();
}

void display(){
	printf("%d\n" , ans ) ;
}

int main(){
	
	read_in();
	
	sort_edge();
	
	get_cost_of_edge_out();
	
	get_pos1_of_L();
	
	get_edge_of_min_tree_need();
	
	get_pos2_of_L();
	
	get_edge_of_max_tree_need();
	
	display();
	
	return 0;
}
