#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )

template< typename type >
inline type scanf( type &in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 10 + 10 ;

int n ;
double p ;

int mine[maxn] ;

class matrix {
	public :
		double s[2][2] ;
		matrix(){ memset( s , 0 , sizeof s ) ; }
} ;

matrix operator * ( const matrix& x , const matrix& y ) {
	matrix res ;
	For( i , 0 , 1 ) For( j , 0 , 1 ) For( k , 0 , 1 )
		res.s[i][j] += x.s[i][k] * y.s[k][j] ;
	return res ;
}

matrix operator ^ ( const matrix& t , int y ) {
	matrix res , x = t ;
	res.s[0][0] = res.s[1][1] = 1.0 ;
	for( ; y ; y >>= 1 , x = x * x )
		if( y & 1 )res = res * x ;
	return res ;
}

matrix x ;
matrix res ;

inline bool chk() {
	For( i , 2 , n )
		if( mine[i] - mine[i - 1] == 1 )return false ;
	return mine[1] != 1 ;
}

int main() {
	
	x.s[0][0] = 0.0 ; x.s[1][0] = 1.0 ;
	
	while( scanf( "%d%lf" , &n , &p ) != EOF ) {
		x.s[0][1] = 1.0 - p ; x.s[1][1] = p ;
		For( i , 1 , n )scanf( mine[i] ) ;
		sort( 1 + mine , 1 + n + mine ) ;
		if( !chk() ){ puts( "0.0000000" ) ; continue ; }
		long double ans = 1.0 ;
		res.s[0][0] = 1.0 ; res.s[0][1] = p ;
		res.s[1][0] = res.s[1][1] = 0.0 ;
		For( i , 1 , n )
			ans *= 1 - ( res * ( x ^ ( mine[i] - mine[i - 1] - 2 ) ) ).s[0][1] ;
		double output = ans ;
		printf( "%.7lf\n" , output ) ;
	}
	
	return 0 ;
}
