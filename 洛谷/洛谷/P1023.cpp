#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

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
static const int inf = ~0U >> 1 ;

int n ;
int Num ;
int Sale ;
int temp ;
int extra ;

int sale[maxn] ;
int num[maxn] ;

int top ;
int bottom ;

inline int get( int x1 , int y1 , int x2 , int y2 ) {
	return ( y1 - y2 ) / ( x1 - x2 ) ;
}

inline void error() { puts( "NO SOLUTION" ) ; exit( 0 ) ; }

int main() {
	
	scanf( Sale ) ;
	
	while( ++n , scanf( sale[n] ) + scanf( num[n] ) != -2 ) ;
	scanf( extra ) ;
	
	sale[n] = sale[n - 1] + num[n - 1] / extra ;
	num[n] = num[n - 1] % extra ;
	
	bottom = -inf ; top = inf ;
	
	if( Sale > sale[n] )error() ;
	int pos = upper_bound( 1 + sale , 1 + n + sale , Sale ) - sale - 1 ;
	
	int k = get( sale[pos] , num[pos] , sale[pos + 1] , num[pos + 1] ) ;
	int number = num[pos] + k * ( Sale - sale[pos] ) ;
	int calc = number * ( Sale - sale[1] ) ;
	
	For( i , 1 , n - 1 ) {
		k = get( sale[i] , num[i] , sale[i + 1] , num[i + 1] ) ;
		int temp = num[i] ;
		For( j , sale[i] , sale[i + 1] - 1 + ( i == n - 1 ) ) {
			int _calc = ( j - sale[1] ) * temp ;
			double t = ( _calc - calc ) * 1.0 / ( number - temp ) ;
			if( number == temp ) {
				if( calc < _calc )printf( "%d\n" , j ) , error() ;
			} else if( number > temp )
				chkmax( bottom , (int)ceil( t ) ) ;
			else
				chkmin( top , (int)floor( t ) ) ;
			temp += k ;
		}
	}
	if( bottom > top )error() ;
	
	printf( "%d\n" , abs( bottom ) > abs( top ) ? top : bottom ) ;
	
	return 0 ;
}
