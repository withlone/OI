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

typedef long long LL;
static const int maxn = 1e3 + 10;
static const int maxm = maxn * maxn << 3;
static const LL inf = 1 << 18;

int n;
int S;
int T;
LL tot;

LL val[maxn];
LL E[maxn][maxn];

void read_in(){
	scanf( n ) ;
	For( i , 1 , n )scanf( val[i] ) ;
	For( i , 1 , n )For( j , 1 , n )
		scanf( E[i][j] ) , tot += E[i][j];
}

int Ct = 1;
int Ht[maxn];
int Nt[maxm];
int to[maxm];
LL cap[maxm];

void Ins( int x , int y , LL z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

void build_edge(){
	S = 0 ; T = n + 1 ;
	For( i , 1 , n )
		Ins( i , T , val[i] ) ;
	For( i , 1 , n )For( j , 1 , n )
		if( i != j )
		Ins( i , j , E[i][j] << 1 ) , Ins( S , i , E[i][j] );
}

int dep[maxn];
int cur[maxn];

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = -1 ;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head <= tail ){
		int x = que[ head++ ] ;
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[to[i]] && cap[i] ){
				dep[to[i]] = dep[x] + 1 ;
				if( to[i] == T )return true;
				que[ ++tail ] = to[i] ;
			}
	}
	return false;
}

LL dfs( int x , LL maxflow ){
	if( x == T )return maxflow;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[to[i]] == dep[x] + 1 && cap[i] ){
			LL t = dfs( to[i] , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0;
}

void Dinic(){
	LL res = 0 , t;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = dfs( S , inf ) )res += t;
	}
	printf("%lld\n" , tot - res );
}

int main(){
	
	read_in();
	
	build_edge();
	
	Dinic();
	
	return 0;
}
