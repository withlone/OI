#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std ;

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template < typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }

template < typename type >
inline bool scanf( type& in ) {
	in = 0 ; char ch = getchar() ;
	for( ;ch> '9'||ch< '0';ch = getchar() )
		if( ch == 10 )return false ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return ch == 10 ? false : true ;
}

typedef long long LL ;
typedef unsigned long long ULL ;
static const int maxn = 1e2 + 10 ;
static const int maxm = 1e4 + 10 ;

int n ;
int cases ;
ULL limit ;

ULL number[maxn] ;

char type[maxn] ;

inline bool chk() {
	ULL t = 1ULL ;
	For( i , 1 , n )
		if( !number[i] ) return false ;
		else {
			double test = limit * 1.0 / number[i] ;
			if( 1.0 * t - test > 0 )return printf( "%d\n" , i ) , true ;
			t *= number[i] ;
		}
	return false ;
}

int main() {
	
	freopen( "overflow.in" , "r" , stdin ) ;
	freopen( "overflow.out" , "w" , stdout ) ;
	
	scanf( cases ) ;
	
	while( cases-- ) {
		scanf( "%s" , type ) ;
		if( !strcmp( type , "int8" ) )limit = 127 ;
		else if( !strcmp( type , "int16" ) )limit = 32767 ;
		else if( !strcmp( type , "int32" ) )limit = 2147483647 ;
		else if( !strcmp( type , "int64" ) )limit = 9223372036854775807 ;
		else {
			scanf( "%s" , type ) ;
			if( !strcmp( type , "int8" ) )limit = 255 ;
			else if( !strcmp( type , "int16" ) )limit = 65535 ;
			else if( !strcmp( type , "int32" ) )limit = 4294967295 ;
			else limit = 18446744073709551615ULL ;
		}
		n = 0 ;
		scanf( "\n" ) ;
		while( scanf( number[ ++n ] ) ) ;
		if( !chk() )puts( "never" ) ;
	}
	
	return 0 ;
}
