#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>

#define For(i, _begin, _end) \
for (int i = (_begin), i##end = (_end); i <= (i##end); ++i)
#define Lop(i, _begin, _end) \
for (int i = (_begin), i##end = (_end); i >= (i##end); --i)
#define Rep(i, _begin, _add) \
for (int i = (_begin); i; i = (_add))
#define FOR(i, _begin, _end) \
for (register int i = (_begin), i##end = (_end); i <= (i##end); ++i)
#define LOP(i, _begin, _end) \
for (register int i = (_begin), i##end = (_end); i >= (i##end); --i)
#define REP(i, _begin, _add) \
for (register int i = (_begin); i; i = (_add))

template < typename tp >
inline tp max (const tp&x, const tp& y) { return x > y ? x : y ; }
template < typename tp >
inline tp min (const tp&x, const tp& y) { return x < y ? x : y ; }
template < typename tp >
inline bool chkmax (tp& x, const tp& y)
	{ return ( x >= y ) ? false : ( x = y , true ) ; }
template < typename tp >
inline bool chkmin (tp& x, const tp& y)
	{ return ( x <= y ) ? false : ( x = y , true ) ; }

template < typename tp >
inline tp scanf (tp& in) {
	in = 0; char ch = getchar(); tp f = 1;
	for( ; ch> '9' || ch< '0'; ch = getchar() ) if( ch == '-' ) f = -1 ;
	for( ; ch>='0' && ch<='9'; ch = getchar() ) in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 6e3 + 11 ;
static const int maxm = 12e3 + 11 ;
static const int maxx = 2048583 ;

int n ;
int m ;
int N ;
int M ;
int cnt ;

int bin[23] ;

char cher[maxn] ;
int ai[maxn][611] ;
int bi[maxx] ;

inline void change( char *x , int y ) {
	static bool stack[maxm] ;
	int tp = 0 ;
	For( i , 0 , m - 1 ) {
		x[i] -= 33 ;
		LOP( j , 5 , 0 )
			stack[ ++tp ] = ( x[i] >> j ) & 1 ;
	}
	cnt = 0 ;
	For( i , 1 , M ) {
		++cnt ;
		for( register int j = 19 ; j >= 0 && i <= M ; --j , ++i )
			if( stack[i] ) ai[y][cnt] |= bin[j] ;
		--i ;
	}
}

inline int with( int x , int y ) {
	int res = 0 ;
	FOR( i , 1 , cnt ) {
		res += bi[ ai[x][i] & ai[y][i] ] ;
	}
	return res ;
}

int main() {
	
	freopen( "confess.in" , "r" , stdin ) ;
	freopen( "confess.out" , "w" , stdout ) ;
	
	srand( time( NULL ) ) ;
	
	bin[0] = 1 ;
	FOR( i , 1 , 20 ) bin[i] = bin[i - 1] << 1 ;
	
	FOR( i , 1 , 1 << 20 ) bi[i] = bi[i >> 1] + ( i & 1 ) ;
	
	M = scanf( n ) << 1 ;
	
	m = n / 3 + ( n % 3 != 0 ) ;
	FOR( i , 0 , n ) {
		scanf( "%s" , cher ) ;
		change( cher , i ) ;
	}
	
	N = n >> 1 ;
	Lop( i , n - 1 , 0 ) FOR( j , i + 1 , n )
		if( with( i , j ) >= N )
			return printf( "%d %d\n" , i + 1 , j + 1 ) , 0 ;
	
	puts( "NO Solution" ) ;
	
	return 0 ;
}
