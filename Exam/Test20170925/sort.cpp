#include<cstdio>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

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

static const int maxn = 5e6 + 10 ;

int n ;
int tp ;

int a[maxn] ;
int cnt[maxn] ;
int stack[maxn] ;

/*inline void wbrain() {
	int ans = 0 ;
	For( i , 1 , n ) {
		int res = 0 ;
		For( j , 1 , i - 1 )res += ( a[i] > a[j] ) ;
		ans += ( res < a[i] - 1 ) ;
	}
	printf( "%d\n" , ans ) ;
}
*/

int main() {
	
	freopen( "sort.in" , "r" , stdin ) ;
	freopen( "sort.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	For( i , 1 , n ) scanf( a[i] ) ;
	
	Lop( i , n , 1 ) {
		while( tp && a[i] < stack[tp] )--tp ;
		cnt[i] = tp ; stack[ ++tp ] = a[i] ;
	}
	
	int ans = 0 ;
	For( i , 1 , n )
		ans += ( cnt[i] > 0 ) ;
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
