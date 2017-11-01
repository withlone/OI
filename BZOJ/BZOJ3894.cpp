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
static const int maxx = 3e4 + 10;
static const int maxm = 30 * maxx;
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;
int ans;

int art[maxn][maxn];
int sci[maxn][maxn];
int s_art[maxn][maxn];
int s_sci[maxn][maxn];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )For( j , 1 , m )
		scanf( art[i][j] ) ;
	For( i , 1 , n )For( j , 1 , m )
		scanf( sci[i][j] ) ;
	For( i , 1 , n )For( j , 1 , m )
		scanf( s_art[i][j] ) ;
	For( i , 1 , n )For( j , 1 , m )
		scanf( s_sci[i][j] ) ;
}

int cnt;
int num[maxn][maxn];

void preparation(){
	For( i , 1 , n )For( j , 1 , m )
		num[i][j] = ++cnt ;
	For( i , 1 , n )For( j , 1 , m )
		ans += art[i][j] + sci[i][j] + s_art[i][j] + s_sci[i][j] ;
}

int Ct = 1;
int Ht[maxx];
int Nt[maxm];
int to[maxm];
int cap[maxm];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

void build_edge(){
	S = 0 ; T = cnt * 3 + 1 ;
	For( i , 1 , n )For( j , 1 , m )
		Ins( S , num[i][j] , art[i][j] ) ,
		Ins( num[i][j] , T , sci[i][j] ) ;
	For( i , 1 , n )For( j , 1 , m ){
		int t1 = num[i][j] + cnt , t2 = t1 + cnt ;
		Ins( S , t1 , s_art[i][j] ) ,
		Ins( t1 , num[i][j] , inf ) ,
		Ins( num[i][j] , t2 , inf ) , 
		Ins( t2 , T , s_sci[i][j] ) ;
		if( num[i - 1][j] )
			Ins( t1 , num[i - 1][j] , inf ) ,
			Ins( num[i - 1][j] , t2 , inf ) ;
		if( num[i + 1][j] )
			Ins( t1 , num[i + 1][j] , inf ) ,
			Ins( num[i + 1][j] , t2 , inf ) ;
		if( num[i][j - 1] )
			Ins( t1 , num[i][j - 1] , inf ) ,
			Ins( num[i][j - 1] , t2 , inf ) ;
		if( num[i][j + 1] )
			Ins( t1 , num[i][j + 1] , inf ) ,
			Ins( num[i][j + 1] , t2 , inf ) ;
	}
}

int cur[maxx];
int dep[maxx];

bool bfs(){
	static int que[maxx];
	int head = 0 , tail = 0;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head != tail ){
		int x = que[ ++head ];
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
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0;
}

int dinic(){
	int res = 0 , t;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur ) ;
		while( t = dfs( S , inf ) )res += t ;
	}
	return res;
}

int main(){
	
	read_in();
	
	preparation();
	
	build_edge();
	
	printf("%d\n" , ans - dinic() );
	
	return 0;
}
