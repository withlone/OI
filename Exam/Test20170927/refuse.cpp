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

static const int maxn = 23 ;

int n ;
int m ;
int tot ;
double ans ;

int sum[maxn] ;

int pvq[maxn][maxn] ;
int qvp[maxn][maxn] ;

int f[2][maxn * maxn] ;
int g[2][maxn * maxn] ;

int main() {
	
	freopen( "refuse.in" , "r" , stdin ) ;
	freopen( "refuse.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n ) FOR( j , 1 , m )
		tot += scanf( pvq[i][j] ) ;
	
	if( n > m ) {
		swap( n , m ) ;
		For( i , 1 , n ) FOR( j , 1 , m )
			qvp[i][j] = pvq[j][i] ;
	}
	else memcpy( qvp , pvq , sizeof qvp ) ;
	
	For( i , 1 , n ) FOR( j , 1 , m )
		sum[i] += qvp[i][j] ;
	
	int full = ( 1 << n ) - 1 ;
	
	For( sus , 0 , full ) {
		int num = 0 , orz = 0 ;
		For( i , 1 , n )
			if( sus >> i - 1 & 1 )
				num += sum[i] , orz ^= 1 ;
		memset( f , 0 , sizeof f ) ;
		memset( g , 0 , sizeof g ) ;
		g[orz][num] = 1 ;
		For( i , 1 , m ) {
			int sumer = 0 ;
			FOR( j , 1 , n )
				if( !( sus >> j - 1 & 1 ) )sumer += qvp[j][i] ;
			Lop( j , tot , sumer ) FOR( k , 0 , 1 ) {
				f[k][j] = g[k][j] ;
				if( j - sumer >= 0 )f[k][j] += g[k ^ 1][j - sumer] ;
			}
			FOR( j , 0 , sumer - 1 )
				f[0][j] = g[0][j] , f[1][j] = g[1][j] ;
			memcpy( g , f , sizeof g ) ;
		}
		FOR( j , 1 , tot )
			ans += ( f[1][j] - f[0][j] ) * tot * 1.0 / j ;
	}
	
	printf( "%.5lf\n" , ans ) ;
	
	return 0 ;
}
