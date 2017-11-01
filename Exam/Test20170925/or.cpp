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

template < typename type >
inline type max( type x , type y ) { return x > y ? x : y ; }
template < typename type >
inline type min( type x , type y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , type y ) { return x > y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , type y ) { return x < y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e6 + 3 ;
static const int mod = 1e9 + 7 ;

int n ;

int a[maxn] ;

int f[maxn][2][2] ;
int g[maxn][2][2] ;

inline int add( int x , const int& y ) {
	x += y ; if( x >= mod ) x -= mod ; return x ;
}

inline int calc( const int& x , const int& y , const int& z ) {
	if( !y )return 0 ;
	if( x == z )return 1 ;
	if( x > z )return 0 ;
	return -1 ;
}

int main() {
	
	freopen( "or.in" , "r" , stdin ) ;
	freopen( "or.out" , "w" , stdout ) ;
	
	register int x , y ;
	
	scanf( n ) ;
	FOR( i , 1 , n )scanf( "%1d" , &a[i] ) ;
	
	g[0][1][1] = 1 ;
	For( i , 1 , n ) For( j , 0 , 1 ) FOR( k , 0 , 1 )
		if( g[i - 1][j][k] )
			For( p , 0 , 1 ) For( q , 0 , 1 ) {
				x = calc( a[i] , j , p ) ; y = calc( p , k , q ) ;
				if( x != -1 && y != -1 ) {
					f[i][x][y] = add( f[i][x][y] , f[i - 1][j][k] ) ;
					g[i][x][y] = add( g[i][x][y] , g[i - 1][j][k] ) ;
					if( p | q )
						f[i][x][y] = add( f[i][x][y] , g[i - 1][j][k] ) ;
				}
			}
	
	int ans = 0 ;
	For( i , 0 , 1 ) FOR( j , 0 , 1 )
		ans = add( ans , f[n][i][j] ) ;
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
