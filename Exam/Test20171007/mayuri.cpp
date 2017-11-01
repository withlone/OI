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
	return ( x >= y ) ? ( false ) : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return ( x <= y ) ? ( false ) : ( x = y , true ) ;
}

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e5 + 19 ;

int cases ;
int n ;
int m ;

inline int ceil( double x ) {
	return (int)x + ( ( x - (int)x ) > 0.0 ) ;
}

int main() {
	
	freopen( "mayuri.in" , "r" , stdin ) ;
	freopen( "mayuri.out" , "w" , stdout ) ;
	
	scanf( cases ) ;
	
	while( cases-- ) {
		scanf( n ) ; scanf( m ) ;
		if( m == 1 ) { printf( "%d\n" , n ) ; continue ; }
		int x = 0 ;
		for( int i = 2 ; i <= n ; ++i ) {
			int k = ceil( ( i - x - 1 ) * 1.0 / ( m - 1 ) ) - 1 ;
			chkmax( k , 0 ) ;
			if( i + k > n ) k = n - i ;
			i += k ;
			x = ( x + ( k + 1 ) * m ) % i ;
		}
		printf( "%d\n" , x + 1 ) ;
	}
	
	return 0 ;
}
