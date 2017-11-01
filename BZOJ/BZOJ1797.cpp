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

static const int maxn = 4e3 + 10;
static const int maxm = 12e4 + 10;
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;

int start_point[maxm];
int end_point[maxm];
int cost_point[maxm];

void read_in(){
	scanf( n ) ; scanf( m ) ; scanf( S ) ; scanf( T ) ;
	For( i , 1 , m )
		scanf( start_point[i] ) , scanf( end_point[i] ) , scanf( cost_point[i] ) ;
}

int Ct = 1 ;
int Ht[maxn];
int Nt[maxm];
int to[maxm];
int cap[maxm];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

void build_edge(){
	For( i , 1 , m )
		Ins( start_point[i] , end_point[i] , cost_point[i] ) ;
}

int cur[maxn];
int dep[maxn];

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = 0 ;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head != tail ){
		int x = que[ ++head ];
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[to[i]] && cap[i] ){
				dep[to[i]] = dep[x] + 1 ;
				if( to[i] == T )return true;
				que[ ++tail ] = to[i] ;
			}
	}
	return false;
}

int dfs( int x , int maxflow ){
	if( x == T )return maxflow ;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[to[i]] == dep[x] + 1 && cap[i] ){
			int t = dfs( to[i] , min( maxflow , cap[i] ) ) ;
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0 ;
}

int dinic(){
	int res = 0 , t;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = dfs( S , inf ) ) res += t ;
	}
	return res ;
}

bool V[maxn];

int tp;
int stack[maxn];

int dt;
int dfn[maxn];
int Low[maxn];

int cnt;
int bel[maxn];

void tarjan( int x ){
	int y ;
	V[x] = true ; stack[ ++tp ] = x ;
	dfn[x] = Low[x] = ++dt ;
	Rep( i , Ht[x] , Nt[i] )if( cap[i] ){
		y = to[i] ;
		if( !dfn[y] )tarjan ( y ) , Low[x] = min( Low[x] , Low[y] ) ;
		else if( V[y] )Low[x] = min( Low[x] , dfn[y] ) ;
	}
	if( dfn[x] != Low[x] )return;
	++cnt;
	do{
		y = stack[ tp-- ];
		V[y] = false;
		bel[y] = cnt;
	}while( x != y );
}

void display(){
	For( i , 1 , m )
		if( cap[i << 1] )puts("0 0") ;
		else{
			bool t1 = ( bel[ start_point[i] ] != bel[ end_point[i] ] ) ;
			bool t2 = ( bel[S] == bel[ start_point[i] ] && bel[T] == bel[ end_point[i] ] ) ;
			printf("%d %d\n" , t1 , t2 );
		}
}

void Run(){
	For( i , 1 , n )if( !dfn[i] )
		tarjan( i ) ;
	display();
}

int main(){
	
	read_in();
	
	build_edge();
	
	dinic();
	
	Run();
	
	return 0 ;
}
