#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std ;

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
inline bool chkmax( type& x , const type& y ) {
	return ( x >= y ) ? ( false ) : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return ( x <= y ) ? ( false ) : ( x = y , true ) ;
}

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 5e3 + 21 ;

int n ;
int m ;

int ai[maxn] ;
int bi[maxn] ;

int f[maxn] ;
pair < int , int > pre[maxn][maxn] ;

void printf( pair < int , int > output ) {
	if( !output.second ) return ;
	printf( pre[output.first][output.second] ) ;
	printf( "%d " , bi[output.second] ) ;
}

int main() {
	
	freopen( "okarin.in" , "r" , stdin ) ;
	freopen( "okarin.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	FOR( i , 1 , n ) scanf( ai[i] ) ;
	scanf( m ) ;
	FOR( i , 1 , m ) scanf( bi[i] ) ;
	
	For( i , 1 , n ) {
		int maxer = 0 ;
		int prer = 0 ;
		memcpy( pre[i] , pre[i - 1] , sizeof pre[i] ) ;
		FOR( j , 1 , m )
			if( ai[i] == bi[j] ) {
				f[j] = maxer + 1 ;
				pre[i][j] = make_pair( i - 1 , prer ) ;
			} else if( bi[j] < ai[i] && maxer < f[j] ) {
				maxer = f[j] ;
				prer = j ;
			}
	}
	
	int ans = 0 , at ;
	FOR( i , 1 , m ) if( chkmax( ans , f[i] ) )
		at = i ;
	
	printf( "%d\n" , ans ) ;
	
	printf( make_pair( n , at ) ) ;
	
	putchar( 10 ) ;
	
	return 0 ;
}
/*
7
1 2 3 4 5 6 7
7
2 1 6 3 6 7 6

5
1 4 2 5 1
4
1 1 2 4
*/
