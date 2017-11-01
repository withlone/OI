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
inline bool chkmax( type& x , const type& y )
	{ return x > y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , const type& y )
	{ return x < y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 5e6 + 11 ;
static const int mod = 100000007 ;

int n ;
int cnt ;
int ans ;

int ki[maxn] ;

bool V[maxn] ;
int pr[maxn] ;

inline void get_prime() {
	For( i , 2 , n ) {
		if( !V[i] )pr[ ++cnt ] = i ;
		for( register int j = 1 ; j <= cnt && pr[j] * i <= n ; ++j ) {
			V[ pr[j] * i ] = true ;
			if( !( i % pr[j] ) )break ;
		}
	}
}

inline int qpow( int x , int y ) {
	int res = 1 ;
	for( ; y ; y >>= 1 , x = 1LL * x * x % mod )
		if( y & 1 )res = 1LL * res * x % mod ;
	return res ;
}

int main() {
	
	freopen( "number.in" , "r" , stdin ) ;
	freopen( "number.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	
	get_prime() ;
	
	For( i , 1 , cnt )
		for( register LL t = pr[i] ; t <= n ; t = t * pr[i] )
			ki[i] += n / t ;
	
	ans = 1 ;
	For( i , 1 , cnt )
		ans = 1LL * ans * qpow( pr[i] , ki[i] - ( ki[i] & 1 ) ) % mod ;
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
