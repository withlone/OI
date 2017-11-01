#include<cstdio>
#include<cstdlib>

#define For(i, _begin, _end) \
for (int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i)
#define Lop(i, _begin, _end) \
for (int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i)
#define Rep(i, _begin, _add) \
for (int i = (_begin) ; i ; i = (_add))
#define FOR(i, _begin, _end) \
for (register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i)
#define LOP(i, _begin, _end) \
for (register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i)
#define REP(i, _begin, _add) \
for (register int i = (_begin) ; i ; i = (_add))

template <typename tp>
inline tp max (const tp& x, const tp& y) { return (x > y)? x: y ; }
template <typename tp>
inline tp min (const tp& x, const tp& y) { return (x < y)? x: y ; }
template <typename tp>
inline bool chkmax (tp& x, const tp& y) {
	return (x >= y) ? (false): (x = y, true) ;
}
template <typename tp>
inline bool chkmin (tp& x, const tp& y) {
	return (x <= y) ? (false): (x = y, true) ;
}

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ; ch> '9' || ch< '0' ; ch = getchar() ) if( ch == '-' ) f = -1 ;
	for( ; ch>='0' && ch<='9' ; ch = getchar() ) in = in * 10 + ch - '0' ;
	return in *= f ;
}

int a ;
int b ;
int f ;
int k ;

int d[3] ;

inline void error() {
	puts ("-1") ;
	exit (0) ;
}

int main() {
	
	scanf(a) ; scanf(b) ; scanf(f) ; scanf(k) ;
	
	d[0] = f , d[1] = a - f ;
	
	int oil = b, to = 1, ans = 0 ;
	while (k--) {
		if (oil < d[to ^ 1]) error() ;
		if (oil < a + d[to] && k) ++ans, oil = b - d[to] ;
		else if (oil < a) ++ans, oil = b - d[to] ;
		else oil -= a ;
		if (oil < 0) error() ;
		to ^= 1 ;
	}
	
	printf ("%d\n", ans) ;
	
	return 0 ;
}
