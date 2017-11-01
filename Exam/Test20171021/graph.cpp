#include<cstdio>
#include<cstring>

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

static const int maxn = 1e5 + 11 ;
static const int maxm = 2e5 + 11 ;
static const int maxe = 4e5 + 11 ;

int n ;
int m ;
int sz ;

bool V[maxn] ;
int dep[maxn] ;

bool vis[maxm] ;

int cc[maxn] ;
int ai[maxn] ;
int bi[maxn] ;
int ci[maxn] ;

int Ct = 1 ;
int Ht[maxn] ;
int Nt[maxe] ;
int to[maxe] ;

inline void ins (int x, int y) {
	Nt[++Ct] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

inline void deal (int x, int edge, int y) {
	vis[edge] = true ;
	if (cc[x])
		++sz, ai[sz] = cc[x], bi[sz] = x, ci[sz] = y, cc[x] = 0 ;
	else cc[x] = y ;
}

void dfs (int x, int f, int dept) {
	dep[x] = dept ; V[x] = true ;
	REP (i, Ht[x], Nt[i]) if (i != f) {
		if (!V[to[i]]) {
			dfs (to[i], i ^ 1, dept + 1) ;
			if (!vis[i >> 1]) deal (x, i >> 1, to[i]) ;
		} else if (dep[to[i]] >= dep[x] && !vis[i >> 1])
			deal (x, i >> 1, to[i]) ;
	}
	if (cc[x] && to[f])
		deal (x, f >> 1, to[f]) ;
}

int main() {
	
	freopen ("graph.in", "r", stdin) ;
	freopen ("graph.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ;
	FOR (i, 1, m) {
		int x, y ;
		scanf(x) ; scanf(y) ;
		ins (x, y) ; ins (y, x) ;
	}
	
	FOR (i, 1, n) if (!V[i]) dfs (i, 0, 1) ;
	
	printf ("%d\n", sz) ;
	FOR (i, 1, sz) printf ("%d %d %d\n", ai[i], bi[i], ci[i]) ;
	
	return 0 ;
}
