#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }

static const int maxn = 200 + 10;
static const int maxm = maxn * maxn;
static const int Inf = 0x7fffffff;

int n;
int m;
int S;
int T;

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
	int x , y ;
	scanf( "%d%d" , &n , &m );
	For( i , 1 , m )
		Ins( i , n + i , 1 ) , Ins( n + i , i , 0 ) ;
	while( scanf( "%d%d" , &x , &y ) != EOF )
		Ins( n + x , y , 1 ) , Ins( y , n + x , 0 ) ;
}

void build_edge(){
	S = 0 ; T = n + m + 1 ;
	For( i , 1 , m )
		Ins( S , i , 1 ) , Ins( i , S , 0 ) ;
	For( i , m + 1 , n )
		Ins( i , T , 1 ) , Ins( T , i , 0 ) ;
}

int dep[maxn];
int cur[maxn];

#define y To[i]

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = -1;
	
	memset( dep , 0 , sizeof( int ) * ( T + 1 ) );
	
	que[ ++tail ] = S;dep[S] = 1;
	
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

int Dinic(){
	int res = 0 , t;
	while( bfs() ){
		memcpy( cur , Ht , sizeof( int ) * ( T + 1 ) );
		while( t = Dfs( S , Inf ) )res += t;
	}
	return res;
}

int main(){
	
	read_in();
	
	build_edge();
	
	printf("%d\n" , Dinic() );
	
	return 0;
}
