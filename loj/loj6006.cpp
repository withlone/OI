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

static const int maxk = 20 + 10;
static const int maxn = 1e3 + maxk;
static const int maxm = ( maxn + maxk + maxn * maxk ) << 1;
static const int Inf = 0x7fffffff;

int n;
int m;
int S;
int T;

int val[maxk];
int size[maxn];
int ty[maxn][maxk];

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
	For( i , 1 , m )scanf( val[i] );
	For( i , 1 , n ){
		scanf( size[i] );
		For( j , 1 , size[i] )scanf( ty[i][j] );
	}
}

void build_edge(){
	S = 0 ; T = n + m + 1 ;
	For( i , 1 , n )
		Ins( S , i , 1 ) , Ins( i , S , 0 ) ;
	For( i , 1 + n , m + n )
		Ins( i , T , val[i - n] ) , Ins( T , i , 0 ) ;
	For( i , 1 , n )
		For( j , 1 , size[i] )
			Ins( i , ty[i][j] + n , 1 ) , Ins( ty[i][j] + n , i , 0 ) ;
}

int cur[maxn];
int dep[maxn];

#define y To[i]

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = -1;
	memset( dep , 0 , sizeof dep );
	dep[S] = 1;que[ ++tail ] = S;
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

bool Dinic(){
	int res = 0 , t;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = Dfs( S , Inf ) )res += t;
	}
	int tot = 0;
	For( i , 1 , m )tot += val[i];
	return res == tot;
}

#undef y

int sz[maxk];
int ans[maxk][maxn];

void display(){
	if( !Dinic() )return puts("No Solution!") , void();
	For( i , ( n + m << 1 ) + 2 , Ct ){
		if( !cap[i] )ans[ To[i] - n ][ ++sz[ To[i] - n ] ] = To[i ^ 1];
		i++;
	}
	For( i , 1 , m ){
		printf("%d:" , i );
		For( j , 1 , sz[i] )
			printf(" %d" , ans[i][j] );
		putchar( '\n' );
	}
}

int main(){
	
	read_in();
	
	build_edge();
	
	display();
	
	return 0;
}
