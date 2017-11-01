#include<cstdio>
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

template < typename tp >
inline bool chkmax( tp& x , const tp& y )
	{ return ( x >= y ) ? false : ( x = y , true ) ; }
template < typename tp >
inline bool chkmin( tp& x , const tp& y )
	{ return ( x <= y ) ? false : ( x = y , true ) ; }

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e3 + 9 ;

int n ;
int m ;
int ans ;

int xi[maxn] ;

int ri[maxn][maxn] ;

char mat[maxn][maxn] ;

int main() {
	
	freopen( "matrix.in" , "r" , stdin ) ;
	freopen( "matrix.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ;
	FOR( i , 1 , n ) scanf( "%s" , mat[i] + 1 ) ;
	
	For( i , 1 , n ) FOR( j , 1 , m ) mat[i][j] -= '0' ;
	
	For( i , 1 , n ) {
		int first = 0 ;
		LOP( j , m , 1 )
			if( !mat[i][j] ) first = 0 ;
			else {
				if( !first ) first = j ;
				ri[i][j] = first ;
			}
	}
	
	For( i , 1 , m ) {
		FOR( j , 1 , n ) xi[j] = ri[j][i] ;
		sort( 1 + xi , 1 + n + xi ) ;
		int t = 1 ;
		FOR( j , i , m ) {
			while( xi[t] < j && t <= n ) ++t ;
			if( t == n + 1 ) break ;
			chkmax( ans , ( j - i + 1 ) * ( n - t + 1 ) ) ;
		}
	}
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
