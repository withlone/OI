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

static const int maxn = 30 * 30 + 10;
static const int maxm = 20 * maxn;
static const int maxx = 30 + 10;
static const int Inf = 0x7fffffff;

int n;
int m;
int S;
int T;

int cnt;
int A[maxx][maxx];
int num[maxx][maxx];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )For( j , 1 , m )
		scanf( A[i][j] ) , num[i][j] = ++cnt;
}

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

void build_edge(){
	S = 0 ; T = cnt + 1 ;
	For( i , 1 , n )For( j , 1 , m )
		if( ( i & 1 ) == ( j & 1 ) )
			Ins( S , num[i][j] , A[i][j] ) , Ins( num[i][j] , S , 0 ) ;
		else Ins( num[i][j] , T , A[i][j] ) , Ins( T , num[i][j] , 0 ) ;
	For( i , 1 , n )For( j , 1 , m )if( ( i & 1 ) == ( j & 1 ) ){
		if( i > 1 )Ins( num[i][j] , num[i - 1][j] , Inf ) , Ins( num[i - 1][j] , num[i][j] , 0 ) ;
		if( i < n )Ins( num[i][j] , num[i + 1][j] , Inf ) , Ins( num[i + 1][j] , num[i][j] , 0 ) ;
		if( j > 1 )Ins( num[i][j] , num[i][j - 1] , Inf ) , Ins( num[i][j - 1] , num[i][j] , 0 ) ;
		if( j < m )Ins( num[i][j] , num[i][j + 1] , Inf ) , Ins( num[i][j + 1] , num[i][j] , 0 ) ;
	}
}

int cur[maxn];
int dep[maxn];

#define y To[i]

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = -1;
	que[ ++tail ] = S;
	memset( dep , 0 , sizeof dep );
	dep[S] = 1;
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
	if( x == T )return maxflow ;
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
	int res = 0 , t ;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = Dfs( S , Inf ) )res += t;
	}
	return res;
}

void display(){
	int tot = 0 ;
	For( i , 1 , n )For( j , 1 , m )
		tot += A[i][j];
	printf("%d\n" , tot - Dinic() );
}

int main(){
	
	read_in();
	
	build_edge();
	
	display();
	
	return 0;
}
