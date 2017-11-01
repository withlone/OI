#include<set>
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

static const int maxn = 2e5 + 17 ;

int n ;

int c[maxn] ;

class clique {
	public :
		int x ;
		int w ;
		int ky1 ;
		int ky2 ;
		
		bool operator < ( const clique& t )
			const { return x == t.x ? w < t.w : x < t.x ; }
		
		inline void calc() {
			ky1 = x - w ;
			ky2 = x + w ;
		}
} cq[maxn] ;

inline int div( const int& x ) {
	int l = 1 , r = n , res = 0 ;
	while( l <= r ) {
		int mid = l + r >> 1 ;
		if( x >= c[mid] )res = mid , l = mid + 1 ;
		else r = mid - 1 ;
	}
	return res ;
}

int main() {
	
	freopen( "clique.in" , "r" , stdin ) ;
	freopen( "clique.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	FOR( i , 1 , n )
		scanf( cq[i].x ) , scanf( cq[i].w ) , cq[i].calc() ;
	
	sort( 1 + cq , 1 + n + cq ) ;
	
	FOR( i , 1 , n )c[i] = 2e9 ;
	
	int ans = 0 ;
	FOR( i , 1 , n ) {
		int t = div( cq[i].ky1 ) ;
		chkmax( ans , t + 1 ) ;
		chkmin( c[t + 1] , cq[i].ky2 ) ;
	}
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
