#include<cstdio>

#define For(i, _l, _r) for (int i = (_l), i##r = (_r) ; i <= (i##r) ; ++i)
#define Lop(i, _l, _r) for (int i = (_l), i##r = (_r) ; i >= (i##r) ; --i)
#define Rep(i, _l, _r) for (int i = (_l) ; i ; i = (_r))

template <typename tp> inline tp max (tp x, tp y) { return x > y? x : y; }
template <typename tp> inline tp min (tp x, tp y) { return x < y? x : y; }
template <typename tp>
inline bool chkmax (tp& x, tp y) { return (x >= y)? (false): (x = y, true) ; }
template <typename tp>
inline bool chkmin (tp& x, tp y) { return (x <= y)? (false): (x = y, true) ; }

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for (; ch> '9' || ch< '0' ; ch = getchar()) if (ch == '-') f = -1 ;
	for (; ch>='0' && ch<='9' ; ch = getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e6 + 11 ;

int n ;
int cases ;

int ans[2][maxn] ;

inline int calc (int n, int m) {
	return 1 + (n - 1) * (m - 1) + ((n - 2) * (m - 2) * (m - 1) >> 1) ;
}

inline void init() {
	For (n, 3, 1e6)
		for (register int m = 1, t ; (t = calc (n, m)) <= 1000000 ; ++m) {
			if (!ans[0][t]) ans[0][t] = n ;
			else if (!ans[1][t]) ans[1][t] = n ;
		}
}

int main() {
	
	init() ;
	
	scanf(cases) ;
	
	while (cases--) {
		scanf(n) ;
		if (ans[0][n] && ans[1][n]) printf ("%d %d\n", ans[0][n], ans[1][n]) ;
		else if (ans[0][n]) printf ("%d\n", ans[0][n]) ;
		else printf ("Poor%d\n", n) ;
	}
	
	return 0 ;
}
