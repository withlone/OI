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
inline bool chkmax( type& x , const type& y ) {
	return x >= y ? false : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x <= y ? false : ( x = y , true ) ;
}
template < typename type >
inline void swap( type& x , type& y ) { type t = x ; x = y ; y = t ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e3 + 13 ;
static const int maxm = 1e4 + 37 ;

int n ;
int m ;
int k ;

int TT[maxm] ;
int AA[maxm] ;
int BB[maxm] ;

int f[maxn] ;
int g[maxn] ;
int di[maxn] ;
int at[maxn] ;
int nmb[maxn] ;

int main() {
	
	freopen( "bus.in" , "r" , stdin ) ;
	freopen( "bus.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ; scanf( k ) ;
	
	FOR( i , 1 , n - 1 )scanf( di[i] ) ;
	
	FOR( i , 1 , m ) {
		register int Ti , Ai , Bi ;
		TT[i] = scanf( Ti ) ; AA[i] = scanf( Ai ) ; BB[i] = scanf( Bi ) ;
		chkmax( g[Ai] , Ti ) ;
		nmb[Bi]++ ;
	}
	
	FOR( i , 1 , n )nmb[i] += nmb[i - 1] ;
	
	int ans = 0 ;
	
	FOR( i , 2 , n )
		f[i] = max( f[i - 1] , g[i - 1] ) + di[i - 1] ;
	FOR( i , 1 , m )
		ans += f[BB[i]] - TT[i] ;
	
	at[n - 1] = n ;
	while( k-- ) {
		int mx = 0 , ps = 0 ;
		LOP( i , n - 2 , 1 )
			if( f[i + 1] > g[i + 1] )
				at[i] = at[i + 1] ;
			else at[i] = i + 1 ;
		FOR( i , 1 , n - 1 )
			if( di[i] && chkmax( mx , nmb[at[i]] - nmb[i] ) )
				ps = i ;
		if( !ps )break ;
		di[ps]-- ;
		FOR( i , 2 , n )
			f[i] = max( f[i - 1] , g[i - 1] ) + di[i - 1] ;
		ans -= mx ;
	}
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
