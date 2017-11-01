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

template < typename type >
inline type max( const type& x , const type& y ) { return x > y ? x : y ; }
template < typename type >
inline type min( const type& x , const type& y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , const type& y )
	{ return x >= y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , const type& y )
	{ return x <= y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
typedef unsigned long long ULL ;
static const int maxn = 103 ;

int cases ;
LL m ;
int k ;
ULL L ;
ULL R ;

ULL C[maxn][maxn] ;

template < typename type >
inline int number( type x ) {
	int res = 0 ;
	while( x ) ++res , x &= x - 1 ;
	return res ;
}

inline ULL f( ULL x , int y ) {
	static bool stack[maxn] ;
	int tp = 0 ; ULL res = ( number( x ) == y ) ;
	while( x ) stack[ ++tp ] = x & 1 , x >>= 1 ;
	int tot1 = 0 ;
	LOP( i , tp , 1 ) if( stack[i] ) {
		res += C[i - 1][y - tot1] ;
		if( ++tot1 > y )break ;
	}
	return res ;
}

inline ULL get( ULL x ) {
	return f( x << 1 , k ) - f( x , k ) ;
}

inline void div() {
	ULL l = 1 , r = ( 1ULL << 63 ) - 1ULL ;
	while( l <= r ) {
		ULL mid = l + r >> 1 , ges = get( mid ) ;
		if( ges == m )L = mid , r = mid - 1 ;
		else if( ges < m )l = mid + 1 ;
		else r = mid - 1 ;
	}
	l = 1 , r = ( 1ULL << 63 ) - 1ULL ;
	while( l <= r ) {
		ULL mid = l + r >> 1 , ges = get( mid ) ;
		if( ges == m )R = mid , l = mid + 1 ;
		else if( ges < m )l = mid + 1 ;
		else r = mid - 1 ;
	}
}

inline void solve() {
	if( k == 1 ) {
		if( m == 1LL )puts( "3 -1" ) ;
		else puts( "1 -1" ) ;
	} else {
		div() ;
		printf( "%llu %llu\n" , L , R - L + 1ULL ) ;
	}
}

int main() {
	
	freopen( "number.in" , "r" , stdin ) ;
	freopen( "number.out" , "w" , stdout ) ;
	
	FOR( i , 0 , 100 )C[i][0] = 1ULL ;
	For( i , 1 , 100 ) FOR( j , 1 , i )
		C[i][j] = C[i - 1][j] + C[i - 1][j - 1] ;
	
	scanf( cases ) ;
	
	while( cases-- ) {
		scanf( m ) ; scanf( k ) ;
		solve() ;
	}
	
	return 0 ;
}
