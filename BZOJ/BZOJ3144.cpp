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

static const int maxn = 40 + 10;
static const int maxx = maxn * maxn * maxn;
static const int maxm = maxx << 2;
static const int inf = ~0U >> 1;

int P;
int Q;
int R;
int D;
int S;
int T;

int score[maxn][maxn][maxn];
int sco[maxx];

void read_in(){
	scanf( P ) ; scanf( Q ) ; scanf( R ) ; scanf( D ) ;
	For( k , 1 , R )For( i , 1 , P )For( j , 1 , Q )
		scanf( score[i][j][k] ) ;
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

int cnt;
int num[maxn][maxn][maxn];

void Lable(){
	For( k , 1 , R )For( i , 1 , P )For( j , 1 , Q )
		sco[ num[i][j][k] = ++cnt ] = score[i][j][k];
}

void build_edge(){
	S = 0 ; T = ++cnt ;
	For( i , 1 , P * Q )
		Ins( S , i , sco[i] ) ;
	For( i , P * Q * ( R - 1 ) + 1 , P * Q * R )
		Ins( i , T , sco[i] ) ;
	For( i , P * Q + 1 , P * Q * R )
		Ins( i - P * Q , i , sco[i] ) ;
	For( i , P * Q * ( D - 1 ) + 1 , P * Q * D )
		Ins( i , S , inf ) ;
	For( k , D + 1 , R )For( i , 1 , P )For( j , 1 , Q ){
		if( num[i + 1][j][k - D] )
			Ins( num[i][j][k] , num[i + 1][j][k - D] , inf ) ;
		if( num[i - 1][j][k - D] )
			Ins( num[i][j][k] , num[i - 1][j][k - D] , inf ) ;
		if( num[i][j + 1][k - D] )
			Ins( num[i][j][k] , num[i][j + 1][k - D] , inf ) ;
		if( num[i][j - 1][k - D] )
			Ins( num[i][j][k] , num[i][j - 1][k - D] , inf ) ;
	}
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
				dep[to[i]] = dep[x] + 1;
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
	printf("%d\n" , res ) ;
}

int main(){
	
	read_in();
	
	Lable();	
	
	build_edge();
	
	Dinic();
	
	return 0;
}
