#include<queue>
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
	for (; ch> '9' || ch < '0' ; ch = getchar()) if (ch == '-') f = -1 ;
	for (; ch>='0' && ch <='9' ; ch = getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r
static const int maxn = 5e5 + 11 ;
static const int maxm = 1e6 + 11 ;
static const int maxx = 2e6 + 11 ;

int n ;
int K ;

int ai[maxn] ;
int bi[maxn] ;

int de[maxn] ;

int T[maxx] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins (int x, int y) {
	if (!x) return ;
	Nt[++Ct] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; de[y]++ ;
}

void modify (int rt, int l, int r, int x, int y) {
	if (l == r) return T[rt] = y, void() ;
	int mid = l + r >> 1 ;
	if (x <= mid) modify (lson, x, y) ;
	else modify (rson, x, y) ;
	T[rt] = max (T[rt << 1], T[rt << 1 | 1]) ;
}

int query (int rt, int l, int r, int L, int R) {
	if (l >= L && r <= R) return T[rt] ;
	int mid = l + r >> 1, res = 0 ;
	if (mid >= L) chkmax (res, query (lson, L, R)) ;
	if (mid <  R) chkmax (res, query (rson, L, R)) ;
	return res ;
}

inline void tuopo() {
	int cnt = 0 ;
	static std :: priority_queue <int> que ;
	FOR (i, 1, n) if (!de[i]) que.push (-i) ;
	while (!que.empty()) {
		bi[++cnt] = -que.top() ; que.pop() ;
		REP (i, Ht[bi[cnt]], Nt[i]) if (!--de[to[i]])
			que.push (-to[i]) ;
	}
}

int main() {
	
	freopen ("permutation.in", "r", stdin) ;
	freopen ("permutation.out", "w", stdout) ;
	
	scanf(n) ; scanf(K) ;
	FOR (i, 1, n) bi[scanf(ai[i])] = i ;
	
	FOR (i, 1, n)
		ins (bi[query (1, 1, n, bi[i], bi[i] + K - 1)], bi[i]),
		modify (1, 1, n, bi[i], i) ;
	
	tuopo() ;
	
	FOR (i, 1, n) ai[bi[i]] = i ;
	
	FOR (i, 1, n) printf ("%d\n", ai[i]) ;
	
	return 0 ;
}
