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
static const int p = 2333 ;
static const int max1 = p + 11 ;
static const int max2 = 10 ;

int C[max1][max1] ;
int S[max1][max1] ;

int ni[max2] ;
int mi[max2] ;

int f[max2] ;
int g[max2] ;

inline int add (int x, int y) {
	x += y ; if (x >= p) x -= p ; return x ;
}

int main() {
	
	freopen ("quondam.in", "r", stdin) ;
	freopen ("quondam.out", "w", stdout) ;
	
	S[0][0] = C[0][0] = 1 ;
	For (i, 1, p) {
		S[i][0] = C[i][0] = 1 ;
		For (j, 1, i) C[i][j] = add (C[i - 1][j - 1], C[i - 1][j]) ;
	}
	
	For (i, 0, p) For (j, 1, p) S[i][j] = add (S[i][j - 1], C[i][j]) ;
	
	int cases ;
	
	scanf(cases) ;
	
	while (cases--) {
		LL n, m ;
		scanf(n) ; scanf(m) ;
		
		memset (ni, 0, sizeof ni) ;
		memset (mi, 0, sizeof mi) ;
		
		for (; n ; n /= p) ni[++ni[0]] = n % p ;
		for (; m ; m /= p) mi[++mi[0]] = m % p ;
		
		f[ni[0] + 1] = 1 ;
		Lop (i, ni[0], 1) f[i] = f[i + 1] * C[ni[i]][mi[i]] % p ;
		
		g[0] = 1 ;
		For (i, 1, ni[0]) g[i] = g[i - 1] * S[ni[i]][p - 1] % p ;
		
		int ans = f[1] ;
		For (i, 1, mi[0])
			ans = add (ans, f[i + 1] * g[i - 1] % p * S[ni[i]][mi[i] - 1] % p) ;
		
		printf ("%d\n", ans) ;
		
	}
	
	return 0 ;
}
