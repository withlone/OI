#include<cmath>
#include<cstdio>
#include<cstring>

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
inline bool chkmax( tp& x , const tp& y )
	{ return ( x >= y ) ? ( false ) : ( x = y , true ) ; }
template < typename tp >
inline bool chkmin( tp& x , const tp& y )
	{ return ( x <= y ) ? ( false ) : ( x = y , true ) ; }
template < typename tp >
inline tp abs( const tp& x ) { return x > 0 ? x : -x ; }

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() ) if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() ) in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 6e3 + 11 ;
static const int maxm = 19e6 + 13 ;
static const double eps = 1e-10 ;

inline int cmp( const double& x , const double& y ) {
	double res = x - y ;
	return abs( res ) < eps ? 0 : res > 0.0 ? 1 : -1 ;
}

int n ;
int m ;
int k ;
int K ;
int S ;
int T ;

int xi[maxn] ;
int yi[maxn] ;

int Fa[maxn] ;

double dt[maxm] ;

int f[maxn] ;
bool V[maxn] ;
double dis[maxn] ;

inline double sqr( const double& x ) { return x * x ; }

inline double dist( int x , int y ) {
	return sqrt( sqr( xi[x] - xi[y] ) + sqr( yi[x] - yi[y] ) ) / 2.0 ;
}

inline int get( int x , int y ) {
	if( x < y ) return ( ( K * x - x * x ) >> 1 ) + y ;
	return ( ( K * y - y * y ) >> 1 ) + x ;
}

inline int Find( int t ) {
	int fa = Fa[t] ;
	while( fa != Fa[fa] ) fa = Fa[fa] ;
	while( t != fa ) Fa[t] = fa , t = fa ;
	return t ;
}

int main() {
	
	freopen( "starway.in" , "r" , stdin ) ;
	freopen( "starway.out" , "w" , stdout ) ;
	
	read_in :
		scanf( n ) ; scanf( m ) ; scanf( k ) ; K = ( k << 1 ) + 3 ;
		FOR( i , 1 , k ) scanf( xi[i] ) , scanf( yi[i] ) ;
	
	get_edge :
		S = 0 ; T = k + 1 ;
		For( i , 1 , k - 1 ) FOR( j , i + 1 , k )
			dt[get( i , j )] = dist( i , j ) ;
		FOR( i , 1 , k )
			dt[i] = yi[i] / 2.0 , dt[get( i , k + 1 )] = ( m - yi[i] ) / 2.0 ;
		dt[k + 1] = m / 2.0 ;
	
	prim_prepartion :
		FOR( i , 1 , k + 1 ) Fa[i] = i , dis[i] = dt[i] ;
	
	prim :
		FOR( I , S , T ) {
			int t = -1 ; double mx = 1e9 ;
			FOR( i , S , T ) if( !V[i] && cmp( mx , dis[i] ) == 1 )
				mx = dis[ t = i ] ;
			Fa[ Find( t ) ] = Find( f[t] ) ;
			if( Find( 0 ) == Find( k + 1 ) ) {
				double mst = 0.0 ;
				for( register int i = T ; i != S ; i = f[i] )
					chkmax( mst , dt[get( i , f[i] )] ) ;
				return printf( "%.10lf\n" , mst ) , 0 ;
			}
			V[t] = true ;
			FOR( i , S , T )
				if( !V[i] && chkmin( dis[i] , dt[get( t , i )] ) )
					f[i] = t ;
		}
	
	return 0 ;
}
