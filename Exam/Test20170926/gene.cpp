#include<cstdio>
#include<cstring>

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

static const int maxn = 1000003 ;
static const int mod = 998244353 ;
static const int ten = 233 ;

int n ;

int f[maxn] ;
int g[maxn] ;

char gene[maxn] ;

inline int get( int l , int r ) {
	int res = f[r] - f[l - 1] ;
	if( res < 0 )res += mod ;
	return res ;
}

inline bool chk( int x , int y ) {
	if( ( 1LL * f[y - x + 1] * g[x - 1] % mod ) == get( x , y ) )return true ;
	return false ;
}

inline int div( int l , int r ) {
	int mid , res = l - 1 , L = l ;
	while( l <= r ) {
		mid = l + r >> 1 ;
		if( chk( L , mid ) )res = mid , l = mid + 1 ;
		else r = mid - 1 ;
	}
	return res ;
}

int main() {
	
	freopen( "gene.in" , "r" , stdin ) ;
	freopen( "gene.out" , "w" , stdout ) ;
	
	scanf( "%s" , gene + 1 ) ;
	
	n = strlen( gene + 1 ) ;
	
	g[0] = 1 ;
	FOR( i , 1 , n )
		g[i] = 1LL * g[i - 1] * ten % mod ;
	
	FOR( i , 1 , n )
		f[i] = ( f[i - 1] + 1LL * g[i - 1] * gene[i] % mod ) % mod ;
	
	long long ans = n ;
	For( i , 2 , n ) if( gene[i] == gene[1] )
		ans += div( i , n ) - i + 1 ;
	
	printf( "%lld\n" , ans ) ;
	
	return 0 ;
}
