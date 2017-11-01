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
static const int maxm = 2e3 + 10;
static const DB inf = 1e9;
static const DB eps = 1e-6;

int cmp( DB x , DB y ){ return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ; }

DB min( DB x , DB y ){ return cmp( x , y ) == -1 ? x : y ; }

int n;
int m;
int P;
int S;
int T;
DB top;

int Ct = 1;
int Ht[maxn];
int Nt[maxm];
int to[maxm];
DB tm[maxm];
DB cap[maxm];

void Ins( int x , int y , DB z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; tm[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; tm[Ct] = 0 ;
}

void read_in(){
	scanf( n ) ; scanf( m ) ; scanf( P ) ;
	For( i , 1 , m ){
		int x , y , z ;
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		Ins( x , y , z ) ;
	}
	S = 1 ; T = n ;
}

int dep[maxn];
int cur[maxn];

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = -1;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head <= tail ){
		int x = que[ head++ ] ;
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[to[i]] && cap[i] ){
				cap[i] = min( cap[i] , top );
				dep[to[i]] = dep[x] + 1 ;
				if( to[i] == T )return true;
				que[ ++tail ] = to[i];
			}
	}
	return false;
}

DB dfs( int x , DB maxflow ){
	if( x == T )return maxflow;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[to[i]] == dep[x] + 1 && cap[i] ){
			DB t = dfs( to[i] , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0;
}

DB dinic(){
	DB res = 0 , t;
	memcpy( cap , tm , sizeof cap );
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = dfs( S , inf ) )
			res += t ;
	}
	return res;
}

void div(){
	top = inf;
	DB maxflow = dinic();
	printf("%.0lf\n" , maxflow);
	DB l = 0 , r = inf , res;
	while( cmp( l , r ) ){
		top = ( l + r ) / 2.0;
		if( !cmp( dinic() , maxflow ) )res = top , r = top;
		else l = top;
	}
	printf("%.4lf\n" , res * P ) ;
}

int main(){
	
	read_in();
	
	div();
	
	return 0;
}
