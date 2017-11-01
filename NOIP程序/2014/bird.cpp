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
inline type min( const type& x , const type& y ){ return x < y ? x : y ; }
template < typename type >
inline type max( const type& x , const type& y ){ return x > y ? x : y ; }
template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }
template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 12377 ;
static const int maxm = 1231 ;
static const int inf = 1061109567 ;

int n ;
int m ;
int K ;

int xi[maxn] ;
int yi[maxn] ;
int pi[maxn] ;
int li[maxn] ;
int hi[maxn] ;
int up[maxn] ;
int down[maxn] ;

int f[maxn][maxm] ;

inline int find( int x ) {
	int res = 0 ;
	FOR( i , 1 , K )
		res += ( pi[i] <= x ) ;
	return res ;
}

int main() {
	
	freopen( "bird.in" , "r" , stdin ) ;
	freopen( "bird.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ; scanf( K ) ;
	
	FOR( i , 0 , n - 1 )
		scanf( xi[i] ) , scanf( yi[i] ) ;
	
	FOR( i , 0 , n )
		up[i] = m , down[i] = 1 ;
	
	FOR( i , 1 , K ) {
		scanf( pi[i] ) , scanf( li[i] ) , scanf( hi[i] ) ;
		up[ pi[i] ] = hi[i] - 1 , down[ pi[i] ] = li[i] + 1 ;
	}
	
	memset( f , 0x3f , sizeof f ) ;
	
	FOR( i , 1 , m )f[0][i] = 0 ;
	
	For( i , 1 , n ) {
		FOR( j , 1 , m ) {
			if( j - xi[i - 1] >= 1 )
				chkmin( f[i][j] ,
				min( f[i - 1][j - xi[i - 1]] , f[i][j - xi[i - 1]] ) + 1 ) ;
			if( j == m ) {
				For( k , max( m - xi[i - 1] , 1 ) , m ) {
					chkmin( f[i][j] , f[i - 1][k] + 1 ) ;
					if( k - xi[i - 1] >= 1 )
						chkmin( f[i][j] , f[i][k] + 1 ) ;
				}
			}
		}
		FOR( j , 1 , m - yi[i - 1] )
			chkmin( f[i][j] , f[i - 1][j + yi[i - 1]] ) ;
		FOR( j , 0 , down[i] - 1 )f[i][j] = inf ;
		FOR( j , up[i] + 1 , m )f[i][j] = inf ;
	}
	
	int ans = inf ;
	FOR( i , 1 , m )
		chkmin( ans , f[n][i] ) ;
	
	if( ans != inf )
		printf( "1\n%d\n" , ans ) ;
	else {
		Lop( i , n - 1 , 0 ) FOR( j , 1 , m )
			if( f[i][j] != inf )
				return printf( "0\n%d\n" , find( i ) ) , 0 ;
		throw ;
	}
	
	return 0 ;
}
