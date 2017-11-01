#include<cstdio>
#include<cstring>

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

static const int maxn = 111 ;
static const int maxm = 1e5 + 11 ;

int n ;
int m ;

int ai[maxn] ;
int bi[maxn] ;
int qi[maxm] ;

inline void radix_sort (int *x) {
	static int ci[65536 + 11] ;
	For (t, 0, 1) {
		memset (ci, 0, sizeof ci) ;
		For (i, 1, n) ci[(ai[i] >> (t * 16)) & 65535]++ ;
		For (i, 1, 65535) ci[i] += ci[i - 1] ;
		Lop (i, n, 1) bi[ci[(ai[i] >> (t * 16)) & 65535]--] = ai[i] ;
		memcpy (ai, bi, sizeof ai) ;
	}
	memset (bi, 0, sizeof bi) ;
}

int main() {
	
	scanf(n) ; scanf(m) ;
	For (i, 1, n) scanf(ai[i]) ;
	radix_sort (ai) ;
	
	qi[0] = 1 ;
	int lst = 0, cnt = 0 ;
	while (cnt < m) {
		int mins = ~0U >> 1, pos = 0 ;
		For (i, 1, n)
			if (chkmin (mins, qi[bi[i]] * ai[i])) pos = i ;
		bi[pos]++ ;
		if (lst ^ mins) qi[++cnt] = mins ;
		lst = mins ;
	}
	printf ("%d\n", qi[cnt]) ;
	
	return 0 ;
}
