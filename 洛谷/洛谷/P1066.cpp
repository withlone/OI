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

typedef long long LL ;
static const int maxn = 3e4 + 11 ;
static const int maxm = ( 1 << 9 ) + 11 ;
static const int maxx = 200 + 11 ;
static const LL ten = 1e18 ;

int k ;
int w ;
int n ;

inline int ceil( double x ) {
	return (int)x + ( x - (int)x > 1e-5 ) ;
}

class bint {
	public :
		LL s[maxx] ;
		int len ;
		bint() { len = 1 ; memset( s , 0 , sizeof s ) ; }
		
		void display() ;
} f[maxm] , g[maxm] , ans ;

bint operator + ( const bint& x , const bint& y ) {
	bint res ;
	res.len = max( x.len , y.len ) + 1 ;
	FOR( i , 1 , res.len ) {
		res.s[i] += x.s[i] + y.s[i] ;
		res.s[i + 1] += res.s[i] / ten ;
		res.s[i] %= ten ;
	}
	while( !res.s[res.len] && res.len > 1 ) --res.len ;
	return res ;
}

inline void bint :: display() {
	printf( "%lld" , s[len] ) ;
	LOP( i , len - 1 , 1 ) printf( "%018lld" , s[i] ) ;
	putchar( 10 ) ;
}

int main() {
	
	scanf( k ) ; scanf( w ) ;
	
	n = ceil( w * 1.0 / k ) - 1 ;
	
	int tot = 1 << k ;
	FOR( i , 1 , ( 1 << k ) - 1 ) g[i].s[1] = --tot ;
	
	For( i , 1 , n - 1 ) {
		LOP( j , ( 1 << k ) - i , 1 )
			f[j] = g[j + 1] , ans = ans + f[j] ;
		LOP( j , ( 1 << k ) - i , 1 )
			g[j] = g[j + 1] + f[j] ;
	}
	
	FOR( i , 1 , ( 1 << w - k * n ) - 1 )
		ans = ans + g[i + 1] ;
	
	ans.display() ;
	
	return 0 ;
}
