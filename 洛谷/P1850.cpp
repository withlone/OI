#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }
template < typename type >
inline type abs( type x ){ return x > 0 ? x : -x ; } 

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 2e3 + 10 ;
static const int maxx = 300 + 10 ;
static const double eps = 1e-10 ;

inline int cmp( double x , double y ) {
	return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ;
}

inline int min( int x , int y ){ return x < y ? x : y ; }
inline double min( double x , double y ){ return cmp( x , y ) == -1 ? x : y ; }

int n ;
int m ;
int v ;
int e ;

int ci[maxn] ;
int di[maxn] ;
double ki[maxn] ;

int dis[maxn][maxn] ;
double f[maxn][maxn][2] ;

int main() {
	
	register int x , y , z ;
	
	scanf( n ) ; scanf( m ) ; scanf( v ) ; scanf( e ) ;
	
	For( i , 1 , n )scanf( ci[i] ) ;
	For( i , 1 , n )scanf( di[i] ) ;
	For( i , 1 , n )scanf( "%lf" , &ki[i] ) ;
	
	memset( dis , 0x3f , sizeof dis ) ;
	
	For( i , 1 , e ) {
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		dis[x][y] = dis[y][x] = min( dis[x][y] , z ) ;
	}
	
	For( i , 0 , v )dis[i][i] = 0 ;
	
	For( k , 1 , v ) For( i , 1 , v ) For( j , 1 , v )
		chkmin( dis[i][j] , dis[i][k] + dis[k][j] ) ;
	
	memset( f , 0x7f , sizeof f ) ;
	f[1][0][1] = f[1][1][0] = 0.0 ;
	For( i , 2 , n ) {
		f[i][0][1] = f[i - 1][0][1] + dis[ci[i - 1]][ci[i]] ;
		For( j , 1 , min( i , m ) ) {
			f[i][j][1] =
			min( f[i - 1][j][0] + dis[di[i - 1]][ci[i]] * ki[i - 1] +
			dis[ci[i - 1]][ci[i]] * ( 1 - ki[i - 1] )
			, f[i - 1][j][1] + dis[ci[i - 1]][ci[i]] ) ;
			f[i][j][0] = min(
			f[i - 1][j - 1][1] +
			ki[i] * dis[ci[i - 1]][di[i]] +
			( 1 - ki[i] ) * dis[ci[i - 1]][ci[i]] ,
			f[i - 1][j - 1][0] +
			dis[di[i - 1]][di[i]] * ki[i - 1] * ki[i] +
			dis[ci[i - 1]][di[i]] * ( 1 - ki[i - 1] ) * ki[i] +
			dis[di[i - 1]][ci[i]] * ki[i - 1] * ( 1 - ki[i] ) +
			dis[ci[i - 1]][ci[i]] * ( 1 - ki[i - 1] ) * ( 1 - ki[i] ) ) ;
		}
	}
	double ans = 1e16 ;
	
	For( j , 0 , m ) For( k , 0 , 1 )
		if( ans - f[n][j][k] > eps )ans = f[n][j][k] ;
	
	printf( "%.2lf\n" , ans ) ;
	
	return 0 ;
}
