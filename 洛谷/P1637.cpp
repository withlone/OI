#include<cstdio>
#include<cstring>
#include<algorithm>

using std :: unique ;
using std :: lower_bound ;

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
static const int maxn = 3e4 + 11 ;

int n ;
int dt ;

LL ai[maxn] ;
LL di[maxn] ;

class bit {
	private :
		LL T[maxn] ;
		inline int lowbit (int x) { return x & -x ; }
	public :
		bit () { memset (T, 0, sizeof T) ; }
		inline void add (int x, LL y) {
			for (int i = x ; i <= dt ; i += lowbit (i))
				T[i] += y ;
		}
		inline LL query (int x) {
			LL res = 0 ;
			for (int i = x ; i ; i -= lowbit (i)) res += T[i] ;
			return res ;
		}
} T1, T2 ;

inline void radix_sort (int l, int r, LL *x) {
	static int ci[65536 + 11] ;
	static LL bi[maxn] ;
	For (t, 0, 3) {
		For (i, 0, 65535) ci[i] = 0 ;
		For (i, l, r) ci[(x[i] >> (t * 16)) & 65535]++ ;
		For (i, 1, 65565) ci[i] += ci[i - 1] ;
		Lop (i, r, l) bi[ci[(x[i] >> (t * 16)) & 65535]--] = x[i] ;
		For (i, l, r) x[i] = bi[i] ;
	}
}

int main() {
	
	scanf(n) ;
	For (i, 1, n) di[i] = scanf(ai[i]) ;
	
	radix_sort (1, n, di) ;
	dt = unique (1 + di, 1 + n + di) - di - 1 ;
	For (i, 1, n) ai[i] = lower_bound (1 + di, 1 + dt + di, ai[i]) - di ;
	
	long long ans = 0 ;
	For (i, 1, n) {
		ans += T2.query (ai[i] - 1) ;
		T1.add (ai[i], 1) ;
		T2.add (ai[i], T1.query (ai[i] - 1)) ;
	}
	
	printf ("%lld\n", ans) ;
	
	return 0 ;
}
