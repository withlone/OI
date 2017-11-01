#include<cstdio>
#include<cstring>

#define For(i, _l, _r) for (int i = (_l), i##r = (_r) ; i <= (i##r) ; ++i)
#define Lop(i, _l, _r) for (int i = (_l), i##r = (_r) ; i >= (i##r) ; --i)
#define Rep(i, _l, _r) for (int i = (_l) ; i ; i = (_r))

template <typename T> inline T max (T x, T y) { return x > y? x: y ; }
template <typename T> inline T min (T x, T y) { return x < y? x: y ; }
template <typename T>
inline bool chkmax (T& x, T y) { return (x >= y)? false: (x = y, true) ; }
template <typename T>
inline bool chkmin (T& x, T y) { return (x <= y)? false: (x = y, true) ; }

template <typename T>
inline T scanf (T& in) {
	in = 0 ; char ch = getchar() ; T f = 1 ;
	for (; ch > '9' || ch < '0' ; ch = getchar()) if (ch == '-') f = -1 ;
	for (; ch >='0' && ch <='9' ; ch = getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 1e6 + 11 ;
static const LL inf = 2147483647 ;

int n ;
int cases ;

char si[maxn] ;

inline bool is_number (char x) {
	return x >= '0' && x <= '9' ;
}

inline bool chk() {
	n = strlen (si) ;
	if (n > 30) return false ;
	if (!is_number (si[n - 1])) return false ;
	int pos = 0, first = 0, second = 0 ;
	For (i, 0, n - 1)
		if (!is_number (si[i]) && si[i] != '-') {
			if (si[i] == ' ') {
				if (!pos) pos = i + 1 ;
				else return false ;
			}
			else return false ;
		} else if (si[i] == '-') {
			if (first && second) return false ;
			else if (first) second = i + 1 ;
			else first = i + 1 ;
		}
	if (!pos) return false ;
	if (si[pos] == '0' && is_number (si[pos + 1]) && pos < n - 1) return false ;
	if (si[0] == '0' && is_number (si[1])) return false ;
	if (first) {
		if (first == 1) {
			if (si[1] < '1' || si[1] > '9') return false ;
		} else {
			if (si[first - 2] != ' ') return false ;
			if (si[first] < '1' || si[first] > '9') return false ;
		}
		if (second) {
			if ((first ^ 1) || second == 1) return false ;
			if (si[second] < '1' || si[second] > '9') return false ;
		}
	}
	int l = 0 ;
	if (si[0] == '-') ++l ;
	for (; si[l] != ' ' && l < n ; ++l) ;
	if (l > 12 || l == n) return false ;
	if (n - 1 - l > 12) return false ;
	return true ;
}

inline LL get_number (char *x, int& p) {
	LL in = 0 ; char ch = x[p++] ; LL f = 1 ;
	for (; !is_number (ch) && p ^ n ; ch = x[p++]) if (ch == '-') f = -1 ;
	for (; is_number (ch) && p ^ n ; ch = x[p++]) in = in * 10 + ch - '0' ;
	return in * f ;
}

int main() {
	
	freopen ("aplusb.in", "r", stdin) ;
	freopen ("aplusb.out", "w", stdout) ;
	
	scanf(cases) ;
	
	while (cases--) {
		scanf ("%[^\n]s", si) ; getchar() ;
		if (!chk()) puts ("Input Error") ;
		else {
			int p = 0 ; ++n ;
			LL a = get_number (si, p) ;
			LL b = get_number (si, p) ;
			if (a > inf || b > inf || a < -inf - 1 || b < -inf - 1 || p != n)
				puts ("Input Error") ;
			else printf ("%lld\n", a + b) ;
		}
	}
	
	return 0 ;
}
