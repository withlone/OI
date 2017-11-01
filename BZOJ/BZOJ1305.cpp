#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 50 + 10;
static const int maxk = 30 + 10;
static const int maxx = maxn << 2;
static const int maxm = 5500;
static const int inf = ~0U >> 1;

int n;
int k;
int S;
int T;

char relation_graph[maxn][maxn];

void read_in(){
	scanf( n ) ; scanf( k ) ;
	For( i , 1 , n )
		scanf( "%s" , relation_graph[i] + 1 ) ;
}

int Ct = 1;
int Ht[maxx];
int Nt[maxm];
int to[maxm];
int cap[maxm];
int tcp[maxm];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; tcp[Ct] = cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; tcp[Ct] = cap[Ct] = 0 ;
}

/*
	i means boy_like
	i + n means boy_dislike
	i + n  + n means girl_like
	i + n + n + n meas girl_dislike
*/

int sign_up_boy;
int sign_up_girl;
int sign_down_boy;
int sign_down_girl;

void edge_to_oneself(){
	For( i , 1 , n )
		Ins( i , i + n , k ) ,
		Ins( i + n + n + n , i + n + n , k ) ;
}

void edge_like_to_like(){
	For( i , 1 , n )For( j , 1 , n )
		if( relation_graph[i][j] == 'Y' )
			Ins( i , j + n + n , 1 ) ;
}

void edge_dislike_to_dislike(){
	For( i , 1 , n )For( j , 1 , n )
		if( relation_graph[i][j] != 'Y' )
			Ins( i + n , j + n + n + n , 1 ) ;
}

void edge_S_to_boy(){
	sign_up_boy = Ct + 1;
	For( i , 1 , n )
		Ins( S , i , 0 );
	sign_down_boy = Ct ;
}

void edge_girl_to_T(){
	sign_up_girl = Ct + 1;
	For( i , 1 , n )
		Ins( i + n + n , T , 0 ) ;
	sign_down_girl = Ct ;
}

void build_edge(){
	S = 0 ; T = n << 2 | 1 ;
	edge_to_oneself();
	edge_like_to_like();
	edge_dislike_to_dislike();
	edge_S_to_boy();
	edge_girl_to_T();
}

int cur[maxx];
int dep[maxx];

bool bfs(){
	static int que[maxx];
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
		memcpy( cur , Ht , sizeof cur );
		while( t = dfs( S , inf ) ) res += t ;
	}
	return res ;
}

bool chk_flow_full(){
	int dinic_maxflow = dinic();
	For( i , sign_up_boy , sign_down_girl )
		if( cap[i] )return false;
		else ++i ;
	return true;
}

bool chk( int flow ){
	memcpy( cap , tcp , sizeof cap ) ;
	For( i , sign_up_boy , sign_down_girl )
		tcp[i] = cap[i] = flow , ++i ;
	return chk_flow_full();
}

void div(){
	int l = 0 , r = n , res;
	while( l <= r ){
		int mid = l + r >> 1;
		if( chk( mid ) )l = mid + 1 , res = mid ;
		else r = mid - 1 ;
	}
	printf("%d\n" , res ) ;
}

int main(){
	
	read_in();
	
	build_edge();
	
	div();
	
	return 0;
}
