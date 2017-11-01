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

template < typename tp >
inline tp max( const tp& x , const tp& y ) { return x > y ? x : y ; }
template < typename tp >
inline tp min( const tp& x , const tp& y ) { return x < y ? x : y ; }
template < typename tp >
inline bool chkmax( tp& x , const tp& y ) {
	return ( x >= y ) ? false : ( x = y , true ) ;
}
template < typename tp >
inline bool chkmin( tp& x , const tp& y ) {
	return ( x <= y ) ? false : ( x = y , true ) ;
}

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e5 + 11 ;

int n ;

char cher[maxn] ;

int sum0[maxn] ;
int sum1[maxn] ;

pair < int , int > val[maxn] ;

int main() {
	
	scanf( n ) ;
	scanf( "%s" , cher + 1 ) ;
	FOR( i , 1 , n ) {
		sum0[i] = sum0[i - 1] ;
		sum1[i] = sum1[i - 1] ;
		if( cher[i] == '0' ) sum0[i]++ ;
		else sum1[i]++ ;
		val[i] = pair < int , int > ( sum0[i] - sum1[i] , i ) ;
	}
	
	sort( val , 1 + n + val ) ;
	
	int first = -1 , ans = 0 ;
	FOR( i , 0 , n )
		if( val[first].first != val[i].first ) first = i ;
		else chkmax( ans , val[i].second - val[first].second ) ;
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
