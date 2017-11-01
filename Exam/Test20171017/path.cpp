#include<cstdio>
#include<cstring>
#include<algorithm>

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

typedef long long LL ;
static const int maxn = 511 ;
static const int inf = 2139062143 ;

int n ;
int m ;

int id[maxn] ;
int vi[maxn] ;

int g[maxn][maxn] ;
LL f[maxn][maxn] ;

inline bool cmp (const int& x, const int& y) {
	return vi[x] < vi[y] ;
}

int main() {
	
	freopen ("path.in", "r", stdin) ;
	freopen ("path.out", "w", stdout) ;
	
	memset (f, 0x7f, sizeof f) ;
	memset (g, 0x7f, sizeof g) ;
	
	scanf(n) ; scanf(m) ;
	FOR (i, 1, n) scanf(vi[i]), id[i] = i ;
	FOR (i, 1, m) {
		int x, y, z ;
		scanf(x) ; scanf(y) ; scanf(z) ;
		g[x][y] = g[y][x] = z ;
	}
	
	std :: sort (1 + id, 1 + n + id, cmp) ;
	
	FOR (K, 1, n) {
		int k = id[K] , vir = vi[k];
		FOR (i, 1, n) FOR (j, 1, n)
			chkmin (g[i][j], max (g[i][k], g[k][j])) ;
		FOR (i, 1, n) if (vi[i] <= vir && (inf ^ g[i][k]))
		FOR (j, 1, n) if (vi[j] <= vir && (inf ^ g[k][j]))
			chkmin (f[i][j], 1LL * vi[k] * max (g[i][k], g[k][j])) ;
	}
	
	FOR (i, 1, n) {
		FOR (j, 1, n)
			if (i == j) printf ("0 ") ;
			else if (f[i][j] == inf) printf ("-1 ") ;
			else printf ("%lld ", f[i][j]) ;
		putchar (10) ;
	}
	
	return 0 ;
}
