#include<cmath>
#include<cstdio>

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
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e5 + 19 ;
static const double eps = 1e-4 ;

double H ;
double S ;
double V ;
double L ;
double K ;
int n ;

int ans ;

int main() {
	
	freopen( "c.in" , "r" , stdin ) ;
	freopen( "c.out" , "w" , stdout ) ;
	
	scanf( "%lf%lf%lf%lf%lf%d" , &H , &S , &V , &L , &K , &n ) ;
	
	double t1 = sqrt( 0.2 * ( H - K ) ) ;
	double t2 = sqrt( 0.2 * H ) ;
	
	double S1 = S - t1 * V + L ;
	double S2 = S - t2 * V ;
	
	FOR( i , 0 , n - 1 )
		if( i < S1 + eps && i > S2 - eps )
			++ans ;
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
