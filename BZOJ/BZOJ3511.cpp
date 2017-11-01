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

static const int maxn = 1e4 + 10;
static const int maxm = 4e4 + 10;
static const int maxe = ( maxn << 2 ) + ( maxm << 3 );
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;
int ans;

int A[maxm];
int B[maxm];
int VA[maxn];
int VB[maxn];
int EA[maxm];
int EB[maxm];
int EC[maxm];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 2 , n - 1 )scanf( VA[i] ) ;
	For( i , 2 , n - 1 )scanf( VB[i] ) ;
	For( i , 1 , m )
		scanf( A[i] ) , scanf( B[i] ) ,
		scanf( EA[i] ) , scanf( EB[i] ) , scanf( EC[i] ) ;
}

void preparation(){
	For( i , 1 , n )ans += VA[i] + VB[i] ;
	For( i , 1 , m )ans += EA[i] + EB[i] ;
}

int Ct = 1;
int Ht[maxn];
int Nt[maxe];
int to[maxe];
int cap[maxe];

void Ins( int x , int y , int z ){
	if( x == y )return;
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

void build_edge(){
	S = 0 ; T = n + 1 ;
	Ins( S , 1 , inf ) , Ins( n , T , inf ) ;
	For( i , 2 , n - 1 )
		Ins( S , i , VA[i] ) ,
		Ins( i , T , VB[i] ) ;
	For( i , 1 , m )
		Ins( S , A[i] , EA[i] ) ,
		Ins( A[i] , T , EB[i] ) ,
		Ins( A[i] , B[i] , EC[i] + EA[i] ) ,
		Ins( B[i] , A[i] , EC[i] + EB[i] ) ;
	
}

int dep[maxn];
int cur[maxn];

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = -1;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head <= tail ){
		int x = que[ head++ ];
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
	if( x == T )return maxflow;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[to[i]] == dep[x] + 1 && cap[i] ){
			int t = dfs( to[i] , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t;
		}
	return 0;
}

void dinic(){
	int t;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = dfs( S , inf ) )ans -= t ;
	}
	printf("%d\n" , ans );
}

int main(){
	
	read_in();
	
	preparation();
	
	build_edge();
	
	dinic();
	
	return 0;
}
