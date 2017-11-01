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

static const int maxn = 300 + 10;
static const int maxm = maxn * ( maxn - 1 ) >> 1 ;
static const int maxe = maxn + maxm << 1;
static const int mod = ( 1 << 9 ) - 1 ;
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;

int opinion[maxn];
int one_side[maxm];
int two_side[maxm];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )
		scanf( opinion[i] ) ;
	For( i , 1 , m )
		scanf( one_side[i] ) , scanf( two_side[i] ) ;
}

void Get_S_and_T(){
	S = 0 ; T = n + 1 ;
}

int Ct = 1;
int Ht[maxn];
int Nt[maxe];
int to[maxe];
int cap[maxe];

void Ins( int x , int y , int p , int q = 0 ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = p ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = q ;
}

void edge_S_to_agree(){
	For( i , 1 , n )
		if( opinion[i] )
			Ins( S , i , 1 ) ;
}

void edge_disagree_to_T(){
	For( i , 1 , n )
		if( !opinion[i] )
			Ins( i , T , 1 ) ;
}

void edge_between_friend(){
	For( i , 1 , m )
		Ins( one_side[i] , two_side[i] , 1 , 1 );
}

void build_edge(){
	
	Get_S_and_T();
	
	edge_S_to_agree();
	
	edge_disagree_to_T();
	
	edge_between_friend();
	
}

int cur[maxn];
int dep[maxn];

bool bfs(){
	static int que[mod + 10];
	int head = 0 , tail = 0 ;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head != tail ){
		int x = que[ ++head ] ;
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[to[i]] && cap[i] ){
				dep[to[i]] = dep[x] + 1 ;
				if( to[i] == T )return true;
				que[ ++tail ] = to[i];
			}
	}
	return false;
}

int dfs( int x , int maxflow ){
	if( x == T ) return maxflow ;
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
		while( t = dfs( S , inf ) ) res += t ;
	}
	return res ;
}

int main(){
	
	read_in();
	
	build_edge();
	
	printf("%d\n" , dinic() );
	
	return 0 ;
}
