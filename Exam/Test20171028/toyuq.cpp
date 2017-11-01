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

static const int maxn = 311 ;
static const int maxm = 611 ;
static const int inf = 1e9 ;

int n ;
int m ;
int ans ;

int wi[maxn] ;
int ti[maxn] ;

int f[maxn][maxn] ;
int g[maxn][maxn] ;
int h[maxn][maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;
int Dt[maxm] ;

inline void ins (int x, int y, int z) {
	Nt[++Ct] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
	Nt[++Ct] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; Dt[Ct] = z ;
}

void dfs (int x, int fa) {
	For (i, 0, m)
		f[x][i] = g[x][i] = h[x][i] = (i >= ti[x])? wi[x] : -inf ;
	Rep (i, Ht[x], Nt[i]) if (to[i] ^ fa) {
		dfs (to[i], x) ;
		int c = Dt[i], son = to[i] ;
		Lop (j, m, c) For (k, 0, j - c) {
			int F = f[x][j], G = g[x][j], H = h[x][j] ;
			chkmax (G, f[x][j - k - c] + g[son][k]) ;
			chkmax (H, g[x][j - k - c] + g[son][k]) ;
			if (j - k - 2 * c >= 0) {
				chkmax (F, f[x][j - k - 2 * c] + f[son][k]) ;
				chkmax (G, g[x][j - k - 2 * c] + f[son][k]) ;
				chkmax (H, h[x][j - k - 2 * c] + f[son][k]) ;
				chkmax (H, f[x][j - k - 2 * c] + h[son][k]) ;
			}
			f[x][j] = F ; g[x][j] = G ; h[x][j] = H ;
		}
	}
	chkmax (ans, h[x][m]) ;
}

int main() {
	
	freopen ("toyuq.in", "r", stdin) ;
	freopen ("toyuq.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ;
	For (i, 1, n) scanf(wi[i]) ;
	For (i, 1, n) scanf(ti[i]) ;
	
	For (i, 1, n - 1) {
		int x, y, z ;
		scanf(x) ; scanf(y) ; scanf(z) ;
		ins (x, y, z) ;
	}
	
	dfs (1, 0) ;
	
	printf ("%d\n", ans) ;
	
	return 0 ;
}
