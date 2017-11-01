#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )
#define FOR( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define LOP( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define REP( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline bool chkmax( type& x , const type& y ) {
	return x >= y ? false : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x <= y ? false : ( x = y , true ) ;
}

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 33 ;
static const int maxm = 907 ;
static const int inf = 1061109567 ;

template < typename type >
class queue {
	private :
		int head ;
		int tail ;
		type que[maxm] ;
	public :
		inline void clear() { head = tail = 0 ; }
		inline void push( type x ) { que[ ++tail ] = x ; }
		inline void pop() { ++head ; }
		inline bool empty() { return head == tail ; }
		inline type front() { return que[head + 1] ; }
} ;

class node {
	public :
		int x ;
		int y ;
		int z ;
		
		node() { x = y = z = 0 ; }
		node( int a , int b , int c ){ x = a ; y = b ; z = c ; }
} ;

int n ;
int m ;
int q ;

int ex ;
int ey ;
int sx ;
int sy ;
int tx ;
int ty ;

int mx[] = { 0 , 0 , 1 , -1 } ;
int my[] = { 1 , -1 , 0 , 0 } ;

int ai[maxn][maxn] ;
bool V[maxn][maxn] ;
int dis[maxn][maxn][4] ;

int f[maxn][maxn][4][maxn][maxn] ;

inline void bfs( int x , int y , int k , int dist[maxn][maxn] ) {
	memset( V , 0 , sizeof V ) ;
	V[x][y] = true ;
	V[x + mx[k]][y + my[k]] = true ; dist[x + mx[k]][y + my[k]] = 0 ;
	static queue < pair< int , int > > que ;
	que.clear() ; que.push( make_pair( x + mx[k] , y + my[k] ) ) ;
	pair < int , int > t , nxt ;
	while( !que.empty() ) {
		t = que.front() ; que.pop() ;
		FOR( i , 0 , 3 ) {
			nxt.first = t.first + mx[i] ; nxt.second = t.second + my[i] ;
			if( ai[nxt.first][nxt.second] && !V[nxt.first][nxt.second] ) {
				V[nxt.first][nxt.second] = true ;
				dist[nxt.first][nxt.second] = dist[t.first][t.second] + 1 ;
				que.push( nxt ) ;
			}
		}
	}
}

int main() {
	
	freopen( "puzzle.in" , "r" , stdin ) ;
	freopen( "puzzle.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ; scanf( q ) ;
	
	For( i , 1 , n ) FOR( j , 1 , m )
		scanf( ai[i][j] ) ;
	
	memset( f , 0x3f , sizeof f ) ;
	
	For( i , 1 , n ) For( j , 1 , m ) if( ai[i][j] )
		FOR( k , 0 , 3 ) if( ai[i + mx[k]][j + my[k]] )
			bfs( i , j , k , f[i][j][k] ) ;
	
	while( q-- ) {
		scanf( ex ) ; scanf( ey ) ;
		scanf( sx ) ; scanf( sy ) ;
		scanf( tx ) ; scanf( ty ) ;
		if( sx == tx && sy == ty ) { puts( "0" ) ; continue ; }
		static queue< node > que ; que.clear() ;
		memset( dis , 0x3f , sizeof dis ) ;
		FOR( i , 0 , 3 ) if( ai[sx + mx[i]][sy + my[i]] ) {
			dis[sx][sy][i] = f[sx][sy][i][ex][ey] + 1 ;
			que.push( node( sx , sy , i ) ) ;
		}
		node t , nxt ;
		while( !que.empty() ) {
			t = que.front() ; que.pop() ;
			nxt = node( t.x + mx[t.z] , t.y + my[t.z] , 0 ) ;
			FOR( i , 0 , 3 ) {
				nxt.z = i ;
				if( dis[nxt.x][nxt.y][nxt.z] >
				dis[t.x][t.y][t.z] + 1 + f[nxt.x][nxt.y][nxt.z][t.x][t.y] ) {
					dis[nxt.x][nxt.y][nxt.z] =
					dis[t.x][t.y][t.z] + 1 + f[nxt.x][nxt.y][nxt.z][t.x][t.y] ;
					que.push( nxt ) ;
				}
			}
		}
		int ans = inf ;
		FOR( i , 0 , 3 )
			chkmin( ans , dis[tx + mx[i]][ty + my[i]][i ^ 1] ) ;
		
		printf( "%d\n" , ans == inf ? -1 : ans ) ;
	}
	
	return 0 ;
}
