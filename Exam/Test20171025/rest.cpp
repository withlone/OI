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

static const int len = 1 << 15 | 1 ;
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

typedef long long LL ;
static const int maxn = 15e5 + 11 ;

int n ;
LL m ;

int Fa[maxn] ;
int size[maxn] ;

class edge {
	public :
		int x ;
		int y ;
		int z ;
		
		bool operator < (const edge& t)
			const { return z < t.z ; }
} e[maxn] ;

int find (int t) { return t == Fa[t]? t: Fa[t] = find (Fa[t]) ; }

inline void radix_sort (int l, int r, edge *x) {
	static int ci[65536 + 11] ;
	static edge bi[maxn] ;
	For (t, 0, 1) {
		memset (ci, 0, sizeof(int) * 65536) ;
		For (i, 0, 65535) ci[i] = 0 ;
		For (i, l, r) ci[(x[i].z >> (t * 16)) & 65535]++ ;
		For (i, 1, 65535) ci[i] += ci[i - 1] ;
		Lop (i, r, l) bi[ci[(x[i].z >> (t * 16)) & 65535]--] = x[i] ;
		memcpy (x, bi, sizeof bi) ;
	}
}

inline LL calc (int x) { return 1LL * x * (x - 1) >> 1 ; }

int main() {
	
	freopen ("rest.in", "r", stdin) ;
	freopen ("rest.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ;
	For (i, 1, n - 1)
		scanf(e[i].x), scanf(e[i].y), scanf(e[i].z) ;
	
	radix_sort (1, n - 1, e) ;
	
	For (i, 1, n) Fa[i] = i, size[i] = 1 ;
	
	LL res = 0LL ;
	For (i, 1, n - 1) {
		int fx = find (e[i].x), fy = find (e[i].y) ;
		if (fx ^ fy) {
			Fa[fx] = fy ;
			res = res - calc (size[fx]) - calc(size[fy]) ;
			size[fy] += size[fx] ;
			res += calc (size[fy]) ;
			if (res >= m) return printf ("%d\n", e[i].z), 0 ;
		}
	}
	
	throw ;
	
	return 0 ;
	
}
