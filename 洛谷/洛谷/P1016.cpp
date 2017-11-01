#include<cstdio>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template < typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }
template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }
template < typename type >
inline type abs( type x ){ return x < 0 ? -x : x ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 10 ;
static const double eps = 1e-5 ;

inline int cmp( double x , double y ) {
	return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ;
}

int n ;
double C ;
double P ;
double D1 ;
double D2 ;
double ans ;

double Di[maxn] ;
double Pi[maxn] ;

inline bool chk() {
	double max_distance = C * D2 ;
	For( i , 1 , n )
		if( cmp( Di[i] - Di[i - 1] , max_distance ) == 1 )
			return false ;
	return true ;
}

void dfs( int x , double oil , double cost ) {
	if( x == n )
		return ( cmp( ans , cost ) == 1 ) ? ans = cost , void() : void() ;
	double need = ( Di[x + 1] - Di[x] ) / D2 ;
	For( i , x + 1 , n ) {
		double ned = ( Di[i] - Di[x] ) / D2 ;
		if( cmp( ned , C ) == 1 )continue ;
		if( cmp( oil , ned ) == -1 )
			dfs( i , 0.0 , cost + ( ned - oil ) * Pi[x] ) ;
		else
			dfs( i , oil - ned , cost ) ;
	}
	dfs( x + 1 , C - need , cost + Pi[x] * ( C - oil ) ) ;
}

inline void output() {
	printf( "%d.%d\n" , (int)ans , (int)( ans * 100 + 0.5 ) % 100 ) ;
}

int main() {
	
	scanf( "%lf%lf%lf%lf%d" , &D1 , &C , &D2 , &P , &n ) ;
	
	Di[1] = 0.0 ; Pi[1] = P ;
	For( i , 2 , ++n )
		scanf( "%lf%lf" , &Di[i] , &Pi[i] ) ;
	++n ;
	Di[n] = D1 ; Pi[n] = 0 ;
	
	if( !chk() )puts( "No Solution" ) ;
	else ans = 1e13 , dfs( 1 , 0.0 , 0.0 ) , output() ;
	
	return 0 ;
}
