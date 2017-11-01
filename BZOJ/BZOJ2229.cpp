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

static const int maxn = 150 + 10;
static const int maxm = 3e3 + 10;
static const int maxq = 30 + 10;
static const int maxe = maxm << 1;
static const int inf = ~0U >> 1;

int cases;

int n;
int m;
int q;
int S;
int T;

int start_point[maxm];
int end_point[maxm];
int cost_path[maxm];

int query_limit[maxq];

int min_cut[maxn][maxn];

void read_cases_number(){
	scanf( cases ) ;
}

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , m )
		scanf( start_point[i] ) , scanf( end_point[i] ) , scanf( cost_path[i] ) ;
	scanf( q ) ;
	For( i , 1 , q )
		scanf( query_limit[i] ) ;
}

int Ct ;
int Ht[maxn];
int Nt[maxe];
int to[maxe];
int cap[maxe];

void Ins( int x , int y , int p , int q = 0 ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = p ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = q ;
}

int dq[maxn];
int qt[maxn];

void preparation(){
	Ct = 1 ; memset( Ht , 0 , sizeof Ht ) ;
	memset( min_cut , 0x3f , sizeof min_cut ) ;
	For( i , 1 , n )dq[i] = i ;
}

void build_edge(){
	For( i , 1 , m )
		Ins( start_point[i] , end_point[i] , cost_path[i] , cost_path[i] );
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
	int res = 0 , t ;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur ) ;
		while( t = dfs( S , inf ) )res += t ;
	}
	return res ; 
}

void update_edge(){
	For( i , 2 , Ct )
		cap[i] = cap[i ^ 1] = cap[i] + cap[i ^ 1] >> 1 , ++i ;
}

void run( int l , int r ){
	
	if( l == r )return;
	
	update_edge();
	
	S = dq[l] ; T = dq[r] ;
	
	int flow = dinic() ;
	
	For( i , 1 , n )
		if( dep[i] )
			For( j , 1 , n )
				if( !dep[j] )
					min_cut[i][j] = min_cut[j][i] = min( min_cut[i][j] , flow ) ;
	
	int pl = l , pr = r ;
	
	For( i , l , r )
		if( dep[ dq[i] ] )qt[ pl++ ] = dq[i] ;
		else qt[ pr-- ] = dq[i] ;
	
	For( i , l , r )dq[i] = qt[i] ;
	
	run( l , pl - 1 ) ;
	run( pr + 1 , r ) ;
	
}

int calc( int x ){
	int res = 0 ;
	For( i , 1 , n )
		For( j , i + 1 , n )
			if( min_cut[i][j] <= x )
				res++ ;
	return res ;
}

void display(){
	For( i , 1 , q )
		printf("%d\n" , calc( query_limit[i] ) );
}

int main(){
	
	bool blank_line_need = false ;
	
	read_cases_number();
	
	while( cases-- ){
		
		if( blank_line_need )putchar( '\n' ) ; else blank_line_need = true ;
		
		read_in();
		
		preparation();
		
		build_edge();
		
		run( 1 ,   n );
		
		display();
		
	}
	
	return 0 ;
}
