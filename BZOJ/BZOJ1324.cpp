#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) \
for( int i = (_Begin) ; i ; i = (_Add) )

#define debug(...) fprintf( stderr , __VA_ARGS__ )

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }

template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

static const int maxn = 1e2 + 10 ;
static const int maxx = 1e4 + 10 ;
static const int maxm = maxx << 3 ;
static const int inf = ~0U >> 1 ;

int n ;
int m ;
int S ;
int T ;

int ans ;

int gemstone_val[maxn][maxn] ;

int cnt ;
int num[maxn][maxn] ;

int Ct = 1 ;
int Ht[maxx] ;
int Nt[maxm] ;
int to[maxm] ;
int cap[maxm] ;

int cur[maxx] ;
int dep[maxx] ;

void ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )For( j , 1 , m )
		scanf( gemstone_val[i][j] ) ;
}

void get_tot_val(){
	For( i , 1 , n )For( j , 1 , m )
		ans += gemstone_val[i][j] ;
}

void preparation(){
	For( i , 1 , n )For( j , 1 , m )
		num[i][j] = ++cnt ;
}

void get_S_and_T(){
	S = 0 ; T = ++cnt ;
}

void edge_black_to_white(){
	For( i , 1 , n )For( j , 1 , m )if( ( i & 1 ) ^ ( j & 1 ) ){
		if( num[i - 1][j] )
			ins( num[i][j] , num[i - 1][j] , inf ) ;
		if( num[i + 1][j] )
			ins( num[i][j] , num[i + 1][j] , inf ) ;
		if( num[i][j - 1] )
			ins( num[i][j] , num[i][j - 1] , inf ) ;
		if( num[i][j + 1] )
			ins( num[i][j] , num[i][j + 1] , inf ) ;
	}
}

void edge_belong(){
	For( i , 1 , n )For( j , 1 , m )
		if( ( i & 1 ) ^ ( j & 1 ) )
			ins( S , num[i][j] , gemstone_val[i][j] ) ;
		else
			ins( num[i][j] , T , gemstone_val[i][j] ) ;
}

void build_edge(){
	
	get_S_and_T() ;
	
	edge_black_to_white() ;
	
	edge_belong() ;
	
}

bool bfs(){
	static int que[maxx] ;
	int head = 0 , tail = 0 ;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head != tail ){
		int x = que[ ++head ] ;
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[to[i]] && cap[i] ){
				dep[to[i]] = dep[x] + 1 ;
				if( to[i] == T )return true ;
				que[ ++tail ] = to[i] ;
			}
	}
	return false ;
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

void display(){
	get_tot_val() ;
	printf("%d\n" , ans - dinic() ) ;
}

int main(){
	
	read_in() ;
	
	preparation() ;
	
	build_edge() ;
	
	display() ;
	
	return 0 ;
}
