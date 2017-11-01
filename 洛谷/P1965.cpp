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

typedef long long LL ;
static const int maxn = 1e6 + 10 ;

int n ;
int m ;
int k ;
int x ;

int result ;
int circle ;

inline int qpow( int x , int y , int mod ) {
	int res = 1 ;
	for( ; y ; y >>= 1 , x = 1LL * x * x % mod )
		if( y & 1 ) res = 1LL * res * x % mod ;
	return res ;
}

inline int get_circle() {
	For( i , 1 , n )
		if( !( i * m % n ) )return i ;
}

int main() {
	
	scanf( n ) ; scanf( m ) ; scanf( k ) ; scanf( x ) ;
	
	circle = get_circle() ;
	
	result = qpow( 10 , k , circle ) ;
	
	printf( "%d\n" , ( x + (int)( 1LL * m * result % n ) ) % n ) ;
	
	return 0 ;
}
