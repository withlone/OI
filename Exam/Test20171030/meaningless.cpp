#include<map>
#include<cstdio>
#include<algorithm>

using std :: map ;

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
	in = 0 ; char ch = Getchar() ; tp f = 1 ;
	for (; ch > '9' || ch < '0' ; ch = Getchar()) if (ch == '-') f = -1 ;
	for (; ch >='0' && ch <='9' ; ch = Getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int max1 = 2e5 + 11 ;
static const int max2 = 60 + 11 ;

int n ;
int m ;

LL ans ;

LL ai[max1] ;

LL bin[max2] ;
LL sum[2][max2] ;

map <LL, int> cnt ;

inline void calc (LL x, int f = 1) {
	For (i, 0, 60) sum[x >> i & 1][i] += f ;
}

inline LL add (LL x, LL y, LL mod) {
	x += y ; if (x >= mod) return x - mod ; return x ;
}

inline LL qmul (LL x, LL y, LL mod) {
	x %= mod ; y %= mod ;
	return add ((x * y - (LL)((long double)x / mod * y) * mod), mod, mod) ;
}

inline LL query (LL x) {
	LL res = 0LL ;
	for (register int i = 0 ; i <= 60 ; ++i)
		res = add (res, qmul (bin[i], sum[0][i] * sum[1][i], x), x) ;
	return add (res, res, x) ;
}

int main() {
	
	freopen ("meaningless.in", "r", stdin) ;
	freopen ("meaningless.out", "w", stdout) ;
	
	bin[0] = 1LL ;
	For (i, 1, 60) bin[i] = bin[i - 1] << 1 ;
	
	scanf(n) ; scanf(m) ;
	For (i, 1, n) calc (scanf(ai[i])), cnt[ai[i]]++ ;
	
	while (m--) {
		int op ; LL x, y ;
		scanf(op) ; scanf(x) ;
		if (op == 1) {
			scanf(y) ;
			int t = cnt[x] ;
			if (t)
				cnt[x] = 0, cnt[y] += t,
				calc (x, -t), calc (y, t) ;
		} else printf ("%lld\n", query (x)) ;
	}
	
	return 0 ;
}
