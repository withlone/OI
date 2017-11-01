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

static const int maxn = 23 ;
static const int maxm = 1e3 + 13 ;

int m ;
int k ;
int n ;
int ans ;

int xi[maxn] ;
int yi[maxn] ;

int fence[maxn] ;

int V[maxn] ;

int xx[maxn][4] ;

inline int calc( int i ) {
	return xx[i][2] - xx[i][0] + xx[i][3] - xx[i][1] + 2 << 1 ;
}

inline void modify( int i , int x ) {
	chkmin( xx[i][0] , xi[x] ) ;
	chkmin( xx[i][1] , yi[x] ) ;
	chkmax( xx[i][2] , xi[x] ) ;
	chkmax( xx[i][3] , yi[x] ) ;
}

void dfs( int x , int fc , int sum ) {
	if( sum > ans )return ;
	int tt[4] ;
	FOR( i , 1 , fc ) {
		fence[x] = i ;
		int lst = calc( i ) ;
		memcpy( tt , xx[i] , sizeof tt ) ;
		modify( i , x ) ;
		int now = calc( i ) ;
		if( x == n )chkmin( ans , sum - lst + now ) ;
		else dfs( x + 1 , fc , sum - lst + now ) ;
		memcpy( xx[i] , tt , sizeof tt ) ;
	}
	if( fc < k ) {
		fence[x] = ++fc ;
		modify( fc , x ) ;
		if( x == n )chkmin( ans , sum + 4 ) ;
		else dfs( x + 1 , fc , sum + 4 ) ;
		memcpy( xx[fc] , xx[0] , sizeof xx[0] ) ;
	}
}

int main() {
	
	freopen( "fence.in" , "r" , stdin ) ;
	freopen( "fence.out" , "w" , stdout ) ;
	
	scanf( m ) ; scanf( k ) ; scanf( n ) ;
	
	FOR( i , 1 , n )scanf( xi[i] ) , scanf( yi[i] ) ;
	
	ans = ~0U >> 1 ;
	
	FOR( i , 0 , k )
		xx[i][0] = xx[i][1] = 2001 , xx[i][2] = xx[i][3] = 0 ;
	
	dfs( 1 , 0 , 0 ) ;
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
