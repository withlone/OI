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
	return x >= y ? false : ( x = y , true ) ;
}
template < typename tp >
inline bool chkmin( tp& x , const tp& y ) {
	return x <= y ? false : ( x = y , true ) ;
}

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}


static const int maxn = 1e4 + 11 ;

int n ;
int x ;
int y ;

int xi[maxn] ;
int yi[maxn] ;
int gi[maxn] ;
int ki[maxn] ;

int main() {
	
	freopen( "carpet.in" , "r" , stdin ) ;
	freopen( "carpet.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	FOR( i , 1 , n )
		scanf( xi[i] ) , scanf( yi[i] ) ,
		gi[i] = xi[i] + scanf( gi[i] ) ,
		ki[i] = yi[i] + scanf( ki[i] ) ;
	scanf( x ) ; scanf( y ) ;
	
	int ans = -1 ;
	FOR( i , 1 , n )
		if( xi[i] <= x && x <= gi[i] && yi[i] <= y && y <= ki[i] )
			ans = i ;
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
