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

static const int maxn = 1e2 + 10;
static const int maxx = 1e4 + 10;
static const int maxm = maxx << 3;
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;
int ans;

int A_profit[maxn][maxn];
int B_profit[maxn][maxn];
int C_profit[maxn][maxn];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )For( j , 1 , m )
		scanf( A_profit[i][j] ) ;
	For( i , 1 , n )For( j , 1 , m )
		scanf( B_profit[i][j] ) ;
	For( i , 1 , n )For( j , 1 , m )
		scanf( C_profit[i][j] ) ;
}

int cnt;
int num[maxn][maxn];

void preparation(){
	For( i , 1 , n )For( j , 1 , m )
		ans += A_profit[i][j] + B_profit[i][j] ;
	For( i , 1 , n )For( j , 1 , m )
		num[i][j] = ++cnt ;
}

void Get_S_and_T(){
	S = 0 ; T = ++cnt ;
}

int Ct = 1;
int Ht[maxx];
int Nt[maxm];
int to[maxm];
int cap[maxm];

void Ins( int x , int y , int p , int q = 0 ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = p ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = q ;
}

void edge_single_point(){
	For( i , 1 , n )For( j , 1 , m )
		if( ( i & 1 ) ^ ( j & 1 ) )
			Ins( S , num[i][j] , A_profit[i][j] ) ,
			Ins( num[i][j] , T , B_profit[i][j] ) ;
		else
			Ins( S , num[i][j] , B_profit[i][j] ) ,
			Ins( num[i][j] , T , A_profit[i][j] ) ;
}

void edge_from_profit_C(){
	For( i , 1 , n )For( j , 1 , m ){
		if( num[i + 1][j] ){
			int t = C_profit[i][j] + C_profit[i + 1][j] ;
			ans += t ;
			Ins( num[i][j] , num[i + 1][j] , t , t ) ;
		}
		if( num[i][j + 1] ){
			int t = C_profit[i][j] + C_profit[i][j + 1] ;
			ans += t ;
			Ins( num[i][j] , num[i][j + 1] , t , t ) ;
		}
	}
}

void build_edge(){
	
	Get_S_and_T();
	
	edge_single_point();
	
	edge_from_profit_C();
	
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
		memcpy( cur , Ht , sizeof cur ) ;
		while( t = dfs( S , inf ) ) res += t ;
	}
	return res ;
}

int main(){
	
	read_in();
	
	preparation();
	
	build_edge();
	
	printf("%d\n" , ans - dinic() ) ;
	
	return 0 ;
}
