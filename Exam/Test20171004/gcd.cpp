#include<cstdio>
#include<bits/stdc++.h>

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
inline type gcd( const type& x , const type& y )
	{ return !y ? x : gcd( y , x % y ) ; }
template < typename type >
inline type max( const type& x , const type& y ) { return x > y ? x : y ; }
template < typename type >
inline type min( const type& x , const type& y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , const type& y )
	{ return x >= y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , const type& y )
	{ return x <= y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 2e5 + 17 ;
static const int maxm = 5e5 + 29 ;

int n ;
int m ;
int Cnt ;
LL ans ;

int ai[maxn] ;

bool V[maxm] ;
int pr[maxm] ;
int mpr[maxm] ;

bool st[maxn] ;
int cnt[maxm] ;

inline void init() {
	For( i , 2 , 5e5 ) {
		if( !V[i] )pr[ ++Cnt ] = i , mpr[i] = i ;
		FOR( j , 1 , Cnt ) {
			int t = pr[j] * i ;
			if( t > 5e5 )break ;
			V[t] = true ;
			mpr[t] = pr[j] ;
			if( !( i % pr[j] ) )break ;
		}
	}
}

inline LL C( const int& x ) { return 1LL * x * ( x - 1 ) >> 1 ; }

inline void solve( int x , bool f ) {
	static int prt[maxn] ;
	int pt = 0 ;
	while( x != 1 ) {
		int t = prt[ ++pt ] = mpr[x] ;
		while( !( x % t ) )x /= t ;
	}
	For( i , 0 , ( 1 << pt ) - 1 ) {
		int t = 1 , ff = 1 ;
		FOR( j , 1 , pt )
			if( i >> j - 1 & 1 )t *= prt[j] , ff *= -1 ;
		if( f )ans += ff * cnt[t]++ ;
		else ans -= ff * --cnt[t] ;
	}
}

int main() {
	
	freopen( "gcd.in" , "r" , stdin ) ;
	freopen( "gcd.out" , "w" , stdout ) ;
	
	init() ;
	
	scanf( n ) ; scanf( m ) ;
	FOR( i , 1 , n )scanf( ai[i] ) ;
	
	while( m-- ) {
		int x ;
		scanf( x ) ;
		solve( ai[x] , st[x] ^= 1 ) ;
		printf( "%lld\n" , ans ) ;
	}
	
	return 0 ;
}
