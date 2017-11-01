#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }
template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }

template < typename type >
inline type printf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e5 + 10 ;
static const double pi = 3.141592653589793 ;
static const double eps = 1e-10 ;

inline int cmp( const double& x , const double& y )
{ return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ; }

int n ;
double L ;
double R ;

class light {
	public :
		double x ;
		double y ;
		double z ;
		double k1 ;
		double b1 ;
		double k2 ;
		double b2 ;
		
		light(){ x = y = z = k1 = k2 = b1 = b2 = 0.0 ; }
		
		inline void calc() {
			double zz = ( 90.0 - z ) * pi / 180.0 ;
			double zzz = ( 90.0 + z ) * pi / 180.0 ;
			k1 = tan( zz ) ; k2 = tan( zzz ) ;
			b1 = y - x * k1 ; b2 = y - x * k2 ;
		}
		
		bool operator < ( const light& t ) const {
			if( cmp( x , t.x ) )return cmp( x , t.x ) == -1 ;
			if( cmp( y , t.y ) )return cmp( y , t.y ) == -1 ;
			return cmp( z , t.z ) == 1 ;
		}
} cp[maxn] ;

inline bool chk( double y ) {
	double maxr = L , l , r ;
	For( i , 1 , n ) if( cmp( cp[i].y , y ) != -1 ) {
		 l = ( y - cp[i].b1 ) / cp[i].k1 ,
		 r = ( y - cp[i].b2 ) / cp[i].k2 ;
		 if( cmp( l , maxr ) != 1 && cmp( r , maxr ) == 1 )
			maxr = r ;
	}
	return cmp( R , maxr ) != 1 ;
}

int main() {
	
	freopen( "light.in" , "r" , stdin ) ;
	freopen( "light.out" , "w" , stdout ) ;
	
	double l = 0.0 , r = 0.0 , mid ;
	
	scanf( "%d%lf%lf" , &n , &L , &R ) ;
	
	For( i , 1 , n )
		scanf( "%lf%lf%lf" , &cp[i].x , &cp[i].y , &cp[i].z ) ,
		cp[i].calc() , r = ( cmp( r , cp[i].y ) == -1 ? cp[i].y : r );
	
	sort( 1 + cp , 1 + n + cp ) ;
	
	while( cmp( l , r ) ) {
		mid = ( l + r ) / 2.0 ;
		if( chk( mid ) )l = mid ;
		else r = mid ;
	}
	
	printf("%.9lf\n" , l ) ;
	
	return 0 ;
}
