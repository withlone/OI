#include<cstdio>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )
#define FOR( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define LOP( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define REP( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename tp >
inline tp max( const tp& x , const tp& y ) { return x > y ? x : y ; }
template < typename tp >
inline tp min( const tp& x , const tp& y ) { return x < y ? x : y ; }
template < typename tp >
inline bool chkmax( tp& x , const tp& y ) {
	return x >= y ? false : ( x = y , true ) ;
}
template < typename tp >
inline bool chkmin( tp& x , const tp& y ) {
	return x <= y ? false : ( x = y , true ) ;
}

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 5e3 + 11 ;
static const int mod = 998244353 ;

int a ;
int b ;
int c ;

int fac[maxn] ;

int C[maxn][maxn] ;

inline int add( int x , int y ) {
	x += y ; if ( x >= mod ) x -= mod ; return x ;
}

inline int mul( int x , int y ) {
	return 1LL * x * y % mod ;
}

inline void init() {
	C[0][0] = 1 ;
	For( i , 1 , 5000 ) {
		C[i][0] = 1 ;
		FOR( j , 1 , i )
			C[i][j] = add( C[i - 1][j] , C[i - 1][j - 1] ) ;
	}
	fac[0] = 1 ;
	FOR( i , 1 , 5000 ) fac[i] = mul( fac[i - 1] , i ) ;
}

inline int calc( int x , int y ) {
	int res = 0 ;
	FOR( i , 0 , min( x , y ) )
		res = add( res , mul( mul( C[x][i] , C[y][i] ) , fac[i] ) ) ;
	return res ;
}

int main() {
	
	init() ;
	
	scanf( a ) ; scanf( b ) ; scanf( c ) ;
	
	printf( "%d\n" ,
	 mul( mul( calc( a , b ) , calc( b , c ) ) , calc( a , c ) ) ) ;
	
	return 0 ;
}
