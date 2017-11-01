#include<cstdio>
#include<cstring>

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
inline tp max (const tp& x, const tp& y) { return (x > y)? x: y ; }
template <typename tp>
inline tp min (const tp& x, const tp& y) { return (x < y)? x: y ; }
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
	for (; ch> '9' || ch< '0' ; ch = getchar()) if (ch == '-') f = -1 ;
	for (; ch>='0' && ch<='9' ; ch = getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 5e3 + 11 ;

int cases ;
int n ;

int ti[3] ;
int ai[maxn] ;

int f[2][2][maxn] ;
int g[3][2][2][maxn] ;

inline void calc() {
	memset (ti, 0, sizeof ti) ;
	FOR (i, 1, n) ti[ai[i]]++ ;
}

inline void solve() {
	memset (g, -0x3f, sizeof g) ;
	g[2][0][0][0] = 0 ;
	int ans = 0 ;
	FOR (i, 1, n) {
		memset (f, -0x3f, sizeof f) ;
		FOR (d, 0, 2) FOR (d1, 0, 1) FOR (d2, 0, 1) FOR (j, 0, min (ti[2], i)) {
			int t = g[d][d1][d2][j] + 1 ;
			int D1 = d1 or !ai[i], D2 = d2 or (ai[i] == 1) ;
			if (d == 2 && ai[i] == 2) D1 = D2 = 1 ;
			chkmax (f[D1][D2][j + (ai[i] == 2 || (d ^ ai[i]) == 1)], t) ;
		}
		FOR (d1, 0, 1) FOR (d2, 0, 1) FOR (j, 0, min (ti[2], i))
			chkmax (g[ai[i]][d1][d2][j], f[d1][d2][j]) ;
		FOR (j, 0, min (ti[2], i))
			chkmax (ans, f[1][1][j]) ;
		FOR (j, 0, min (ti[2], i) - (ai[i] != 2))
			chkmax (ans, max (f[1][0][j], f[0][1][j])) ;
	}
	printf ("%d\n", n - ans) ;
}

int main() {
	
	freopen ("conjunct.in", "r", stdin) ;
	freopen ("conjunct.out", "w", stdout) ;
	
	scanf(cases) ;
	
	while (cases--) {
		scanf(n) ;
		FOR (i, 1, n) scanf(ai[i]) ;
		calc() ;
		if (!ti[1] || !ti[0]) puts ("0") ;
		else if (!ti[2]) puts ("-1") ;
		else solve() ;
	}
	
	return 0 ;
}
