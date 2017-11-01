#include<cstdio>
#include<algorithm>

using std :: sort ;

#define For(i, _l, _r) for (int i = (_l), i##r = (_r) ; i <= (i##r) ; ++i)
#define Lop(i, _l, _r) for (int i = (_l), i##r = (_r) ; i >= (i##r) ; --i)
#define Rep(i, _l, _r) for (int i = (_l) ; i ; i = (_r))

template <typename tp> inline tp max (tp x, tp y) { return x > y? x: y ; }
template <typename tp> inline tp min (tp x, tp y) { return x < y? x: y ; }
template <typename tp>
inline bool chkmax (tp& x, tp y) { return (x >= y)? false: (x = y, true) ; }
template <typename tp>
inline bool chkmin (tp& x, tp y) { return (x <= y)? false: (x = y, true) ; }

static const int len = 1 << 15 ;
char buffer[len], *Ser, *Ter ;
inline char Getchar() {
	if (Ser == Ter) Ter = (Ser = buffer) + fread (buffer, 1, len, stdin) ;
	return (Ser == Ter)? EOF: (*Ser++) ;
}

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = Getchar() ; tp f = 1 ;
	for (; ch > '9' || ch < '0' ; ch = Getchar()) if (ch == '-') f = -1 ;
	for (; ch >='0' && ch <='9' ; ch = Getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 6e5 + 11 ;

int n ;
LL m ;

int ai[maxn] ;
int bi[maxn] ;

namespace idea {
	
	int r1 ;
	int r2 ;
	int r3 ;
	int r4 ;
	
	inline bool chk (LL x) {
		LL res = 0LL ;
		
		int pos = 1 ;
		Lop (i, r1, 1) {
			while (1LL * ai[i] * bi[pos] >= x && pos <= r3) ++pos ;
			res += pos - 1 ;
		}
		
		pos = r3 ;
		Lop (i, n, r2 + 1) {
			while (1LL * ai[i] * bi[pos] >= x && pos > 0) --pos ;
			res += r3 - pos ;
		}
		
		pos = r4 + 1 ;
		For (i, 1, r1 ) {
			while (1LL * ai[i] * bi[pos] >= x && pos <= n) ++pos ;
			res += pos - r4 - 1 ;
		}
		
		pos = n ;
		For (i, r2 + 1, n) {
			while (1LL * ai[i] * bi[pos] >= x && pos > r4) --pos ;
			res += n - pos ;
		}
		
		if (x <= 0LL)
			res += 1LL * (r4 - r3 + r2 - r1) * n - 1LL * (r4 - r3) * (r2 - r1) ;
		return res >= m ;
	}
	
	inline void main() {
		For (i, 1, n) {
			if (ai[i] < 0) r1 = r2 = i ;
			else if (!ai[i]) r2 = i ;
			if (bi[i] < 0) r3 = r4 = i ;
			else if (!bi[i]) r4 = i ;
		}
		
		LL l = -1e18, r = 1e18, res ;
		while (l <= r) {
			LL mid = (l + r) / 2 ;
			if (chk (mid)) res = mid, l = mid + 1 ;
			else r = mid - 1 ;
		}
		printf ("%lld\n", res) ;
	}
}

int main() {
	
	freopen ("kth.in", "r", stdin) ;
	freopen ("kth.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ;
	For (i, 1, n) scanf(ai[i]) ;
	For (i, 1, n) scanf(bi[i]) ;
	
	sort (1 + ai, 1 + n + ai) ;
	sort (1 + bi, 1 + n + bi) ;
	
	idea :: main() ;
	
	return 0 ;
}
