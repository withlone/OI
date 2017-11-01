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
inline type max( const type& x , const type& y ) { return x > y ? x : y ; }
template < typename type >
inline type min( const type& x , const type& y ) { return x < y ? x : y ; }
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

static const int maxn = 23 ;
static const int maxm = 4e2 + 9 ;

int n ;
int m ;

int ai[maxm] ;
int steps[maxn] ;
int ender[maxn] ;

int mc[maxn][maxn] ;
int tm[maxn][maxn] ;
bool use[maxn][maxm] ;

int main() {
	
	freopen( "jsp.in" , "r" , stdin ) ;
	freopen( "jsp.out" , "w" , stdout ) ;
	
	scanf( m ) ; scanf( n ) ;
	FOR( i , 1 , n * m )scanf( ai[i] ) ;	
	For( i , 1 , n ) FOR( j , 1 , m )scanf( mc[i][j] ) ;
	For( i , 1 , n ) FOR( j , 1 , m )scanf( tm[i][j] ) ;
	
	int ans = 0 ;
	For( i , 1 , n * m ) {
		int x = ai[i] , tot = 0 ;
		steps[x]++ ;
		int y = mc[x][steps[x]] ;
		For( j , ender[x] + 1 , 400 ) {
			if( use[y][j] )tot = 0 ;
			else ++tot ;
			if( tot == tm[x][steps[x]] ) {
				FOR( k , j - tot + 1 , j )use[y][k] = true ;
				chkmax( ender[x] , j ) ;
				chkmax( ans , ender[x] ) ;
				break ;
			}
		}
	}
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
