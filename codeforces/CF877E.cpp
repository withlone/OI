#include<cstdio>

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

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r
static const int maxn = 2e5 + 11 ;
static const int maxm = 8e5 + 11 ;

int n ;
int m ;
int dct ;

char si[11] ;

int Fa[maxn] ;
bool ti[maxn] ;

int li[maxn] ;
int ri[maxn] ;
int dep[maxn] ;
int val[maxn] ;
int size[maxn] ;

bool rev[maxm] ;
int sum[maxm] ;
int tot[maxm] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxn] ;
int to[maxn] ;

inline void ins (int x, int y) {
	Nt[++Ct] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

void dfs (int x) {
	size[x] = 1 ; li[x] = ++dct ;
	Rep (i, Ht[x], Nt[i]) {
		dep[to[i]] = dep[x] + 1 ;
		dfs (to[i]) ;
		size[x] += size[to[i]] ;
	}
	ri[x] = dct ;
}

inline void update (int rt) {
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1] ;
}

inline void pushdown (int rt, int L, int R) {
	int ls = rt << 1, rs = rt << 1 | 1 ;
	rev[rt] = false; rev[ls] ^= 1 ; rev[rs] ^= 1 ;
	sum[ls] = L - sum[ls] ; sum[rs] = R - sum[rs] ;
}

void build (int rt, int l, int r) {
	if (l == r) return sum[rt] = val[l], void() ;
	int mid = l + r >> 1 ;
	build (lson) ; build (rson) ;
	update (rt) ;
}

void modify (int rt, int l, int r, int L, int R) {
	if (l >= L && r <= R)
		return rev[rt] ^= 1, sum[rt] = r - l + 1 - sum[rt], void() ;
	int mid = l + r >> 1 ;
	if (rev[rt]) pushdown (rt, mid - l + 1, r - mid) ;
	if (mid >= L) modify (lson, L, R) ;
	if (mid <  R) modify (rson, L, R) ;
	update (rt) ;
}

int query (int rt, int l, int r, int L, int R) {
	if (l >= L && r <= R) return sum[rt] ;
	int mid = l + r >> 1, res = 0 ;
	if (rev[rt]) pushdown (rt, mid - l + 1, r - mid) ;
	if (mid >= L) res += query (lson, L, R) ;
	if (mid <  R) res += query (rson, L, R) ;
	return res ;
}

int main() {
	
	scanf(n) ;
	For (i, 2, n) ins (scanf(Fa[i]), i) ;
	For (i, 1, n) scanf(ti[i]) ;
	
	dfs (1) ;
	
	For (i, 1, n) val[li[i]] = ti[i] ;
	
	build (1, 1, n) ;
	
	scanf(m) ;
	
	while (m--) {
		int x ;
		scanf ("%s", si) ; scanf(x) ;
		if (si[0] == 'g') printf ("%d\n", query(1, 1, n, li[x], ri[x])) ;
		else modify (1, 1, n, li[x], ri[x]) ;
	}
	
	return 0 ;
}
