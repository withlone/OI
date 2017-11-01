#include<cstdio>
#include<algorithm>

#define For(i, _begin, _end) \
for (int i = (_begin), i##end = (_end) ; i <= (i##end) ; ++i)
#define Lop(i, _begin, _end) \
for (int i = (_begin), i##end = (_end) ; i >= (i##end) ; --i)
#define Rep(i, _begin, _add) \
for (int i = (_begin) ; i ; i = (_add))
#define FOR(i, _begin, _end) \
for (register int i = (_begin), i##end = (_end) ; i <= (i##end) ; ++i)
#define LOP(i, _begin, _end) \
for (register int i = (_begin), i##end = (_end) ; i >= (i##end) ; --i)
#define REP(i, _begin, _add) \
for (register int i = (_begin) ; i ; i = (_add))

template <typename tp>
inline tp max (const tp& x, const tp& y) { return (x > y) ? x : y ; }
template <typename tp>
inline tp min (const tp& x, const tp& y) { return (x < y) ? x : y ; }
template <typename tp>
inline bool chkmax (tp& x, const tp& y) {
	return (x >= y)? (false): (x = y, true) ;
}
template <typename tp>
inline bool chkmin (tp& x, const tp& y) {
	return (x <= y)? (false): (x = y, true) ;
}

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for (; ch> '9' || ch< '0' ; ch = getchar() ) if (ch == '-') f = -1 ;
	for (; ch>='0' && ch<='9' ; ch = getchar() ) in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 5e5 + 11 ;
static const double eps = 1e-10 ;

template <typename tp>
inline tp abs (const tp& x) { return x > 0 ? x : -x ; }

inline int cmp (const double& x, const double& y) {
	return abs (x - y) < eps? 0: x - y > 0.0? 1: -1 ;
}

int n ;
int head ;
int tail ;

int xi[maxn] ;
int yi[maxn] ;

int que[maxn] ;

std :: pair <int, int> boot[maxn] ;

inline double slope (int a, int b) {
	return (yi[a] - yi[b]) * 1.0 / (xi[a] - xi[b]) ;
}

inline bool chk (int a, int b, int c) {
	return 1LL * (yi[a] - yi[b]) * (xi[b] - xi[c])
		>= 1LL * (yi[b] - yi[c]) * (xi[a] - xi[b]) ;
}

inline bool chkmax (double& x, const double& y) {
	return (cmp (x, y) != -1)? (false): (x = y, true) ;
}

inline double get (int x) {
	int l = head + 2, r = tail ;
	double res = slope (que[head + 1], x) ;
	while (l <= r) {
		int mid = l + r >> 1 ;
		if (chk (que[mid - 1], x, que[mid]))
			chkmax (res, slope (que[mid - 1], x)), r = mid - 1 ;
		else chkmax (res, slope (que[mid], x)), l = mid + 1 ;
	}
	return res ;
}

int main() {
	
	freopen ("slope.in", "r", stdin) ;
	freopen ("slope.out", "w", stdout) ;
	
	scanf(n) ;
	FOR (i, 1, n) scanf(boot[i].first), scanf(boot[i].second) ;
	
	if (n == 1) return printf ("%.3lf\n", 0.0), 0 ;
	
	std :: sort (1 + boot, 1 + n + boot) ;
	
	FOR (i, 1, n) xi[i] = boot[i].first, yi[i] = boot[i].second ;
	
	double ans = slope (1, 2) ;
	
	que[1] = 1 ; que[2] = 2 ; tail = 2 ;
	FOR (i, 3, n) {
		while (tail - head >= 2 && chk (que[tail - 1], que[tail], i) ) --tail ;
		double temp = get (i) ;
		chkmax (ans, temp) ;
		que[++tail] = i ; ++head ;
	}
	
	printf ("%.3lf\n", ans) ;
	
	return 0 ;
}
