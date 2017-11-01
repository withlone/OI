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

static const int max1 = 1e5 + 11 ;
static const int max2 = 61 ;
static const int max3 = 1e6 + 11 ;
static const int max4 = 8e6 + 11 ;

int n ;
int m ;

char si[max4] ;

int num ;
int root ;

bool mark[max3] ;
int Fa[max3] ;
int ch[max3][10] ;

int find (int t) { return (t == Fa[t])? t: (Fa[t] = find (Fa[t])) ; }

inline void insert (char *xi) {
	int p = root ;
	For (i, 0, n - 1) {
		if (!ch[p][xi[i]]) ch[p][xi[i]] = ++num ;
		p = find (ch[p][xi[i]]) ;
	}
	mark[p] = true ;
}

inline bool query (char *xi) {
	int p = root ;
	For (i, 0, n - 1) {
		if (!ch[p][xi[i]]) return false ;
		p = find (ch[p][xi[i]]) ;
	}
	return mark[p] ;
}

inline int& get (char *xi) {
	int p = root ;
	For (i, 0, n - 2) {
		if (!ch[p][xi[i]]) ch[p][xi[i]] = ++num ;
		p = find (ch[p][xi[i]]) ;
	}
	return ch[p][xi[n - 1]] ;
}

void merge (int& x, int& y) {
	int fx = find (x), fy = find (y) ;
	x = fx ; y = fy ;
	if (!x) return x = fy, void() ;
	if (!y) return y = fx, void() ;
	if (fx == fy) return ;
	Fa[fy] = fx ;
	if (mark[fx] | mark[fy]) mark[fx] = mark[fy] = true ;
	For (i, 0, 9) {
		merge (ch[x][i], ch[fy][i]) ;
		x = find (x) ;
	}
}

inline void transform (char *x) { For (i, 0, strlen (x) - 1) x[i] -= '0' ; }

int main() {
	
	freopen ("quantum.in", "r", stdin) ;
	freopen ("quantum.out", "w", stdout) ;
	
	For (i, 1, max3 - 1) Fa[i] = i ;
	
	root = ++num ;
	
	scanf(m) ;
	
	while (m--) {
		int op ;
		scanf(op) ; scanf ("%s", si) ; n = strlen (si) ; transform (si) ;
		if (op == 1) insert (si) ;
		else if (op == 2) printf ("%d\n", query (si)) ;
		else {
			int& x = get (si) ;
			scanf ("%s", si) ; n = strlen (si) ; transform (si) ;
			int& y = get (si) ;
			if (!x && !y) x = y = ++num ;
			else merge (x, y) ;
		}
	}
	
	return 0 ;
}
