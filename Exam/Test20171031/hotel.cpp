#include<cstdio>

#define For(i, _l, _r) for (int i = (_l), i##r = (_r) ; i <= (i##r) ; ++i)
#define Lop(i, _l, _r) for (int i = (_l), i##r = (_r) ; i >= (i##r) ; --i)
#define Rep(i, _l, _r) for (int i = (_l) ; i ; i = (_r))

template <typename tp> inline tp max (tp x, tp y) { return x > y? x: y ; }
template <typename tp> inline tp min (tp x, tp y) { return x < y? x: y ; }
template <typename tp>
inline bool chkmax (tp& x, tp y) { return (x >= y)? false: (x = y, true) ; }
template <typename tp>
inline bool chkmin (tp& x, tp y) { return (x <= y)? false: (x = y, true) ; }

static const int len = 1 << 20 | 1 ;
char buffer[len], *Ser, *Ter ;
inline char Getchar() {
	if (Ser == Ter) Ter = (Ser = buffer) + fread (buffer, 1, len, stdin) ;
	return (Ser == Ter)? (char)EOF: (*Ser++) ;
}

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = Getchar() ; tp f = 1 ;
	for (; ch > '9' || ch < '0' ; ch = Getchar()) if (ch == '-') f = -1 ;
	for (; ch >='0' && ch <='9' ; ch = Getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r
static const int max1 = 3e5 + 11 ;
static const int max2 = 2e6 + 11 ;

int n ;
int m ;

int wi[max1] ;

class data {
	public :
		int len ; int lmax ; int rmax ; LL secmin ; LL ans ; LL tag ;
		
		data () { len = lmax = rmax = secmin = ans = tag = 0 ; }
		data (int a, int b, int c, LL d) {
			len = a ; lmax = b ; rmax = c ; secmin = d ; ans = tag = 0 ;
		}
} T[max2] ;

inline LL sqr (const LL& x) { return x * (x + 1) >> 1 ; }

inline data update (const data& ls, const data& rs) {
	if (!ls.len) return rs ; if (!rs.len) return ls ;
	data res ;
	res.lmax = ls.lmax ; res.rmax = rs.rmax ; res.len = ls.len + rs.len ;
	if (ls.secmin == rs.secmin) {
		res.secmin = ls.secmin ;
		res.ans = ls.ans + rs.ans + 1LL * ls.rmax * rs.lmax ;
	} else if (ls.secmin < rs.secmin) {
		res.secmin = ls.secmin ; res.rmax = rs.len + ls.rmax ;
		res.ans = ls.ans - sqr (ls.rmax) + sqr (res.rmax) ;
	} else {
		res.secmin = rs.secmin ; res.lmax = ls.len + rs.lmax ;
		res.ans = rs.ans - sqr (rs.lmax) + sqr (res.lmax) ;
	}
	return res ;
}

void build (int rt, int l, int r) {
	if (l == r) return T[rt] = data (1, 0, 0, wi[l]), void() ;
	int mid = l + r >> 1 ;
	build (lson) ; build (rson) ;
	T[rt] = update (T[rt << 1], T[rt << 1 | 1]) ;
}

inline void pushdown (int rt) {
	int ls = rt << 1, rs = rt << 1 | 1 ;
	T[ls].tag += T[rt].tag ; T[ls].secmin += T[rt].tag ;
	T[rs].tag += T[rt].tag ; T[rs].secmin += T[rt].tag ;
	T[rt].tag = 0 ;
}

void modify (int rt, int l, int r, int L, int R, int x) {
	if (l >= L && r <= R) return T[rt].secmin += x, T[rt].tag += x, void() ;
	int mid = l + r >> 1 ;
	if (T[rt].tag) pushdown (rt) ;
	if (mid >= L) modify (lson, L, R, x) ;
	if (mid <  R) modify (rson, L, R, x) ;
	T[rt] = update (T[rt << 1], T[rt << 1 | 1]) ;
}

data query (int rt, int l, int r, int L, int R) {
	if (l >= L && r <= R) return T[rt] ;
	int mid = l + r >> 1 ; data res ;
	if (T[rt].tag) pushdown (rt) ;
	if (mid >= L) res = query (lson, L, R) ;
	if (mid <  R) res = update (res, query (rson, L, R)) ;
	return res ;
}

int main() {
	
	freopen ("hotel.in", "r", stdin) ;
	freopen ("hotel.out", "w", stdout) ;
	
	
	scanf(n) ; scanf(m) ;
	For (i, 1, n) scanf(wi[i]) ;
	
	build (1, 1, n) ;
	
	while (m--) {
		int op, l, r, x ;
		scanf(op) ; scanf(l) ; scanf(r) ;
		if (op == 1) scanf(x), modify (1, 1, n, l, r, -x) ;
		else {
			data output = query (1, 1, n, l, r) ;
			if (output.secmin) printf ("%lld\n", sqr (output.len)) ;
			else printf ("%lld\n", output.ans) ;
		}
	}
	
	return 0 ;
}
