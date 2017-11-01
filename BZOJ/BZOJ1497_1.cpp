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

static const int maxn = 5e3 + 10;
static const int maxm = 5e4 + 10;
static const int maxe = maxn + maxm * 4 << 1;
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;
int ans ;

int P[maxn];
int A[maxm];
int B[maxm];
int C[maxm];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )scanf( P[i] ) , P[i] <<= 1;
	For( i , 1 , m )
		scanf( A[i] ) , scanf( B[i] ) , scanf( C[i] ) , C[i] <<= 1;
}

int Ct = 1;
int Ht[maxn];
int Nt[maxe];
int to[maxe];
int cap[maxe];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

void build_edge(){
	S = 0 ; T = n + 1 ;
	For( i , 1 , n )
		Ins( i , T , P[i] ) ;
	For( i , 1 , m ){
		int c = C[i] >> 1;
		Ins( S , A[i] , c ) ,
		Ins( S , B[i] , c ) ,
		Ins( A[i] , B[i] , c ) ,
		Ins( B[i] , A[i] , c ) ;
		ans += C[i];
	}
}

int dep[maxn];
int cur[maxn];

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = -1;
	memset( dep , 0 , sizeof( int ) * ( T + 1 ) );
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head <= tail ){
		int x = que[ head++ ] ;
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
	if( x == T )return maxflow ;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[to[i]] == dep[x] + 1 && cap[i] ){
			int t = dfs( to[i] , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t;
		}
	return 0;
}

void dinic(){
	int t ;
	while( bfs() ){
		memcpy( cur , Ht , sizeof( int ) * ( T + 1 ) ) ;
		while( t = dfs( S , inf ) )ans -= t;
	}
	printf("%d\n" , ans >> 1 );
}

int main(){

	read_in();

	build_edge();

	dinic();

	return 0;
}
