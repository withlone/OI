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

static const int maxn = 500 + 10;
static const int maxm = 124750 + 10;
static const int maxe = maxm << 1;
static const int mod = ( 1 << 9 ) - 1;
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;

int pi[maxm];
int qi[maxm];
int ti[maxm];
int ci[maxm];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , m )
		scanf( pi[i] ) , scanf( qi[i] ) , scanf( ti[i] ) , scanf( ci[i] ) ;
}

int Ct;
int Ht[maxn];
int Nt[maxe];
int to[maxe];
int Dt[maxe];
int cap[maxe];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; Dt[Ct] = z ;
}

void build_edge1(){
	For( i , 1 , m )
		Ins( pi[i] , qi[i] , ti[i] ) ;
}

int dis[maxn];

void spfa(){
	static int que[mod + 50];
	static bool V[maxn];
	memset( V , 0 , sizeof V ) ;
	memset( dis , 0x3f , sizeof dis ) ;
	int head = 0 , tail = 0 ;
	que[ ++tail ] = 1 ; dis[1] = 0 ;
	while( head != tail ){
		int x = que[ ++head &= mod ] ; V[x] = false;
		Rep( i , Ht[x] , Nt[i] )
			if( dis[to[i]] > dis[x] + Dt[i] ){
				dis[to[i]] = dis[x] + Dt[i];
				if( !V[to[i]] )
					V[to[i]] = true , que[ ++tail &= mod ] = to[i] ;
			}
	}
	printf("%d\n" , dis[n] ) ;
}

void Ins( int x , int y , int p , int q ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = p ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = q ;
}

void build_edge2(){
	Ct = 1 ; memset( Ht , 0 , sizeof Ht ) ;
	S = 1 ; T = n ;
	For( i , 1 , m )
		if( dis[pi[i]] - dis[qi[i]] == ti[i] )
			Ins( qi[i] , pi[i] , ci[i] , 0 ) ;
		else if( dis[pi[i]] - dis[qi[i]] == -ti[i] )
			Ins( pi[i] , qi[i] , ci[i] , 0 ) ;
}

int cur[maxn];
int dep[maxn];

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = 0 ;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head != tail ){
		int x = que[ ++head ] ;
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
	return 0 ;
}

int dinic(){
	int res = 0 , t ;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = dfs( S , inf ) )res += t ;
	}
	return res ;
}

int main(){
	
	read_in();
	
	build_edge1();
	
	spfa();
	
	build_edge2();
	
	printf("%d\n" , dinic() );
	
	return 0;
}
