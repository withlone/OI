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

static const int maxn = 5e4 + 21 ;

int n ;

int li[maxn] ;
int ri[maxn] ;

int ai[maxn] ;
int bi[maxn] ;
int at[maxn] ;

int cnt[maxn] ;

inline void error() {
	puts( "-1" ) ; exit( 0 ) ;
}

inline void debug( int *x , int n = ::n ) {
	FOR( i , 1 , n )printf( "%d " , x[i] ) ; putchar( 10 ) ;
}

int main() {
	
	scanf( n ) ;
	
	FOR( i , 1 , n )scanf( li[i] ) , scanf( ri[i] ) ;
	
	ai[1] = 1 ; ai[2] = ri[1] ;
	FOR( i , 3 , n ) {
		if( ai[i - 2] == li[ ai[i - 1] ] )
			ai[i] = ri[ ai[i - 1] ] ;
		else if( ai[i - 2] == ri[ ai[i - 1] ] )
			ai[i] = li[ ai[i - 1] ] ;
		else error() ;
	}
	
	FOR( i , 1 , n )at[ ai[i] ] = i ;
	
	FOR( i , 1 , n ) {
		bi[i] = i - at[i] ;
		if( bi[i] < 0 )bi[i] += n ;
		cnt[ bi[i] ]++ ;
	}
	
	int ans = 0 ;
	FOR( i , 0 , n )chkmax( ans , cnt[i] ) ;
	
	memset( ai , 0 , sizeof ai ) ;
	ai[1] = 1 ; ai[2] = li[1] ;
	FOR( i , 3 , n ) {
		if( ai[i - 2] == li[ ai[i - 1] ] )
			ai[i] = ri[ ai[i - 1] ] ;
		else if( ai[i - 2] == ri[ ai[i - 1] ] )
			ai[i] = li[ ai[i - 1] ] ;
		else error() ;
	}
	
	FOR( i , 1 , n )at[ ai[i] ] = i ;
	
	memset( cnt , 0 , sizeof cnt ) ;
	
	FOR( i , 1 , n ) {
		bi[i] = i - at[i] ;
		if( bi[i] < 0 )bi[i] += n ;
		cnt[ bi[i] ]++ ;
	}
	
	FOR( i , 0 , n )chkmax( ans , cnt[i] ) ;
	
	printf( "%d\n" , n - ans ) ;
	
	return 0 ;
}
