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

static const int maxn = 850 + 10 ;
static const int maxm = 17000 + 10 ;
static const int inf = ~0U >> 1 ;

int n ;
int m ;
int S ;
int T ;

int dep[maxn] ;
int cur[maxn] ;
int que[maxn] ;

int at ;
int ans[maxn] ;

int qvq[maxn] ;
int qt[maxn] ;

int Ct = 1 ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;
int cap[maxm] ;

void ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = z ;
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

void diver( int l , int r ){
	if( l == r )return ;
	For( i , 2 , Ct )
		cap[i] = cap[i ^ 1] = cap[i] + cap[i ^ 1] >> 1 , ++i ;
	S = qvq[l] ; T = qvq[r] ;
	ans[ ++at ] = dinic() ;
	int ql = l , qr = r ;
	For( i , l , r )
		if( dep[ qvq[i] ] )qt[ ql++ ] = qvq[i] ;
		else qt[ qr-- ] = qvq[i] ;
	For( i , l , r )
		qvq[i] = qt[i] ;
	diver( l , ql - 1 ) ;
	diver( qr + 1 , r ) ;
}

int main(){
	
	scanf( n ) ; scanf( m ) ;
	
	For( i , 1 , n )qvq[i] = i ;
	
	For( i , 1 , m ){
		int x , y , z ;
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		ins( x , y , z ) ;
	}
	
	diver( 1 , n ) ;
	
	sort( 1 + ans , 1 + at + ans ) ;
	
	printf("%d\n" , unique( 1 + ans , 1 + at + ans ) - ans - 1 ) ;
	
	return 0 ;
}
