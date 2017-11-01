#include<cstdio>
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

static const int maxn = 2e5 + 11 ;

int n ;
int m ;

int ai[maxn] ;
int bi[maxn] ;
int wi[maxn] ;
int id[maxn] ;

int Fa[maxn] ;
bool ok[maxn] ;

inline bool cmp (const int& x, const int& y) {
	return wi[x] > wi[y] ;
}

int find (int t) { return (t == Fa[t])? t: (Fa[t] = find(Fa[t])) ; }

inline bool merge (int x, int y) {
	int fx = find (x), fy = find (y) ;
	if (fx == fy)
		return ok[fx]? !(ok[fx] = false): false ;
	else {
		if (!ok[fx] & !ok[fy]) return false ;
		Fa[fx] = fy ;
		ok[fy] &= ok[fx] ;
		return true ;
	}
}

int main() {
	
	scanf(n) ; scanf(m) ;
	FOR (i, 1, m)
		scanf(ai[i]), scanf(bi[i]), scanf(wi[i]), id[i] = i ;
	
	std :: sort (1 + id, 1 + m + id, cmp) ;
	
	int ans = 0 ;
	
	FOR (i, 1, n) Fa[i] = i, ok[i] = true ;
	
	FOR (I, 1, m) {
		int i = id[I] ;
		int a = ai[i], b = bi[i], w = wi[i] ;
		if (merge (a, b)) ans += w ;
	}
	
	printf ("%d\n", ans) ;
	
	return 0 ;
}
