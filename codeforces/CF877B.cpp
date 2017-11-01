#include<cstdio>
#include<cstring>

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

static const int maxn = 5e3 + 11 ;

int n ;

char si[maxn] ;

int sum1[maxn] ;
int sum2[maxn] ;

int main () {
	
	scanf ("%s", si + 1) ;
	n = strlen (si + 1) ;
	For (i, 1, n) {
		sum1[i] = sum1[i - 1] ; sum2[i] = sum2[i - 1] ;
		if (si[i] == 'a') sum1[i]++ ;
		else sum2[i]++ ;
	}
	
	int ans = n ;
	For (l, 1, n) For (r, l, n)
		chkmin (ans, sum2[l - 1] + sum2[n] - sum2[r] + sum1[r] - sum1[l - 1]) ;
	
	chkmin (ans, sum2[n]) ;
	
	printf ("%d\n", n - ans) ;
	
	return 0 ;
}
