#include<cstdio>
#include<cstring>
#include<cstdlib>

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
	return x > y ? false : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x < y ? false : ( x = y , true ) ;
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

static const int maxn = 1e3 + 13 ;
static const int maxx = 2e3 + 3 ;
static const int maxm = 2e6 + 3 ;
static const int inf = ~0U >> 1 ;

int n ;

int tp[2] ;
int stack[2][maxx] ;

int a[maxn] ;
int c[maxn] ;
int f[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins( const int& x , const int& y ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

inline void error() {
	puts( "0" ) ; exit( 0 ) ;
}

void dfs( int x ) {
	REP( i , Ht[x] , Nt[i] )
		if( c[to[i]] != -1 ) {
			if( c[to[i]] == c[x] )error() ;
		}
		else {
			c[to[i]] = c[x] ^ 1 ;
			dfs( to[i] ) ;
		}
}

int main() {
	
	freopen( "twostack.in" , "r" , stdin ) ;
	freopen( "twostack.out" , "w" , stdout ) ;
	
	FOR( i , 1 , scanf( n ) )scanf( a[i] ) ;
	
	f[n + 1] = inf ;
	LOP( i , n , 1 )f[i] = min( f[i + 1] , a[i] ) ;
	
	For( j , 2 , n ) FOR( i , 1 , j - 1 )
		if( a[i] < a[j] && f[j + 1] < a[i] )
			ins( i , j ) , ins( j , i ) ;
	
	memset( c , -1 , sizeof c ) ;
	FOR( i , 1 , n ) if( c[i] == -1 )
		c[i] = 0 , dfs( i ) ;
	
	int toper = 1 ;
	FOR( i , 1 , n + 1 ) {
		while( stack[0][tp[0]] == toper || stack[1][tp[1]] == toper ) {
			if( stack[0][tp[0]] == toper )
				tp[0]-- , toper++ , printf( "b " ) ;
			else
				tp[1]-- , toper++ , printf( "d " ) ;
		}
		if( i == n + 1 )break ;
		if( !c[i] )stack[0][ ++tp[0] ] = a[i] , printf( "a " ) ;
		else stack[1][ ++tp[1] ] = a[i] , printf( "c " ) ;
	}
	
	putchar( 10 ) ;
	
	return 0 ;
}
