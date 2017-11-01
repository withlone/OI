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
static const int maxx = 1e4 + 10;
static const int maxm = maxx * 6;
static const int inf = 1e9;

int n;
int m;
int S;
int T;

int mp[maxn][maxn];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )For( j , 1 , m )
		scanf( mp[i][j] ) ;
}

int cnt;
int num[maxn][maxn];

void preparation(){
	For( i , 1 , n )For( j , 1 , m )
		num[i][j] = ++cnt;
}

int Ct = 1;
int Ht[maxx];
int Nt[maxm];
int to[maxm];
int cap[maxm];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = z ;
}

void build_edge(){
	S = 0 ; T = n * m + 1;
	For( i , 1 , n )For( j , 1 , m )
		if( mp[i][j] == 1 )
			Ins( S , num[i][j] , inf ) ;
		else if( mp[i][j] == 2 )
			Ins( num[i][j] , T , inf ) ;
	For( i , 1 , n )For( j , 1 , m ){
		if( num[i + 1][j] ){
			if( mp[i][j] != mp[i + 1][j] || !( mp[i][j] + mp[i + 1][j] ) )
				Ins( num[i][j] , num[i + 1][j] , 1 ) ;
			else
				Ins( num[i][j] , num[i + 1][j] , inf ) ;
		}
		if( num[i][j + 1] ){
			if( mp[i][j] != mp[i][j + 1] || !( mp[i][j] + mp[i][j + 1] ) )
				Ins( num[i][j] , num[i][j + 1] , 1 ) ;
			else
				Ins( num[i][j] , num[i][j + 1] , inf ) ;
		}
	}
}

int cur[maxx];
int dep[maxx];

bool bfs(){
	static int que[maxx];
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
	if( x == T )return maxflow;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[to[i]] == dep[x] + 1 && cap[i] ){
			int t = dfs( to[i] , min( maxflow , cap[i] ) ) ;
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0;
}

void dinic(){
	int res = 0 , t;
	while( bfs() ){
		memcpy( cur , Ht , sizeof( int ) * ( T + 1 ) );
		while( t = dfs( S , inf ) )res += t ;
	}
	printf("%d\n" , res ) ;
}

int main(){
	
	read_in();
	
	preparation();
	
	build_edge();
	
	dinic();
	
	return 0;
}
