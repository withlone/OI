#include<cstdio>
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
	return x > y ? false : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x < y ? false : ( x = y , true ) ;
}
template < typename type >
inline type abs( type x ) { return x < 0 ? -x : x ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 23 ;
static const int maxm = 403 ;
static const int maxx = 270001 ;
static const double eps = 1e-10 ;

inline int cmp( const double& x , const double& y ){
	return abs( x - y ) < eps ? 0 : x - y > 0.0 ? 1 : -1 ;
}

int cases ;
int n ;
int cnt ;
int rubbish ;

int beat[maxm] ;

double a ;
double b ;

double xi[maxn] ;
double yi[maxn] ;

int f[maxx] ;

inline bool chk( int x ) {
	if( !cmp( yi[x] , a * xi[x] * xi[x] + b * xi[x] ) )return true ;
	return false ;
}

int main() {
	
	freopen( "angrybirds.in" , "r" , stdin ) ;
	freopen( "angrybirds.out" , "w" , stdout ) ;
	
	scanf( cases ) ;
	
	while( cases-- ) {
		scanf( n ) ; scanf( rubbish ) ;
		FOR( i , 1 , n )
			scanf( "%lf%lf" , &xi[i] , &yi[i] )
			, xi[i] *= 100 , yi[i] *= 100 ;
		
		cnt = 0 ;
		For( i , 1 , n ) For( j , i + 1 , n ) {
			if( !cmp( xi[j] - xi[i] , 0 ) )continue ;
			a = ( xi[i] * yi[j] - xi[j] * yi[i] )
						/ ( xi[i] * xi[j] * ( xi[j] - xi[i] ) ) ;
			if( a >= 0.0 )continue ;
			b = ( yi[i] - xi[i] * xi[i] * a ) / xi[i] ;
			if( !cmp( a + b , b ) )continue ;
			beat[ ++cnt ] = 0 ;
			FOR( k , 1 , n ) if( chk( k ) )
				beat[cnt] |= 1 << k - 1 ;
		}
		FOR( i , 1 , n )beat[ ++cnt ] = 1 << i - 1 ;
		sort( 1 + beat , 1 + cnt + beat ) ;
		cnt = unique( 1 + beat , 1 + cnt + beat ) - beat - 1 ;
		FOR( i , 0 , ( 1 << n ) - 1 )f[i] = n + 1 ;
		f[0] = 0 ;
		For( i , 0 , ( 1 << n ) - 1 )
			FOR( j , 1 , cnt ) if( ( i & beat[j] ) != beat[j] )
				chkmin( f[i | beat[j]] , f[i] + 1 ) ;
		printf( "%d\n" , f[( 1 << n ) - 1] ) ;
	}
	
	return 0 ;
}
