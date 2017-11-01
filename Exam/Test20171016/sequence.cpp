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

typedef long long LL ;
static const int maxn = 2e5 + 11 ;
static const int maxm = 8e5 + 11 ;

int n ;
int m ;
int k ;
int q ;

int ai[maxn] ;
int ri[maxn] ;
LL sum[maxn] ;

namespace init {
	int dt ;
	
	int sz[maxm] ;
	int dir[maxn] ;
	
	void insert (int rt, int l, int r, int x, int y) {
		sz[rt] += y ;
		if (l == r) return ;
		int mid = l + r >> 1 ;
		if (x <= mid) insert (rt << 1, l, mid, x, y) ;
		else insert (rt << 1 | 1, mid + 1, r, x, y) ;
	}
	
	int query (int rt, int l, int r, int k) {
		if (l == r) return l ;
		int mid = l + r >> 1 ;
		if (sz[rt << 1 | 1] >= k) return query (rt << 1 | 1, mid + 1, r, k) ;
		return query (rt << 1, l, mid, k - sz[rt << 1 | 1]) ;
	}
	
	inline void initer() {
		dir[0] = m ;
		FOR (i, 1, n) dir[i] = ai[i] ;
		std :: sort (dir, 1 + n + dir) ;
		dt = std :: unique (dir, 1 + n + dir) - dir ;
		m = std :: lower_bound (dir, dt + dir, m) - dir ;
		FOR (i, 1, n)
			ai[i] = std :: lower_bound (dir, dt + dir, ai[i] ) - dir ;
	}
	
	inline void main() {
		initer() ;
		int boot = 0 ;
		FOR (i, 1, n) {
			while (boot < n && (sz[1] < k || query (1, 1, dt, k) < m))
				insert (1, 1, dt, ai[++boot], 1) ;
			if (sz[1] >= k && query (1, 1, dt, k) >= m)
				ri[i] = boot ;
			insert (1, 1, dt, ai[i], -1) ;
		}
		FOR (i, 1, n) {
			if (!ri[i]) ri[i] = n + 1 ;
			sum[i] = sum[i - 1] + ri[i] ;
		}
	}
}

int main() {
	
	freopen ("sequence.in", "r", stdin) ;
	freopen ("sequence.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ; scanf(k) ;
	FOR (i, 1, n) scanf (ai[i]) ;
	
	init :: main() ;
	
	scanf(q) ;
	
	while (q--) {
		int l, x ;
		scanf(l) ; scanf(x) ;
		int r = std :: upper_bound (1 + ri, 1 + n + ri, x) - ri - 1 ;
		if (l > r) puts("0") ;
		else
		printf ("%lld\n", 1LL * (r - l + 1) * (x + 1) - sum[r] + sum[l - 1]) ;
	}
	
	return 0 ;
}
