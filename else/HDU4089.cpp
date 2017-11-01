#include<cmath>
#include<cstdio>

using namespace std ;

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

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

static const int maxn = 2e3 + 10 ;
static const double eps = 1e-10 ;

inline int cmp( const double& x , const double& y ) {
	return abs( x - y ) < eps ? 0 : x - y > 0.0 ? 1 : -1 ;
}

int n ;
int m ;
int k ;

double p1 ;
double p2 ;
double p3 ;
double p4 ;

double f[maxn] ;
double c[maxn] ;
double php[maxn] ;

inline void dp() {
	p2 /= 1.0 - p1 ; p3 /= 1.0 - p1 ; p4 /= 1.0 - p1 ;
	php[0] = 1.0 ;
	f[1] = p4 / ( 1.0 - p2 ) ; c[0] = p4 ;
	For( i , 1 , n )php[i] = php[i - 1] * p2 ;
	For( i , 2 , n ) {
		For( j , 2 , i )
			c[j - 1] = p3 * f[j - 1] + p4 * ( j <= k ) ;
		f[i] = c[0] * php[i - 1] ;
		For( j , 2 , i )
			f[i] += c[j - 1] * php[i - j] ;
		f[i] /= 1.0 - php[i] ;
		f[1] = f[i] * p2 + c[0] ;
		For( j , 2 , i - 1 )
			f[j] = p2 * f[j - 1] + c[j - 1] ;
	}
	printf("%.5lf\n" , f[m] ) ;
}

int main() {
	
	while( scanf( "%d%d%d" , &n , &m , &k ) != EOF ) {
		scanf( "%lf%lf%lf%lf" , &p1 , &p2 , &p3 , &p4 ) ;
		if( p4 < eps )printf( "%.5lf\n" , 0.0 ) ;
		else dp() ;
	}
	
	return 0 ;
}
