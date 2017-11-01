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

static const int maxn = 1e3 + 10 ;

int n ;
int s ;

double f[maxn][maxn] ;

int main() {
	
	scanf( n ) ; scanf( s ) ;
	
	Lop( i , n , 0 ) Lop( j , s , 0 ) if( i != n || j != s )
		f[i][j] = ( ( n - i ) * j * f[i + 1][j] +
					i * ( s - j ) * f[i][j + 1] +
					( n - i ) * ( s - j ) * f[i + 1][j + 1] 
					+ n * s ) / ( n * s - i * j ) ;
	
	printf("%.4lf\n" , f[0][0] ) ;
	
	return 0 ;
}
