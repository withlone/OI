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

template < typename tp >
inline tp max( const tp& x , const tp& y ) { return x > y ? x : y ; }
template < typename tp >
inline tp min( const tp& x , const tp& y ) { return x < y ? x : y ; }
template < typename tp >
inline bool chkmax( tp& x , const tp& y ) {
	return x >= y ? false : ( x = y , true ) ;
}
template < typename tp >
inline bool chkmin( tp& x , const tp& y ) {
	return x <= y ? false : ( x = y , true ) ;
}

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e5 + 11 ;
static const int maxm = 2e5 + 11 ;
static const int maxx = 23 ;

int n ;
int s ;
int k ;
int ans ;

int F[maxn][maxx] ;
int G[maxn][maxx] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins( int x , int y ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

inline int ceil( double x ) {
	return (int)x + ( x - (int)x > 1e-5 ) ;
}

void dfs( int x , int f ) {
	G[x][0] = 1 ;
	Rep( i , Ht[x] , Nt[i] ) if( to[i] != f ) {
		dfs( to[i] , x ) ;
		FOR( z , 1 , k )
			G[x][z] += G[to[i]][z - 1] ,
			F[x][z] = min( F[x][z] + F[to[i]][z - 1] , n ) ;
	}
	if( G[x][k] ) {
		int t = ceil( G[x][k] * 1.0 / s ) ;
		F[x][0] = min( t * s - G[x][k] , n ) ;
		G[x][k] = 0 ; ans += t ;
	}
	FOR( i , 0 , k ) {
		int t = min( F[x][i] , G[x][k - i] ) ;
		F[x][i] -= t ; G[x][k - i] -= t ;
	}
	FOR( i , 0 , k - 1 ) {
		int t = min( F[x][i] , G[x][k - 1 - i] ) ;
		F[x][i] -= t ; G[x][k - 1 - i] -= t ;
	}
}

int main() {
	
	freopen( "repulsed.in" , "r" , stdin ) ;
	freopen( "repulsed.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( s ) ; scanf( k ) ;
	FOR( i , 1 , n - 1 ) {
		register int x , y ;
		scanf( x ) ; scanf( y ) ;
		ins( x , y ) ; ins( y , x ) ;
	}
	
	dfs( 1 , 0 ) ;
	
	int ps = k , lst = 0 ;
	For( i , 0 , k ) {
		while( ps >= 0 && G[1][i] ) {
			if( ps + i > k ) ps = k - i ;
			int t = min( F[1][ps] , G[1][i] ) ;
			F[1][ps] -= t ; G[1][i] -= t ;
			while( ps >= 0 && !F[1][ps] ) --ps ;
		}
		lst += G[1][i] ;
	}
	
	printf( "%d\n" , ans + ceil( lst * 1.0 / s ) ) ;
	
	return 0 ;
}
