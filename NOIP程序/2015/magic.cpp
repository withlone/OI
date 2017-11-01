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

static const int maxn = 43 ;

int n ;

int ai[maxn][maxn] ;

int main() {
	
	freopen( "magic.in" , "r" , stdin ) ;
	freopen( "magic.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	
	int x = 1 , y = ( n >> 1 ) + 1 ;
	FOR( I , 1 , n * n ) {
		ai[x][y] = I ;
		if( x == 1 && y != n )
			x = n , y++ ;
		else if( x != 1 && y == n )
			--x , y = 1 ;
		else if( x == 1 && y == n )
			++x ;
		else if( !ai[x - 1][y + 1] )
			x-- , y++ ;
		else ++x ;
	}
	
	For( i , 1 , n ) {
		FOR( j , 1 , n )
			printf( "%d " , ai[i][j] ) ;
		putchar( 10 ) ;
	}
	
	return 0 ;
}
