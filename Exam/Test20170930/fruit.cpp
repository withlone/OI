#include<cstdio>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )
#define FOR( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define LOP( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define REP( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type max( const type& x , const type& y ) { return x > y ? x : y ; }
template < typename type >
inline type min( const type& x , const type& y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , const type& y ) {
	return x >= y ? false : x = y , true ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x <= y ? false : x = y , true ;
}

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 1e5 + 19 ;

int n ;
int m ;

int a[maxn] ;

inline bool chk( LL x ) {
	int ps = 1 ;
	FOR( i , 1 , m ) {
		LL t = x ;
		while( ps <= n && t >= a[ps] )
			t -= a[ps] , ++ps ;
		if( ps > n )return true ;
	}
	return false ;
}

int main() {
	
	freopen( "fruit.in" , "r" , stdin ) ;
	freopen( "fruit.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ;
	FOR( i , 1 , n )scanf( a[i] ) ;
	
	LL l = 0 , r = 1e15 , ans ;
	while( l <= r ) {
		LL mid = l + r >> 1 ;
		if( chk( mid ) )ans = mid , r = mid - 1 ;
		else l = mid + 1 ;
	}
	
	printf( "%lld\n" , ans ) ;
	
	return 0 ;
}
