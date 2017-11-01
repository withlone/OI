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
static const int p = 2333 ;
static const int max1 = p + 11 ;

int cases ;

int C[max1][max1] ;
int S[max1][max1] ;

inline int add (int x, int y) {
	x += y ; if (x >= p) x -= p ; return x ;
}

int lucas (LL n, LL k) {
	if (n <= p) return C[n][k] ;
	return lucas (n / p, k / p) * C[n % p][k % p] % p ;
}

int get_S (LL n, LL k) {
	if (k < 0) return 0 ; if (n <= p) return S[n][k] ;
	return add (get_S (n / p, k / p - 1) * S[n % p][p - 1] % p,
							lucas (n / p, k / p) * S[n % p][k % p] % p) ;
}

int main() {
	
	freopen ("quondam.in", "r", stdin) ;
	freopen ("quondam.out", "w", stdout) ;
	
	C[0][0] = 1 ;
	For (i, 1, p) {
		C[i][0] = 1 ;
		For (j, 1, i)
			C[i][j] = add (C[i - 1][j - 1], C[i - 1][j]) ;
	}
	For (i, 0, p) {
		S[i][0] = C[i][0] ;
		For (j, 1, p) S[i][j] = add (S[i][j - 1], C[i][j]) ;
	}
	
	scanf(cases) ;
	
	while (cases--) {
		LL n, k ;
		scanf(n) ; scanf(k) ;
		printf ("%d\n", get_S (n, k)) ;
	}
	
	return 0 ;
}
