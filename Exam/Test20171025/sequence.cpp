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

static const int len = 1 << 15 ;
char buffer[len], *Ser, *Ter ;
inline char Getchar() {
	if (Ser == Ter) Ter = (Ser = buffer) + fread (buffer, 1, len, stdin) ;
	return (Ser == Ter)? EOF: (*Ser++) ;
}

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = Getchar() ; tp f = 1 ;
	for (; ch > '9' || ch < '0' ; ch = Getchar()) if (ch == '-') f = -1 ;
	for (; ch >='0' && ch <='9' ; ch = Getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 5e6 + 11 ;

int n ;
int top ;

int f[maxn] ;
int ai[maxn] ;

int stack[maxn] ;

int main() {
	
	freopen ("sequence.in", "r", stdin) ;
	freopen ("sequence.out", "w", stdout) ;
	
	scanf(n) ;
	For (i, 1, n) scanf(ai[i]) ;
	
	int ans = 0 ;
	
	For (i, 1, n) {
		while (top && ai[stack[top]] > ai[i]) top-- ;
		f[i] = f[stack[top]] + 1 ; chkmax (ans, f[i]) ;
		stack[++top] = i ;
	}
	
	printf ("%d\n", ans) ;
	
	return 0 ;
}
