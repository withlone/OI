#include<map>
#include<cstdio>
#include<algorithm>

using namespace std ;

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

typedef unsigned long long ULL ;
typedef long long LL ;
typedef pair < ULL , ULL > __ ;
static const int maxn = 25e2 + 11 ;

int n ;
int m ;
int q ;

__ emp ;

__ T[maxn][maxn] ;

map < LL , __ > adder ;

__ operator + ( const __& x , const __& y ) {
	return __ ( x.first + y.first , x.second + y.second ) ;
}

__ operator - ( const __& x ) {
	return __ ( -x.first , -x.second ) ;
}

void operator += ( __& x , const __& y ) {
	x = x + y ;
}

inline LL change( LL a , LL b , LL c , LL d ) {
	return  a * 1e12 + b * 1e8 + c * 1e4 + d ;
}

inline int lowbit( int x ) { return x & -x ; }

inline void modify( int x , int y , __ c ) {
	for( int i = x ; i <= n ; i += lowbit( i ) )
		for( int j = y ; j <= m ; j += lowbit( j ) )
			T[i][j] += c ;
}

inline void modify( int x1 , int x2 , int y1 , int y2 , __ c ) {
	modify( x1 , y1 , c ) ; modify( x2 + 1 , y2 + 1 , c ) ;
	modify( x1 , y2 + 1 , -c ) ; modify( x2 + 1 , y1 , -c ) ;
}

inline __ query( int x , int y ) {
	__ res = emp ;
	for( int i = x ; i ; i -= lowbit( i ) )
		for( int j = y ; j ; j -= lowbit( j ) )
			res += T[i][j] ;
	return res ;
}

int main() {
	
	scanf( n ) ; scanf( m ) ; scanf( q ) ;
	
	modify( 1 , n , 1 , m , __ ( rand() , rand() ) ) ;
	
	while( q-- ) {
		int op , x1 , x2 , y1 , y2 ;
		scanf( op ) ; scanf( x1 ) ; scanf( y1 ) ; scanf( x2 ) ; scanf( y2 ) ;
		if( op == 3 )
			puts( query( x1 , y1 ) == query( x2 , y2 ) ? "Yes" : "No" ) ;
		else {
			if( x1 > x2 ) swap( x1 , x2 ) ;
			if( y1 > y2 ) swap( y1 , y2 ) ;
			LL c = change( x1 , x2 , y1 , y2 ) ;
			__ t ;
			if( op == 1 )
				t = adder[c] = __ ( rand() , rand() ) ,
				modify( x1 , x2 , y1 , y2 , t ) ;
			else t = adder[c] , adder[c] = emp ,
				modify( x1 , x2 , y1 , y2 , -t ) ;
		}
	}
	
	return 0 ;
}
