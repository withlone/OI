#include<cstdio>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type max( type x , type y ) { return x > y ? x : y ; }
template < typename type >
inline type min( type x , type y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }
template < typename type >
inline type gcd( type x , type y ){ return !y ? x : gcd( y , x % y ) ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 1e6 + 10 ;
static const int maxm = maxn << 2 ;

int n ;
int m ;
int qwq ;
int mdep ;

int seq[maxn] ;
int dep[maxn] ;

LL dt[maxn] ;

void build( int rt , int l , int r , int deper ) {
	if( l == r )
		return dep[l] = deper , chkmax( mdep , deper ) , void() ;
	int mid = l + r >> 1 ;
	build( rt << 1 , l , mid , deper + 1 ) ;
	build( rt << 1 | 1 , mid + 1 , r , deper + 1 ) ;
}

int main() {
	
	scanf( n ) ; scanf( m ) ; scanf( qwq ) ;
	
	For( i , 1 , n ) scanf( seq[i] ) ;
	
	build( 1 , 1 , n , 1 ) ;
	
	LL base = 1 << mdep - 1 ;
	LL temp = gcd( base , 1LL * qwq ) ;
	base /= temp ; qwq /= temp ;
	LL t = 0LL ;
	For( i , 1 , n ) {
		dt[i] = ( ( 1 << dep[i] ) - 1 ) << ( mdep - dep[i] ) ;
		t = t + dt[i] * ( seq[i] ) ;
		dt[i] = dt[i] + dt[i - 1] ;
	}
	
	register int x , y , z ;
	
	while( m-- ) {
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		t = t + (( dt[y] - dt[x - 1] ) * ( z )) ;
		printf("%lld\n" , t / base * qwq ) ;
	}
	
	return 0 ;
}
