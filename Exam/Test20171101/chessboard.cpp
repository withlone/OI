#include<cstdio>
#include<cstring>

#define For(i, _l, _r) for (int i = (_l), i##r = (_r) ; i <= (i##r) ; ++i)
#define Lop(i, _l, _r) for (int i = (_l), i##r = (_r) ; i >= (i##r) ; --i)
#define Rep(i, _l, _r) for (int i = (_l) ; i ; i = (_r))

template <typename tp> inline tp max (tp x, tp y) { return x > y? x: y ; }
template <typename tp> inline tp min (tp x, tp y) { return x < y? x: y ; }
template <typename tp>
inline bool chkmax (tp& x, tp y) { return (x >= y)? false: (x = y, true) ; }
template <typename tp>
inline bool chkmin (tp& x, tp y) { return (x <= y)? false: (x = y, true) ; }

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for (; ch> '9' || ch< '0' ; ch = getchar()) if( ch == '-' ) f = -1 ;
	for (; ch>='0' && ch<='9' ; ch = getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int mod = 1e9 + 7 ;
static const int max1 = 8 + 3 ;
static const int max2 = 1024 + 11 ;

int n ;

int ans[max1] ;

char bd[max1][max1] ;

int f[max1][max2] ;

inline int add (int x, int y) {
	x += y ; if (x >= mod) x -= mod ; return x ;
}

inline int reduce (int x, int y) {
	x -= y ; if (x < 0) x += mod ; return x ;
}

inline void dp (int limit) {
	static int bin[max1] ;
	memset (f, 0, sizeof f) ; f[0][0] = 1 ;
	int maxsta = 1 ;
	bin[0] = 1 ;
	For (i, 1, n - limit + 1) bin[i] = (maxsta *= limit) ;
	For (i, 0, n - 1) For (j, 0, maxsta - 1) if (f[i][j])
		For (cur, 0, (1 << n) - 1) {
			bool pass = true ;
			static bool V[max1] ;
			memset (V, 0, sizeof V) ;
			For (k, 1, n)
				if (cur >> k - 1 & 1) {
					if (bd[i + 1][k] == '*')
						{ pass = false ; break ; }
				} else {
					For (w, max (1, k - limit + 1), k) V[w] = true ;
				}
			if (!pass) continue ;
			int nxt = 0, lst = j ;
			For (k, 1, n - limit + 1) {
				int now = lst % limit ;
				if (!V[k]) {
					if (now == limit - 1) { pass = false ; break ; }
					nxt += bin[k - 1] * (now + 1) ;
				}
				lst /= limit ;
			}
			if (!pass) continue ;
			f[i + 1][nxt] = add (f[i + 1][nxt], f[i][j]) ;
		}
	int res = 0 ;
	For (i, 0, maxsta - 1) res = add (res, f[n][i]) ;
	ans[limit] = res ;
}

int main() {
	
	freopen ("chessboard.in", "r", stdin) ;
	freopen ("chessboard.out", "w", stdout) ;
	
	scanf ("%d", &n) ;
	For (i, 1, n) scanf ("%s", bd[i] + 1) ;
	
	For (i, 1, n) dp (i) ;
	
	ans[n + 1] = ans[n] ;
	For (i, 0, n) printf ("%d\n", reduce (ans[i + 1], ans[i])) ;
	
	return 0 ;
}
