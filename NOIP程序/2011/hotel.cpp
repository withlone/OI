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
	return x > y ? false : x = y , true ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x < y ? false : x = y , true ;
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

typedef long long LL ;
static const int maxn = 2e5 + 3 ;
static const int maxm = 61 ;

int n ;
int m ;
int lowest ;

LL ans ;

int sum[maxm] ;

int cost[maxn] ;
int color[maxn] ;

int Ct ;
int Ht ;
int Nt[maxn] ;
int to[maxn] ;

inline LL sqr( int x ) {
	return 1LL * x * ( x - 1 ) >> 1 ;
}

int main() {
	
	freopen( "hotel.in" , "r" , stdin ) ;
	freopen( "hotel.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ; scanf( lowest ) ;
	
	FOR( i , 1 , n )
		scanf( color[i] ) , scanf( cost[i] ) ;
	
	Nt[ ++Ct ] = Ht ; Ht = Ct ; to[Ct] = n + 1 ;
	LOP( i , n , 1 ) if( cost[i] <= lowest ) {
		Nt[ ++Ct ] = Ht ; Ht = Ct ; to[Ct] = i ;
	}
	
	For( j , 0 , m - 1 ) {
		FOR( i , 1 , n )
			sum[i] = sum[i - 1] + ( color[i] == j ) ;
		
		ans += sqr( sum[n] ) ;
		
		int lst = 0 ;
		REP( i , Ht , Nt[i] ) {
			ans -= sqr( sum[to[i] - 1] - sum[lst] ) ;
			lst = to[i] ;
		}
	}
	
	printf( "%lld\n" , ans ) ;
	
	return 0 ;
}
