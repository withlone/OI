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

static const int len = 1 << 20 | 1 ;
char buffer[len], *Ser, *Ter ;
inline char Getchar() {
	if (Ser == Ter) Ter = (Ser = buffer) + fread (buffer, 1, len, stdin) ;
	return (Ser == Ter)? EOF: (*Ser++) ;
}

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = Getchar() ; tp f = 1 ;
	for (; ch> '9' || ch< '0' ; ch = Getchar()) if (ch == '-') f = -1 ;
	for (; ch>='0' && ch<='9' ; ch = Getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 2e5 + 11 ;

int n ;
int m ;
int *top ;

int ai[maxn] ;
int ri[maxn] ;

int f[maxn] ;
int g[maxn] ;

int stack[maxn] ;

int bin[20] ;
int Log[maxn] ;
int ST[19][maxn] ;

inline int get_max (int x, int y) {
	return (ai[x] > ai[y])? x: y ;
}

inline int query (int l, int r) {
	int t = Log[r - l + 1] ;
	return get_max (ST[t][l], ST[t][r + 1 - bin[t]]) ;
}

int main() {
	
	freopen ("permutation.in", "r", stdin) ;
	freopen ("permutation.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ;
	For (i, 1, n) scanf(ai[i]), ST[0][i] = i ;
	
	bin[0] = 1 ;
	For (i, 1, 18) bin[i] = bin[i - 1] << 1 ;
	For (i, 2, n) Log[i] = Log[i >> 1] + 1 ;
	
	For (i, 1, 18) Lop (j, n, 1)
		if (j + bin[i - 1] <= n)
			ST[i][j] = get_max (ST[i - 1][j], ST[i - 1][j + bin[i - 1]]) ;
		else ST[i][j] = ST[i - 1][j] ;
	
	top = stack ;
	Lop (i, n, 1) {
		while (top != stack && ai[*top] < ai[i]) top-- ;
		if (top == stack) ri[i] = n + 1 ;
		else ri[i] = *top ;
		*(++top) = i ;
	}
	
	Lop (i, n, 1) f[i] = f[ri[i]] + 1 ;
	Lop (i, n, 1) g[i] = g[ri[i]] + ri[i] - 1 - i ;
	
	while (m--) {
		int l, r, output = 0 ;
		scanf(l) ; scanf(r) ;
		int pos = query (l, r) ;
		if (ri[l - 1] <= r)
			output = f[l - 1] - f[pos] - 1 + g[l] - g[ri[l - 1]] ;
		else
			output = g[l] - g[pos] + r - pos ;
		printf ("%d\n", output) ;
	}
	
	return 0 ;
}
