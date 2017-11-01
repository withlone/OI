#include<cstdio>

#define For(i, _l, _r) for (int i = (_l), i##r = (_r) ; i <= (i##r) ; ++i)
#define Lop(i, _l, _r) for (int i = (_l), i##r = (_r) ; i >= (i##r) ; --i)
#define Rep(i, _l, _r) for (int i = (_l) ; i ; i = (_r))

template <typename tp> inline tp max (tp x, tp y) { return x > y? x: y ; }
template <typename tp> inline tp min (tp x, tp y) { return x < y? x: y ; }
template <typename tp>
inline bool chkmax (tp& x, tp y) { return (x >= y)? false: (x = y, true) ; }
template <typename tp>
inline bool chkmin (tp& x, tp y) { return (x <= y)? false: (x = y, true) ; }

static const int len = 1 << 20 | 1 ;
char buffer[len], *Ser, *Ter ;
inline char Getchar() {
	if (Ser == Ter) Ter = (Ser = buffer) + fread (buffer, 1, len, stdin) ;
	return (Ser == Ter)? (char)EOF: (*Ser++) ;
}

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for (; ch > '9' || ch < '0' ; ch = getchar()) if (ch == '-') f = -1 ;
	for (; ch >='0' && ch <='9' ; ch = getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int mod = 998244353 ;
static const int max1 = 1e6 + 11 ;

int n ;

int f[max1] ;
LL g[max1] ;

inline int add (int x, int y) {
	x += y ; if (x >= mod) x -= mod ; return x ;
}

inline int calc1 (int n) {
	register int i = 0, res = 0 ;
	for (; g[i + 1] <= n ; ++i)
		res = add (res, f[i + 1] * (i + 1) % mod) ;
	res = add (res, (n - g[i]) * (i + 1) % mod) ;
	return res ;
}

inline int calc2 (int n) {
	register int i = 0, res = 0 ;
	for (; g[i + 1] <= n ; ++i)
		res = add (res, (1LL * (i + 1) *
		((g[i] + g[i + 1] + 1) * f[i + 1] / 2 % mod)) % mod) ;
	res = add (res, ((1LL * (i + 1) % mod) *
	((g[i] + 1 + n) * (n - g[i]) / 2 % mod)) % mod) ;
	return res ;
}

int main() {
	
	freopen ("recursion.in", "r", stdin) ;
	freopen ("recursion.out", "w", stdout) ;
	
	g[1] = f[1] = 1 ;
	For (i, 2, 1e6)
		g[i] = g[i - 1] + (f[i] = (1 + f[i - f[f[i - 1]]])) ;
	
	scanf(n) ;
	printf ("%d ", calc1 (n)) ;
	printf ("%d\n", calc2 (n)) ;
	
	return 0 ;
}
