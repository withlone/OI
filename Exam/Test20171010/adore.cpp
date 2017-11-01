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
inline bool chkmax( tp& x , const tp& y ) {
	return x >= y ? false : ( x = y , true ) ;
}
template < typename tp >
inline bool chkmin( tp& x , const tp& y ) {
	return x <= y ? false : ( x = y , true ) ;
}

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e4 + 11 ;
static const int maxx = ( 1 << 10 ) + 11 ;
static const int maxm = 13 ;
static const int mod = 998244353 ;

int n ;
int m ;

int edge[maxn][maxm][maxm] ;
int EDGE[maxn][maxm][maxm] ;

int p1[maxn][maxm] ;
int p2[maxn][maxm] ;

int f[maxx] ;
int g[maxx] ;

inline int lowbit( int x ) {
	int res = 0 ;
	for( ; x ; x &= x - 1 ) ++res ;
	return res ;
}

inline int add( int x , int y ) {
	x += y ; if ( x >= mod ) x -= mod ; return x ;
}

int main() {
	
	freopen( "adore.in" , "r" , stdin ) ;
	freopen( "adore.out" , "w" , stdout ) ;
	
	read_in :
		scanf( n ) ; scanf( m ) ;
		FOR( i , 1 , m ) scanf( edge[1][1][i] ) ;
		For( i , 2 , n - 2 ) For( x , 1 , m ) FOR( y , 1 , m )
			scanf( edge[i][x][y] ) ;
		FOR( i , 1 , m ) scanf( edge[n - 1][i][1] ) ;
	
		For( i , 2 , n - 2 ) For( x , 1 , m ) FOR( y , 1 , m )
			EDGE[i][x][y] = edge[i][y][x] ;
	
	init :
		FOR( i , 1 , m )
			p1[1][1] |= edge[1][1][i] << i - 1 ,
			p1[n - 1][i] = edge[n - 1][i][1] ,
			p1[n][1] |= edge[n - 1][i][1] << i - 1 ;
		For( i , 2 , n - 2 ) For( x , 1 , m ) FOR( y , 1 , m )
			p1[i][x] |= edge[i][x][y] << y - 1 ;
		FOR( i , 1 , m )
			p2[1][1] |= EDGE[1][1][i] << i - 1 ,
			p2[n - 1][i] = EDGE[n - 1][i][1] ;
		For( i , 2 , n - 2 ) For( x , 1 , m ) FOR( y , 1 , m )
			p2[i][x] |= EDGE[i][x][y] << y - 1 ;
	
	Main :
		f[ p1[1][1] ] = 1 ;
		For( i , 2 , n - 2 ) {
			memcpy( g , f , sizeof g ) ;
			memset( f , 0 , sizeof f ) ;
			For( sus , 0 , ( 1 << m ) - 1 ) if( g[sus] ) {
				int nxt = 0 ;
				FOR( j , 1 , m )
					if( sus >> j - 1 & 1 ) nxt ^= p1[i][j] ;
				f[nxt] = add( f[nxt] , g[sus] ) ;
				nxt = 0 ;
				FOR( j , 1 , m )
					if( sus >> j - 1 & 1 ) nxt ^= p2[i][j] ;
				f[nxt] = add( f[nxt] , g[sus] ) ;
			}
		}
	
	display :
		int ans = 0 ;
		For( sus , 0 , ( 1 << m ) - 1 )
			if( !( lowbit( sus & p1[n][1] ) & 1 ) )
				ans = add( ans , f[sus] ) ;
		
		printf( "%d\n" , ans ) ;
	
	return 0 ;
}
