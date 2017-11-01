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

static const int maxn = 3e5 + 17 ;
static const int maxm = 6e5 + 43 ;
static const int maxx = 20 ;

int n ;
int m ;

int dep[maxn] ;
int Fa[maxn][maxx] ;
int dis[maxn][maxx] ;

int cnt[maxn] ;
int dist[maxn] ;

int Ct = 1 ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;
int Dt[maxm] ;
int head[maxm] ;

class transport {
	public :
		int x ;
		int y ;
		int lca ;
		int dist ;
		
		bool operator < ( const transport& t )
			const { return dist < t.dist ; }
} tran[maxn] ;

inline void ins( const int& x , const int& y , const int& z ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
}

void dfs( const int& x ) {
	REP( i , Ht[x] , Nt[i] ) if( to[i] != Fa[x][0] ) {
		dep[to[i]] = dep[x] + 1 ;
		Fa[to[i]][0] = x ;
		dis[to[i]][0] = Dt[i] ;
		dfs( to[i] ) ;
	}
}

inline pair < int , int > qlca( int x , int y ) {
	if( dep[x] < dep[y] )swap( x , y ) ;
	int delta = dep[x] - dep[y] , res = 0 ;
	FOR( i , 0 , 19 ) if( delta >> i & 1 )
		res += dis[x][i] , x = Fa[x][i] ;
	if( x == y )return make_pair( x , res ) ;
	LOP( i , 19 , 0 ) if( Fa[x][i] != Fa[y][i] )
		res += dis[x][i] + dis[y][i] ,
		x = Fa[x][i] , y = Fa[y][i] ;
	return make_pair( Fa[x][0] , res + dis[x][0] + dis[y][0] ) ;
}

void update( const int& x ) {
	REP( i , Ht[x] , Nt[i] ) if( to[i] != Fa[x][0] )
		update( to[i] ) , cnt[x] += cnt[to[i]] ;
}

inline bool chk( const int& x ) {
	int left = upper_bound( 1 + dist , 1 + m + dist , x ) - dist ;
	int best = dist[m] - x , tot = m - left + 1 ;
	memset( cnt , 0 , sizeof(int) * (n + 1) ) ;
	FOR( i , left , m )
		cnt[ tran[i].x ]++ , cnt[ tran[i].y ]++ , cnt[ tran[i].lca ]-= 2 ;
	update( 1 ) ;
	FOR( i , 2 , Ct )
		if( cnt[ head[i] ] == tot && best <= Dt[i] )
			return true ;
		else ++i ;
	return false ;
}

int main() {
	
	freopen( "transport.in" , "r" , stdin ) ;
	freopen( "transport.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ;
	FOR( i , 1 , n - 1 ) {
		register int x , y , z ;
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		ins( x , y , z ) , ins( y , x , z ) ;
	}
	
	FOR( i , 1 , m ) scanf( tran[i].x ) , scanf( tran[i].y ) ;
	
	dfs( 1 ) ;
	
	For( j , 1 , 19 ) FOR( i , 1 , n )
		Fa[i][j] = Fa[ Fa[i][j - 1] ][j - 1] ,
		dis[i][j] = dis[i][j - 1] + dis[ Fa[i][j - 1] ][j - 1] ;
	
	FOR( i , 1 , m ) {
		pair < int , int > x = qlca( tran[i].x , tran[i].y ) ;
		tran[i].lca = x.first ; tran[i].dist = x.second ;
	}
	
	sort( 1 + tran , 1 + m + tran ) ;
	
	FOR( i , 1 , m ) dist[i] = tran[i].dist ;
	
	FOR( i , 2 , Ct )
		if( dep[to[i]] > dep[to[i ^ 1]] )head[i] = to[i] ;
		else head[i] = to[i ^ 1] ;
	
	int l = 0 , r = dist[m] , ans ;
	while( l <= r ) {
		int mid = l + r >> 1 ;
		if( chk( mid ) ) r = mid - 1 , ans = mid ;
		else l = mid + 1 ;
	}
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
