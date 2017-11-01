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

typedef long long LL ;
static const int maxn = 61 ;
static const int mod = 1000003 ;

LL n ;

int g[maxn] ;

inline int add (int x, int y) {
	x += y ; if (x >= mod) x -= mod ; return x ;
}

inline int qpow (int x, int y) {
	int res = 1 ;
	for (; y ; y >>= 1, x = 1LL * x * x % mod)
		if (y & 1) res = 1LL * res * x % mod ;
	return res ;
}

int main() {
	
	scanf(n) ;
	g[0] = 1 ;
	For (i, 1, 60) g[i] = g[i - 1] * 3 % mod ;
	
	int ans = 0, t = 1 ;
	Lop (i, 60, 0)
		if (n >> i & 1) {
			ans = add (ans, 1LL * g[i] * t % mod) ;
			t = (t << 1) % mod ;
		}
	
	ans = (n % mod) * (n % mod + 1) * qpow (2, mod - 2) % mod - ans ;
	
	if (ans < 0) ans += mod ;
	
	printf ("%d\n", ans) ;
	
	return 0 ;
}
