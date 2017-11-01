#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std ;

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) \
for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

static const int maxn = 100 + 10 ;
static const int maxx = 1e4 + 10 ;
static const int maxm = 1e6 + 10 ;
static const int inf = ~0U >> 1 ;

int n ;
int m ;
int S ;
int T ;
int dt ;
int cnt ;
int ans ;

int a[maxn] ;
int d[maxn][maxn] ;

int dir[maxn] ;
int num[maxn][maxn] ;

int cur[maxx] ;
int que[maxx] ;
int dep[maxx] ;

int Ct = 1 ;
int Ht[maxx] ;
int Nt[maxm] ;
int to[maxm] ;
int cap[maxm] ;

void ins( int x , int y , int z ){
	if( !z )return ;
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

int main(){
	
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )scanf( a[i] ) , dir[ ++dt ] = a[i] ;
	For( i , 1 , n )cnt = max( cnt , a[i] ) ;
	For( i , 1 , n )For( j , i , n )
		scanf( d[i][j] ) ;
	
	sort( 1 + dir , 1 + dt + dir ) ;
	dt = unique( 1 + dir , 1 + dt + dir ) - dir - 1 ;
	
	For( i , 1 , n )For( j , i , n )
		num[i][j] = ++cnt ;
	
	S = 0 ; T = ++cnt ;
	
	For( i , 1 , dt )
		ins( dir[i] , T , m * dir[i] * dir[i] ) ;
	
	For( i , 1 , n )
		ins( num[i][i] , a[i] , inf ) ,
		ins( num[i][i] , T , a[i] ) ;
	
	For( i , 1 , n )For( j , i , n ){
		if( d[i][j] > 0 )ins( S , num[i][j] , d[i][j] ) , ans += d[i][j] ;
		else ins( num[i][j] , T , -d[i][j] ) ;
		if( i == j )continue ;
		For( k , i , j )ins( num[i][j] , num[k][k] , inf ) ;
		if( num[i + 1][j] )ins( num[i][j] , num[i + 1][j] , inf ) ;
		if( num[i + 1][j] == num[i][j - 1] )continue ;
		if( num[i][j - 1] )ins( num[i][j] , num[i][j - 1] , inf ) ;
	}
	
	printf("%d\n" , ans - dinic() ) ;
	
	return 0 ;
}
