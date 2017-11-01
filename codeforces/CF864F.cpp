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

static const int maxn = 3e3 + 1 ;
static const int maxx = 13 ;

int n ;
int m ;
int q ;
int dct ;
int inf ;

short dis[maxn][maxn] ;
short Fa[maxn][maxn][maxx] ;

short dfn[maxn] ;
short low[maxn] ;

bool in[maxn] ;
short stack[maxn] ;

short Ct ;
short Ht[maxn] ;
short Nt[maxn] ;
short to[maxn] ;
short num[maxn] ;
short fir[maxn + 1] ;

inline void ins (short x, short y) {
	Nt[++Ct] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; num[x]++ ;
}

void dfs (short x, short pre, short root, short dep, bool ok) {
	if (ok) Fa[root][x][0] = pre, dis[root][x] = dep ;
	in[x] = true ; dfn[x] = ++dct ; low[x] = inf ;
	FOR (i, fir[x], fir[x + 1] - 1)
		if (!dfn[to[i]])
			dfs (to[i], x, root, dep + 1, ok & (dfn[x] < low[x])),
			chkmin (low[x], low[to[i]]) ;
		else if (in[to[i]])
			chkmin (low[x], dfn[to[i]]) ;
	in[x] = false ;
}

inline void preparation() {
	fir[1] = 1 ;
	FOR (i, 2, n + 1)
		fir[i] = fir[i - 1] + num[i - 1] ;
	short cnt = 0 ;
	FOR (i, 1, n) {
		REP (k, Ht[i], Nt[k])
			num[++cnt] = to[k] ;
		if (fir[i] ^ fir[i + 1]) std :: sort (fir[i] + num, fir[i + 1] + num) ;
	}
	memcpy (to, num, sizeof to) ;
}

inline int query (int x, short fa[maxn][maxx], int k) {
	FOR (i, 0, 12)
		if (k >> i & 1) x = fa[x][i] ;
	return x ;
}

int main() {
	
	register int x, y, z ;
	
	scanf(n) ; scanf(m) ; scanf(q) ; inf = n + 1 ;
	
	FOR (i, 1, m) scanf(x), scanf(y), ins (x, y) ;
	
	preparation() ;
	
	memset (dis, -1, sizeof dis) ;
	FOR (i, 1, n) {
		dct = 0,
		memset (dfn, 0, sizeof dfn),
		memset (low, 0, sizeof low),
		memset (in, 0, sizeof in),
		dfs (i, 0, i, 0, true) ;
		FOR (j, 1, 12) FOR (k, 1, n)
			Fa[i][k][j] = Fa[i][Fa[i][k][j - 1]][j - 1] ;
	}
	
	while (q--) {
		scanf(x) ; scanf(y); scanf(z) ;
		z = dis[x][y] - z + 1 ;
		if (z < 0) puts ("-1") ;
		else printf ("%d\n", query (y, Fa[x], z)) ;
	}
	
	return 0 ;
}
