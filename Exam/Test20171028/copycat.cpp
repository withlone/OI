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
	for (; ch > '9' || ch < '0' ; ch = getchar()) if (ch == '-') f = -1 ;
	for (; ch >='0' && ch <='9' ; ch = getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e3 + 11 ;

int n ;
int cases ;

char C[maxn] ;
char J[maxn] ;

char change[maxn] ;

inline bool is_alp (char x) {
	return x >= 'a' && x <= 'z' ;
}

inline bool chk() {
	if ((n = strlen (C)) != strlen (J)) return false ;
	for (register int i = 0 ; i < n ; ++i)
		if (C[i] != J[i]) {
			if (!is_alp (C[i]) || !is_alp (J[i])) return false ;
			if (change[C[i]]) {
				if (change[C[i]] != J[i]) return false ;
			} else change[C[i]] = J[i] ;
		}
	return true ;
}

int main() {
	
	freopen ("copycat.in", "r", stdin) ;
	freopen ("copycat.out", "w", stdout) ;
	
	scanf(cases) ;
	
	while (cases--) {
		scanf ("%[^\n]s", C) ; getchar() ;
		scanf ("%[^\n]s", J) ; getchar() ;
		
		memset (change, 0, sizeof change) ;
		printf ("%d\n", chk()) ;
	}
	
	return 0 ;
}
