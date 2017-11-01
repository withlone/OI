#include<cstdio>

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

template < typename tp >
inline tp max( const tp& x , const tp& y ) { return x > y ? x : y ; }
template < typename tp >
inline tp min( const tp& x , const tp& y ) { return x < y ? x : y ; }
template < typename tp >
inline bool chkmax( tp& x , const tp& y ) {
	return x >= y ? false : ( x = y , true ) ;
}
template < typename tp >
inline bool chkmin( tp& x , const tp& y ) {
	return x <= y ? false : ( x = y , true ) ;
}
template < typename tp >
inline tp abs( const tp& x ) { return x > 0 ? x : -x ; }

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 5e5 + 11 ;
static const int maxm = 1e6 + 11 ;
static const double eps = 1e-10 ;

inline int cmp( const double& x , const double& y ) {
	return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ;
}

int n ;

int ci[maxn] ;
int di[maxn] ;
int Fa[maxn] ;

double ans[maxn] ;

int tp[maxn] ;
int stack[maxn] ;
int pre[maxn][20] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins( int x , int y ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

void dfs1( int x ) {
	di[x] = di[Fa[x]] + 1 ;
	REP( i , Ht[x] , Nt[i] )
		dfs1( to[i] ) ;
}

inline double slope( int x , int y ) {
	return ( ci[y] - ci[x] ) * 1.0 / ( di[y] - di[x] ) ;
}

void dfs2( int x ) {
	int t , p ;
	ans[x] = slope( Fa[x] , x ) ;
	p = t = x ; pre[x][0] = Fa[x] ;
	FOR( i , 1 , 19 )
		pre[x][i] = pre[ pre[x][i - 1] ][i - 1] ;
	LOP( i , 19 , 0 ) if( pre[t][i] && pre[ pre[t][i] ][0] ) {
		int t2 = pre[t][i] , t1 = pre[t2][0] ;
		if( cmp( slope( t1 , x ) , slope( t2 , x ) ) == 1 )
			ans[x] = slope( t1 , x ) , t = t2 ;
		if( cmp( slope( t1 , t2 ) , slope( t2 , x ) ) == 1 )
			p = t2 ;
	}
	pre[x][0] = pre[p][0] ;
	FOR( i , 1 , 19 )
		pre[x][i] = pre[ pre[x][i - 1] ][i - 1] ;
	REP( i , Ht[x] , Nt[i] )
		dfs2( to[i] ) ;
}

int main() {
	
	freopen( "lost.in" , "r" , stdin ) ;
	freopen( "lost.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	FOR( i , 1 , n ) scanf( ci[i] ) ;
	FOR( i , 2 , n ) ins( scanf( Fa[i] ) , i ) ;
	
	dfs1( 1 ) ; dfs2( 1 ) ;
	
	FOR( i , 2 , n ) printf( "%.10lf\n" , -ans[i] ) ;
	
	return 0 ;
}
