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

static const int maxn = 100 + 10;
static const int maxm = 1e3 + 10;
static const int maxx = maxn << 1;
static const int maxe = 1e6 + 10;
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;

int Ct = 1;
int Ht[maxx];
int Nt[maxe];
int to[maxe];
int cap[maxe];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

bool F[maxn][maxn];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , m ){
		int x , y ;
		scanf( x ) ; scanf( y ) ;
		F[x][y] = true;
	}
}

void Floyd(){
	For( i , 1 , n )F[i][i] = true;
	For( k , 1 , n )
		For( i , 1 , n )
			For( j , 1 , n )
				F[i][j] |= F[i][k] & F[k][j] ;
}

void build_edge(){
	S = 0 ; T = n << 1 | 1 ;
	For( i , 1 , n )
		Ins( S , i , 1 ) ,
		Ins( i + n , T , 1 ) ;
	For( i , 1 , n )For( j , 1 , n )if( i != j )if( F[i][j] )
		Ins( i , j + n , 1 ) ;
}

int dep[maxx];
int cur[maxx];

bool bfs(){
	static int que[maxx];
	int head = 0 , tail = -1;
	memset( dep , 0 , sizeof dep ) ;
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
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0;
}

void Dinic(){
	int res = 0 , t ;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur ) ;
		while( t = dfs( S , inf ) )res += t ;
	}
	printf("%d\n" , n - res ) ;
}

int main(){
		
	read_in();
	
	Floyd();
	
	build_edge();
	
	Dinic();
	
	return 0;
}
