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

static const int maxn = 211 ;

int n ;
int m ;

bool mt[maxn][maxn] ;
int ri[maxn][maxn] ;

inline bool Getbool() {
	char ch = getchar() ;
	while (ch != '.' && ch != '*') ch = getchar() ;
	return (ch == '.')? true: false ;
}

inline void deal (bool *mt, int *ri) {
	int lst = 1 ;
	Lop (i, m, 1)
		if (mt[i]) ri[i] = ri[i + 1] + 1 ;
		else ri[i] = 0 ;
}

inline int solve (int x, int y) {
	int lst = ri[x][y], res = lst ;
	For (i, x + 1, n)
		res += (chkmin (lst, ri[i][y]), lst) ;
	return res ;
}

int main() {
	
	scanf(n) ; scanf(m) ;
	For (i, 1, n) For (j, 1, m)
		mt[i][j] = Getbool() ;
	
	For (i, 1, n)
		deal (mt[i], ri[i]) ;
	
	int ans = 0 ;
	For (i, 1, n) For (j, 1, m) ans += solve (i, j) ;
	
	printf ("%d\n", ans) ;
	
	return 0 ;
}
