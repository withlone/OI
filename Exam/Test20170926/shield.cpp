#include<cstdio>
#include<cstring>
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

template < typename type >
inline type max( const type& x , const type& y ) { return x > y ? x : y ; }
template < typename type >
inline type min( const type& x , const type& y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , const type& y )
	{ return x > y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , const type& y )
	{ return x < y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 200003 ;

int n ;
int bt ;
int ans ;
LL x1 ;
LL y1 ;
LL x2 ;
LL y2 ;
LL c[maxn] ;

LL xi[maxn] ;
LL yi[maxn] ;
LL Bi[maxn] ;

class point {
	public :
		LL x ;
		LL y ;
		bool operator < ( const point& t )
			const { return x == t.x ? y < t.y : x < t.x ; }
} pt[maxn] ;

inline bool cmp( const int& x , const int& y ) {
	return xi[x] == xi[y] ? yi[x] < yi[y] : xi[x] < xi[y] ;
}

inline int div( int x ) {
	int l = 1 , r = n , res = 0 ;
	while( l <= r ) {
		int mid = l + r >> 1 ;
		if( x >= c[mid] )res = mid , l = mid + 1 ;
		else r = mid - 1 ;
	}
	return res ;
}

int main() {
	
	freopen( "shield.in" , "r" , stdin ) ;
	freopen( "shield.out" , "w" , stdout ) ;
	
	register LL x , y ;
	
	scanf( n ) ; scanf( x1 ) ; scanf( y1 ) ; scanf( x2 ) ; scanf( y2 ) ;
	
	int f = 1 ;
	if( x1 * y2 - x2 * y1 < 0 )f = -1 ;
	
	FOR( i , 1 , n ) {
		scanf( x ) ; scanf( y ) ;
		pt[i].x = xi[i] = x * y2 - x2 * y ;
		pt[i].y = Bi[i] = yi[i] = x1 * y - x * y1 ;
	}
	
	sort( 1 + Bi , 1 + n + Bi ) ;
	bt = unique( 1 + Bi , 1 + n + Bi ) - Bi - 1 ;
	FOR( i , 1 , n )
		pt[i].y = lower_bound( 1 + Bi , 1 + bt + Bi , yi[i] ) - Bi ;
	
	sort( 1 + pt , 1 + n + pt ) ;
	
	memset( c , 0x7f , sizeof c ) ;
	FOR( i , 1 , n )yi[i] = pt[i].y ;
	//printf( "%lld " , yi[i] = pt[i].y ) ; putchar( 10 ) ;
	FOR( i , 1 , n ) {
		int t = div( yi[i] ) ;
		chkmin( c[t + 1] , yi[i] ) ;
		chkmax( ans , t + 1 ) ;
	}
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
