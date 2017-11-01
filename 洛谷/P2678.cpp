#include<cstdio>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template < typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }
template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 5e4 + 10 ;

int L ;
int n ;
int m ;

int stone[maxn] ;

inline bool chk( int x ) {
	int res = 0 , lst = stone[0] ;
	For( i , 1 , n )
		if( stone[i] - lst < x )++res ;
		else lst = stone[i] ;
	return res <= m ;

}

int main() {
	
	scanf( L ) ; scanf( n ) ; scanf( m ) ;
	
	stone[0] = 0 ;
	For( i , 1 , n )scanf( stone[i] ) ;
	stone[ ++n ] = L ;
	
	int l = 1 , r = 1e9 , ans ;
	while( l <= r ) {
		int mid = l + r >> 1 ;
		if( chk( mid ) )ans = mid , l = mid + 1 ;
		else r = mid - 1 ;
	}
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
