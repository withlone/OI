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
	return ( x >= y ) ? false : ( x = y , true ) ;
}
template < typename tp >
inline bool chkmin( tp& x , const tp& y ) {
	return ( x <= y ) ? false : ( x = y , true ) ;
}

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 111 ;

int n ;
int m ;
int k ;
int ans ;
int tot ;

int ai[maxn][maxn] ;

int sum[maxn] ;

int main() {
	
	scanf( n ) ; scanf( m ) ; scanf( k ) ;
	For( i , 1 , n ) FOR( j , 1 , m ) scanf( ai[i][j] ) ;
	
	For( j , 1 , m ) {
		FOR( i , 1 , n ) sum[i] = sum[i - 1] + ai[i][j] ;
		int mx = 0 , top = 0 ;
		FOR( i , 1 , n ) if( ai[i][j] ) {
			int t = sum[min( i + k - 1 , n )] - sum[i - 1] ;
			if( t > mx )
				mx = t , top = i ;
		}
		if( mx )
			ans += mx , tot += sum[top - 1] ;
	}
	
	printf( "%d %d\n" , ans , tot ) ;
	
	return 0 ;
}
