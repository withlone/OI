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
	return ( x >= y ) ? false : ( x = y , true ) ;
}
template < typename tp >
inline bool chkmin( tp& x , const tp& y ) {
	return ( x <= y ) ? false : ( x = y , true ) ;
}

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e5 + 11 ;

int n ;
int m ;
int ps ;
int sp ;
bool flag ;

int ai[maxn] ;

void merge_sort( int l , int r ) {
	if( l == r - 1 || !m ) return ai[l] = --sp , void() ;
	int mid = l + r >> 1 ;
	if( !( m -= 2 ) ) {
		FOR( i , mid , r - 1 ) ai[i] = ++ps ;
		FOR( i , l , mid - 1 ) ai[i] = ++ps ;
	} else {
		merge_sort( l , mid ) ;
		if( !m )
			FOR( i , mid , r - 1 ) ai[i] = ++ps ;
		else
			merge_sort( mid , r ) ;
	}
}

int main() {
	
	scanf( n ) ; scanf( m ) ;
	sp = n + 1 ;
	
	if( --m & 1 ) return puts( "-1" ) , 0 ;
	if( !m ) {
		FOR( i , 1 , n ) printf( "%d " , i ) ;
		putchar( 10 ) ;
		return 0 ;
	}
	
	merge_sort( 0 , n ) ;
	
	if( m || flag ) puts( "-1" ) ;
	else {
		FOR( i , 0 , n - 1 ) printf( "%d " , ai[i] ) ;
		putchar( 10 ) ;
	}
	
	return 0 ;
}
