#include<cmath>
#include<cstdio>
#include<cstring>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef double DB;
static const int maxn = 100 + 10;
static const int maxm = 400 + 10;
static const int maxe = maxm << 1;
static const DB inf = 1e9;
static const DB eps = 1e-5;

int cmp( DB x , DB y ){ return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ; }

int n;
int m;
int S;
int T;
DB mid;

int A[maxm];
int B[maxm];
int C[maxm];

void read_in(){
	S = 1 ; T = n ;
	For( i , 1 , m )
		scanf( A[i] ) , scanf( B[i] ) , scanf( C[i] ) ;
}

int Ct = 1;
int Ht[maxn];
int Nt[maxe];
int to[maxe];
DB cap[maxe];

void Ins( int x , int y , DB z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = z ;
}

int dep[maxn];
int cur[maxn];

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = -1 ;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head <= tail ){
		int x = que[ head++ ];
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[to[i]] && cap[i] > eps ){
				dep[to[i]] = dep[x] + 1 ;
				if( to[i] == T )return true;
				que[ ++tail ] = to[i];
			}
	}
	return false;
}

DB min( DB x , DB y ){ return cmp( x , y ) == -1 ? x : y ; }

DB dfs( int x , DB maxflow ){
	if( x == T )return maxflow;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[to[i]] == dep[x] + 1 && cap[i] > eps ){
			DB t = dfs( to[i] , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0;
}

DB dinic(){
	DB res = 0 , t;
	Ct = 1 ; memset( Ht , 0 , sizeof Ht ) ;
	For( i , 1 , m )
		if( C[i] - mid < eps )res += C[i] - mid;
		else Ins( A[i] , B[i] , C[i] - mid ) ;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = dfs( S , inf ) )res += t ;
	}
	return res;
}

int vct;
int vec[maxm];

void div(){
	DB l = 0 , r = 1e9;
	while( r - l > eps ){
		mid = ( l + r ) / 2.0 ;
		if( dinic() < eps )r = mid;
		else l = mid;
	}
	dinic();
	bfs();
	vct = 0;
	For( i , 1 , m )
		if( C[i] - mid < eps || dep[ A[i] ] && !dep[ B[i] ] || !dep[ A[i] ] && dep[ B[i] ] )
			vec[ ++vct ] = i ;
	printf("%d\n" , vct );
	For( i , 1 , vct )
		printf("%d%c" , vec[i] , vct == i ? '\n' : ' ' );
}

int main(){
	
	bool f = false;
	
	while( scanf( "%d%d" , &n , &m ) != EOF ){
		
		if( f )putchar( '\n' ) ; else f = true;
		
		read_in();
		
		div();
	}
	return 0;
}
