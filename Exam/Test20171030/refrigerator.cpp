#include<cstdio>
#include<cstring>
#include<algorithm>

using std :: sort ;

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

static const int mod = 19260817 ;
static const int max1 = 511 ;
static const int max2 = 1e5 + 11 ;

int n ;
int m ;

int sum ;

int f[max2] ;
int g[max2] ;

class card {
	public :
		int k ;
		int d ;
		
		bool operator < (const card& t)
		 	const { return d < t.d ; }
} bt[max1] ;

inline int add (int x, int y) {
	x += y ; if (x >= mod) x -= mod ; return x ;
}

inline int reduce (int x, int y) {
	x -= y ; if (x < 0) x += mod ; return x ;
}

inline void update (int k, int d) {
	For (b, 0, d - 1) {
		int sum = 0, head = 0 ;
		For (i, 0, (m - b) / d) {
			sum = add (sum, g[b + i * d]) ;
			while (i - head > k) sum = reduce (sum, g[b + (head++) * d]) ;
			f[b + i * d] = sum ;
		}
	}
}

int main() {
	
	freopen ("refrigerator.in", "r", stdin) ;
	freopen ("refrigerator.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ;
	For (i, 1, n) sum += scanf(bt[i].k) * scanf(bt[i].d) ;
	sort (1 + bt, 1 + n + bt) ;
	
	if (sum <= m) return puts ("1"), 0 ;
	
	int ans = 0 ;
	
	g[0] = 1 ;
	Lop (i, n, 1) {
		sum -= bt[i].k * bt[i].d ;
		update (bt[i].k - 1, bt[i].d) ;
		For (j, max (0, m - sum - bt[i].d), m - sum - 1) ans = add (ans, f[j]) ;
		update (bt[i].k, bt[i].d) ;
		memcpy (g, f, sizeof g) ;
	}
	
	printf ("%d\n", ans) ;
	
	return 0 ;
}
