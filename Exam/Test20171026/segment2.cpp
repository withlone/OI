#include<cstdio>
#include<cstring>
#include<algorithm>

using std :: sort ;
using std :: lower_bound ;
using std :: upper_bound ;

#define For(i, _l, _r) for (int i = (_l), i##r = (_r) ; i <= (i##r) ; ++i)
#define Lop(i, _l, _r) for (int i = (_l), i##r = (_r) ; i >= (i##r) ; --i)
#define Rep(i, _l, _r) for (int i = (_l) ; i ; i = (_r))

template <typename tp> inline tp max (tp x, tp y) { return x > y? x : y; }
template <typename tp> inline tp min (tp x, tp y) { return x < y? x : y; }
template <typename tp>
inline bool chkmax (tp& x, tp y) { return (x >= y)? (false): (x = y, true) ; }
template <typename tp>
inline bool chkmin (tp& x, tp y) { return (x <= y)? (false): (x = y, true) ; }

static const int len = 1 << 20 | 1 ;
char buffer[len], *Ser, *Ter ;
inline char Getchar() {
	if (Ser == Ter) Ter = (Ser = buffer) + fread (buffer, 1, len, stdin) ;
	return (Ser == Ter)? (char)EOF: (*Ser++) ;
}

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = Getchar() ; tp f = 1 ;
	for (; ch> '9' || ch< '0' ; ch = Getchar()) if (ch == '-') f = -1 ;
	for (; ch>='0' && ch<='9' ; ch = Getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 3e5 + 11 ;
static const int maxm = 6e5 + 11 ;

int n ;
int m ;
int cnt ;

int Fa[maxm] ;
int li[maxm] ;
int ri[maxm] ;
int dep[maxm] ;
int fa[21][maxm] ;

int buc1[maxn] ;
int buc2[maxn] ;
int buc3[maxn] ;

int lti[maxn] ;
int rti[maxn] ;

inline int get_lca (int x, int y) {
	if (dep[x] < dep[y]) x ^= y ^= x ^= y ;
	int delta = dep[x] - dep[y] ;
	For (i, 0, 20) if (delta >> i & 1) x = fa[i][x] ;
	if (x == y) return x ;
	Lop (i, 20, 0) if (fa[i][x] ^ fa[i][y])
		x = fa[i][x], y = fa[i][y] ;
	return fa[0][x] ;
}

inline int get_out (int l, int r) { return buc3[l - 1] + buc3[n] - buc3[r] ; }

inline int get_left (int l) { return buc2[l - 1] ; }

inline int get_right (int r) { return buc1[n] - buc1[r] ; }

void build (int l, int r, int f) {
	int mid ; scanf(mid) ;
	if (mid == -1) {
		dep[l] = dep[f] + 1 ;
		li[l] = ri[l] = l ; Fa[l] = f ; fa[0][l] = f ;
		return ;
	}
	int rt = ++cnt ;
	if (!lti[l]) lti[l] = rt ; if (!rti[r]) rti[r] = rt ;
	buc1[l]++ ; buc2[r]++ ; buc3[l]++ ; buc3[r]++ ;
	dep[rt] = dep[f] + 1 ;
	build (l, mid, rt) ; build (mid + 1, r, rt) ;
	li[rt] = l ; ri[rt] = r ; Fa[rt] = f ; fa[0][rt] = f ;
}

int main() {
	
	freopen ("segment.in", "r", stdin) ;
	freopen ("segment.out", "w", stdout) ;
	
	cnt = scanf(n) ; scanf(m) ;
	
	build (1, n, 0) ;
	
	For (i, 1, 20) For (j, 1, (n << 1) - 1)
		fa[i][j] = fa[i - 1][fa[i - 1][j]] ;
	
	For (i, 1, n)
		buc1[i] += buc1[i - 1], buc2[i] += buc2[i - 1], buc3[i] += buc3[i - 1] ;
	
	while (m--) {
		int x, y, output ;
		scanf(x) ; scanf(y) ;
		int t = get_out (x, y) - ((get_left (x) + get_right (y)) << 1) ;
		int lca = get_lca (x, y) ;
		if (li[lca] == x && ri[lca] == y) lca = Fa[lca] ;
		if (li[lca] == x) lca = Fa[lti[x]] ;
		else if (ri[lca] == y) lca = Fa[rti[y]] ;
		printf ("%d\n", t - dep[lca]) ;
	}
	
	return 0 ;
}
