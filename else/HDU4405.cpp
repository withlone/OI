#include<cstdio>
#include<cstring>

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

static const int maxn = 1e5 + 10 ;

int n ;
int m ;

int route[maxn] ;

double f[maxn] ;

int main() {
	
	register int x , y ;
	
	while( scanf( "%d%d" , &n , &m ) != EOF , n + m ) {
		For( i , 1 , m )
			route[ scanf( x ) ] = scanf( y ) ;
		Lop( i , n - 1 , 0 )
			if( route[i] )f[i] = f[ route[i] ] ;
			else
				f[i] = ( 1.0 / 6.0 ) * 
				( f[i + 1] + f[i + 2] + f[i + 3] 
				+ f[i + 4] + f[i + 5] + f[i + 6] ) + 1.0 ;
		printf( "%.4lf\n" , f[0] ) ;
		memset( route , 0 , sizeof(int) * (n + 1) ) ;
		memset( f , 0 , sizeof(double) * (n + 1) ) ;
	}
	
	return 0 ;
}
