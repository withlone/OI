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

static const int maxn = 2e5 + 17 ;

int n ;
int ans ;

int ai[maxn] ;

int V[maxn] ;

int stack[maxn] ;

int main() {
	
	freopen( "message.in" , "r" , stdin ) ;
	freopen( "message.out" , "w" , stdout ) ;
	
	ans = scanf( n ) ;
	FOR( i , 1 , n ) scanf( ai[i] ) ;
	
	For( i , 1 , n ) if( !V[i] ) {
		register int t = i , dep = 1 , tp = 0 ;
		for( ; !V[t] ; t = ai[t] , ++dep )
			V[t] = dep , stack[ ++tp ] = t ;
		while( tp )
			if( stack[ tp-- ] == t )
				chkmin( ans , dep - V[t] ) ;
	}
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
