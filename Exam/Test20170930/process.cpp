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
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define LOP( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define REP( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline bool chkmax( type& x , const type& y ) {
	return x >= y ? false : x = y , true ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x <= y ? false : x = y , true ;
}

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 1e5 + 19 ;

int n ;
LL mod ;

class process {
	public :
		LL t ;
		LL s ;
		
		bool operator < ( const process& x )
			const { return x.s * t < s * x.t ; }
} pc[maxn] ;

inline LL qadd( LL x , LL y ) {
	LL res = 0LL ;
	for( ; y ; y >>= 1 , x = ( x << 1 ) % mod )
		if( y & 1 )res = ( res + x ) % mod ;
	return res ;
}

int main() {
	
	freopen( "process.in" , "r" , stdin ) ;
	freopen( "process.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( mod ) ;
	FOR( i , 1 , n )scanf( pc[i].t ) , scanf( pc[i].s ) ;
	
	sort( 1 + pc , 1 + n + pc ) ;
	
	LL ans = 0LL , sumt = 0LL ;
	FOR( i , 1 , n )
		ans = ( ans + qadd( pc[i].s , sumt ) ) % mod ,
		sumt = ( sumt + pc[i].t ) % mod ;
	
	printf( "%lld\n" , ans ) ;
	
	return 0 ;
}
