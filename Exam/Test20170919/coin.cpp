#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

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

static const int maxn = 1e3 + 10 ;


int cases ;
int n ;

int coin ;

double f[maxn][maxn] ;

inline void dp() {
	For( i , 1 , 1000 ) For( j , 1 , i )
		f[i][j] = 1.0 - 0.5 * ( f[i - 1][j - 1] + f[i - 1][j] ) ;
}

int main() {
	
	freopen( "coin.in" , "r" , stdin ) ;
	freopen( "coin.out" , "w" , stdout ) ;
	
	dp() ;
	
	scanf( cases ) ;
	
	while( cases-- ) {
		scanf( n ) ;
		long double ans = 0.0 ;
		For( i , 1 , n ) {
			scanf( coin ) ;
			ans += f[n][i] * coin ;
		}
		double output = ans ;
		printf("%.3lf\n" , output ) ;
	}
	
	return 0 ;
}
