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
static const int maxn = 2e5 + 11 ;
static const int maxm = 17e5 + 11 ;
static const int maxx = 22e5 + 11 ;

int n ;
int m ;
int top ;
int cnt ;

int ai[maxn] ;
int li[maxn] ;
int ri[maxn] ;

int stack[maxn] ;

int T1[maxn] ;
int T2[maxn] ;

int output[maxm] ;

class data {
	public :
		int x ;
		int f ;
		int y1 ;
		int y2 ;
		int id ;
		LL key ;
		
		data () { x = y1 = y2 = id = f = 0 ; }
		data (int a, int b, int c, int d, int e) {
			x = a ; y1 = b ; y2 = c ; id = d ; f = e ;
			key = ((x * 1LL) << 31) + id ;
		}
		
		bool operator < (const data& t) const {
			if (x ^ t.x) return x < t.x ;
			return id < t.id ;
		}
} d[maxx] ;

inline int lowbit (int x) { return x & -x ; }

inline void add (int x, int y) {
	for (int i = x, ader = x * y ; i <= n ; i += lowbit (i))
		T1[i] += y, T2[i] += ader ;
}

inline int query (int x) {
	int res = 0 ;
	for (int i = x ; i ; i -= lowbit (i))
		res += (x + 1) * T1[i] - T2[i] ;
	return res ;
}

inline void radix_sort (int l, int r, data *ai) {
	static int ci[65536 + 11] ;
	static data bi[maxx] ;
	
	For (i, l, r) ++ci[ai[i].key & 65535] ;
	For (i, 1, 65535) ci[i] += ci[i - 1] ;
	Lop (i, r, l) bi[ci[ai[i].key & 65535]--] = ai[i] ;
	For (i, l, r) ai[i] = bi[i] ;
	
	memset (ci, 0, sizeof ci) ;
	For (i, l, r) ++ci[(ai[i].key >> 16) & 65535] ;
	For (i, 1, 65535) ci[i] += ci[i - 1] ;
	Lop (i, r, l) bi[ci[(ai[i].key >> 16) & 65535]--] = ai[i] ;
	For (i, l, r) ai[i] = bi[i] ;
	
	memset (ci, 0, sizeof ci) ;
	For (i, l, r) ++ci[(ai[i].key >> 32) & 65535] ;
	For (i, 1, 65535) ci[i] += ci[i - 1] ;
	Lop (i, r, l) bi[ci[(ai[i].key >> 32) & 65535]--] = ai[i] ;
	For (i, l, r) ai[i] = bi[i] ;
	
	memset (ci, 0, sizeof ci) ;
	For (i, l, r) ++ci[(ai[i].key >> 48) & 65535] ;
	For (i, 1, 65535) ci[i] += ci[i - 1] ;
	Lop (i, r, l) bi[ci[(ai[i].key >> 48) & 65535]--] = ai[i] ;
	For (i, l, r) ai[i] = bi[i] ;
}

int main() {
	
	freopen ("permutation.in", "r", stdin) ;
	freopen ("permutation.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ;
	For (i, 1, n) scanf(ai[i]) ;
	
	For (i, 1, n) {
		while (top && ai[stack[top]] < ai[i]) ri[stack[top--]] = i - 1 ;
		li[i] = stack[top] + 1 ; stack[++top] = i ;
	}
	while (top) ri[stack[top--]] = n ;
	
	For (i, 1, n) {
		if (i < ri[i]) {
			d[++cnt] = data(li[i], i + 1, ri[i], 0, 1) ;
			d[++cnt] = data(li[i] + 1, i + 1, ri[i], 0, -1) ;
		}
		if (li[i] < i && ri[i] < n) {
			d[++cnt] = data(li[i] + 1, ri[i] + 1, ri[i] + 1, 0, 1) ;
			d[++cnt] = data(i + 1, ri[i] + 1, ri[i] + 1, 0, -1) ;
		}
	}
	
	For (i, 1, m) {
		int x, y ;
		scanf(x) ; scanf(y) ;
		d[++cnt] = data(x, x + 1, y, i, 0) ;
	}
	
	radix_sort (1, cnt, d) ;
	
	For (i, 1, cnt)
		if (!d[i].id) add (d[i].y1, d[i].f), add (d[i].y2 + 1, -d[i].f) ;
		else if (d[i].y1 <= d[i].y2)
			d[i].f = query (d[i].y2) - query (d[i].y1 - 1) ;
	
	
	For (i, 1, cnt) if (d[i].id > 0) output[d[i].id] = d[i].f ;
	
	For (i, 1, m) printf ("%d\n", output[i]) ;
	
	return 0 ;
}
