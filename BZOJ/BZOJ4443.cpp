#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) \
for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

static const int maxn = 250 + 10 ;
static const int maxx = maxn << 1 ;
static const int maxm = maxn * maxn + maxn * 2 << 1 ;
static const int inf = ~0U >> 1 ;

int n ;
int m ;
int k ;
int S ;
int T ;

int top_limit ;
int bottom_limit ;

int mat[maxn][maxn] ;

int cur[maxx] ;
int dep[maxx] ;
int que[maxx] ;

int Ct = 1 ;
int Ht[maxx] ;
int Nt[maxm] ;
int to[maxm] ;
int cap[maxm] ;

void ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

bool bfs(){
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

bool chk( int x ){
	Ct = 1 ; memset( Ht , 0 , sizeof Ht ) ;
	For( i , 1 , n )
		ins( S , i , 1 ) ;
	For( i , 1 , m )
		ins( i + n , T , 1 ) ;
	For( i , 1 , n )For( j , 1 , m )
		if( mat[i][j] <= x )
			ins( i , j + n , 1 ) ;
	return dinic() >= k ;
}

int main(){
	
	bottom_limit = inf ;
	
	scanf( n ) ; scanf( m ) ; scanf( k ) ;
	k = n - k + 1 ;
	
	S = 0 ; T = n + m + 1 ;
	
	For( i , 1 , n )For( j , 1 , m )
		scanf( mat[i][j] ) ,
		top_limit = max( top_limit , mat[i][j] ) ,
		bottom_limit = min( bottom_limit , mat[i][j] ) ;
	
	int l = bottom_limit , r = top_limit , ans = -1 ;
	while( l <= r ){
		int mid = l + r >> 1 ;
		if( chk( mid ) )ans = mid , r = mid - 1 ;
		else l = mid + 1 ;
	}
	
	printf("%d\n" , ans ) ;
	
	return 0 ;
}
