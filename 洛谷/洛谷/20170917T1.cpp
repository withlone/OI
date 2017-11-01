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
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;

LL AND ;
LL OR ;
LL SUM ;

LL a ;
LL b ;
LL c ;

int main() {
	
	while( scanf( "%lld%lld%lld" , &AND , &OR , &SUM ) != EOF ) {
		a = b = c = AND ; OR ^= AND ;
		SUM -= AND * 3 + OR ;
		b |= OR & SUM ;
		c |= OR ;
		printf("%lld %lld %lld\n" , a , b , c ) ;
	}
	
	return 0 ;
}
