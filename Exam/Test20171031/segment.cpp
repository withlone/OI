#include<cstdio>
#include<algorithm>

using std :: sort ;
using std :: unique ;
using std :: lower_bound ;

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
static const int mod = 998244353 ;
static const int max1 = 1e5 + 11 ;
static const int max2 = 4e5 + 11 ;
static const int max3 = 2e6 + 11 ;

LL n ;
int m ;

int dt ;
LL dir[max2] ;

int sum[max3] ;
int tag[max3] ;

class data {
	public :
		LL l ; LL r ; LL a ;
		bool operator < (const data& t)
			const { return a < t.a ; }
} d[max1] ;

inline int add (int x, int y) {
	x += y ; if (x >= mod) x -= mod ; return x ;
}

inline int mul (int x, int y) {
	return 1LL * x * y % mod ;
}

inline int sqr (int x) {
	return 1LL * x * x % mod ;
}

inline void pushdown (int rt, LL L, LL R) {
	L %= mod ; R %= mod ;
	int ls = rt << 1, rs = rt << 1 | 1 ;
	tag[ls] = tag[rs] = tag[rt] ;
	sum[ls] = mul (L, sqr (tag[rt])) ; sum[rs] = mul (R, sqr (tag[rt])) ;
	tag[rt] = 0 ;
}

void modify (int rt, int l, int r, int L, int R, int a) {
	if (l >= L && r <= R) {
		sum[rt] = mul ((dir[r] - dir[l - 1]) % mod, sqr (tag[rt] = a)) ;
		return ;
	}
	int mid = l + r >> 1 ;
	if (tag[rt]) pushdown (rt, dir[mid] - dir[l - 1], dir[r] - dir[mid]) ;
	if (mid >= L) modify (rt << 1, l, mid, L, R, a) ;
	if (mid <  R) modify (rt << 1 | 1, mid + 1, r, L, R, a) ;
	sum[rt] = add (sum[rt << 1], sum[rt << 1 | 1]) ;
}

int main() {
	
	freopen ("segment.in", "r", stdin) ;
	freopen ("segment.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ;
	For (i, 1, m) {
		dir[++dt] = scanf(d[i].l), dir[++dt] = scanf(d[i].r) ;
		dir[++dt] = d[i].l - 1 ; dir[++dt] = d[i].l + 1 ;
		scanf(d[i].a) ;
	}
	
	sort (1 + d, 1 + m + d) ;
	sort (1 + dir, 1 + dt + dir) ;
	dt = unique (1 + dir, 1 + dt + dir) - dir - 1 ;
	
	For (i, 1, m)
		d[i].l = lower_bound (1 + dir, 1 + dt + dir, d[i].l) - dir,
		d[i].r = lower_bound (1 + dir, 1 + dt + dir, d[i].r) - dir,
		modify (1, 1, dt, d[i].l, d[i].r, d[i].a % mod) ;
	
	printf ("%d\n", sum[1]) ;
	
	return 0 ;
}
