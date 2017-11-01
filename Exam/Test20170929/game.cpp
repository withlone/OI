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
inline bool chkmax( type& x , const type& y )
	{ return x > y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , const type& y )
	{ return x < y ? false : x = y , true ; }
template < typename type >
type gcd( const type& x , const type& y )
	{ return !y ? x : gcd( y , x % y ) ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 5e5 + 29 ;

int n ;
int li ;
int ri ;

int a[maxn] ;

class BIT {
	private :
		int T[maxn] ;
		
		inline int lowbit( int x ) { return x & -x ; }
		
	public :
		
		BIT() { memset( T , 0 , sizeof T ) ; }
		
		inline void insert( int x ) {
			for( ; x <= n + 1 ; x += lowbit( x ) )
				++T[x] ;
		}
		
		inline int query( int x ) {
			int res = 0 ;
			for( ; x ; x -= lowbit( x ) )res += T[x] ;
			return res ;
		}
		
		inline int query( int l , int r ) {
			return query( r ) - query( l - 1 ) ;
		}
		
} bit ;

namespace idea {
	
	int dt ;
	int dir[maxn] ;
	
	int sum[maxn] ;
	
	LL ans ;
	LL tot ;
	
	class sorter {
		public :
			int a ;
			int b ;
			
			bool operator < ( const sorter& x )
				const { return a == x.a ? b > x.b : a < x.a ; }
	} ster[maxn] ;
	
	inline void main() {
 		FOR( i , 1 , n )
 			sum[i] = sum[i - 1] + a[i] ,
 			ster[i].a = sum[i] - i * li ,
 			dir[i] = ster[i].b = sum[i] - i * ri ;
 		
 		sort( dir , 1 + n + dir ) ;
 		dt = unique( dir , 1 + n + dir ) - dir ;
 		FOR( i , 0 , n )
 			ster[i].b = lower_bound( dir , dt + dir , ster[i].b ) - dir + 1 ;
 		
 		sort( ster , n + 1 + ster ) ;
 		
		ans = 0LL , tot = 1LL * n * ( n + 1 ) >> 1 ;
		
		FOR( i , 0 , n ) {
			ans += bit.query( ster[i].b , n + 1 ) ;
			bit.insert( ster[i].b ) ;
		}
		
		LL g = gcd( ans , tot ) ;
		 
		ans /= g , tot /= g ;
		if( !ans )puts( "0" ) ;
		else if( ans == tot )puts( "1" ) ;
		else printf( "%lld/%lld\n" , ans , tot ) ;
		
	}
}

int main() {
	
	freopen( "game.in" , "r" , stdin ) ;
	freopen( "game.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( li ) ; scanf( ri ) ;
	FOR( i , 1 , n )scanf( a[i] ) ;
	
	idea :: main() ;
	
	return 0 ;
}
