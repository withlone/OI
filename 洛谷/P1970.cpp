#include<cstdio>
#include<cstring>

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
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e5 + 10 ;
static const int inf  = 1e6 + 1 ;

int n ;

int hi[maxn] ;

int f[maxn] ;
int g[maxn] ;

int main() {
	
	For( i , 1 , scanf( n ) )scanf( hi[i] ) ;
	
	g[0] = -1 ;
	For( i , 1 , n )
		if( f[i - 1] & 1 ) {
			if( hi[i] < g[i - 1] )
				f[i] = f[i - 1] + 1 , g[i] = hi[i] ;
			else
				f[i] = f[i - 1] , g[i] = max( g[i - 1] , hi[i] ) ;
		} else {
			if( hi[i] > g[i - 1] )
				f[i] = f[i - 1] + 1 , g[i] = hi[i] ;
			else f[i] = f[i - 1] , g[i] = min( g[i - 1] , hi[i] ) ;
		}
	
	int ans = f[n] ;
	
	memset( g , 0 , sizeof(int) * (n + 1) ) ;
	memset( f , 0 , sizeof(int) * (n + 1) ) ;
	
	g[0] = inf ;
	For( i , 1 , n )
		if( f[i - 1] & 1 ) {
			if( hi[i] > g[i - 1] )
				f[i] = f[i - 1] + 1 , g[i] = hi[i] ;
			else
				f[i] = f[i - 1] , g[i] = min( g[i - 1] , hi[i] ) ;
		} else {
			if( hi[i] < g[i - 1] )
				f[i] = f[i - 1] + 1 , g[i] = hi[i] ;
			else
				f[i] = f[i - 1] , g[i] = max( g[i - 1] , hi[i] ) ;
		}
	
	printf( "%d\n" , max( ans , f[n] ) ) ;
	
	return 0 ;
}
