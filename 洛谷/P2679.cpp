#include<cstdio>
#include<cstring>

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

static const int maxn = 2011 ;
static const int maxm = 211 ;
static const int mod = 1e9 + 7 ;

int n ;
int m ;
int K ;

char ai[maxn] ;
char bi[maxn] ;

int F[maxm][maxm] ;
int G[maxm][maxm] ;

inline int add( int x , const int& y ) {
	x += y ; if( x >= mod ) x -= mod ; return x ;
}

int main() {
	
	scanf( n ) ; scanf( m ) ; scanf( K ) ;
	
	scanf( "%s" , ai + 1 ) ;
	scanf( "%s" , bi + 1 ) ;
	
	int ans = 0 ;
	
	F[0][0] = 1 ;
	For( i , 1 , n ) Lop( j , m , 1 ) LOP( k , K , 1 )
		if( ai[i] == bi[j] )
			F[j][k] = add( F[j][k] , add( F[j - 1][k - 1] , G[j - 1][k] ) ) ,
			G[j][k] = add( F[j - 1][k - 1] , G[j - 1][k] ) ;
		else G[j][k] = 0 ;
	
	printf( "%d\n" , F[m][K] ) ;
	
	return 0 ;
}
