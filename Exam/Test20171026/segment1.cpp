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
	return (Ser == Ter)? EOF: (*Ser++) ;
}

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = Getchar() ; tp f = 1 ;
	for (; ch > '9' || ch < '0' ; ch = Getchar()) if (ch == '-') f = -1 ;
	for (; ch >='0' && ch <='9' ; ch = Getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 3e5 + 11 ;
static const int maxm = 6e5 + 11 ;

int n ;
int m ;
int cnt ;

int T[maxn] ;

int output[maxn] ;

class data {
	public :
		int x ;
		int y ;
		int id ;
		int ans ;
		
		data () { x = y = id = ans = 0 ; }
		data (int a, int b, int c) { x = a ; y = b ; id = c ; }
} di[maxm] ;

inline bool cmp1 (data a, data b) {
	if (a.x ^ b.x) return a.x < b.x ;
	return a.id > b.id ;
}

inline bool cmp2 (data a, data b) {
	if (a.y ^ b.y) return a.y > b.y ;
	return a.id > b.id ;
}

void build (int l, int r) {
	int mid ; scanf(mid) ;
	if (mid == -1) return ;
	di[++cnt] = data (l, r, 0) ;
	build (l, mid) ; build (mid + 1, r) ;
}

inline int lowbit (int x) { return x & -x ; }

inline void add (int x) {
	for (int i = x ; i <= n ; i += lowbit (i))
		++T[i] ;
}

inline int query (int x) {
	int res = 0 ;
	for (int i = x ; i ; i -= lowbit (i)) res += T[i] ;
	return res ;
}

int main() {
	
	freopen ("segment.in", "r", stdin) ;
	freopen ("segment.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ;
	build (1, n) ;
	For (i, 1, m) {
		++cnt ;
		scanf(di[cnt].x) ; scanf(di[cnt].y) ; di[cnt].id = i ;
	}
	
	sort (1 + di, 1 + cnt + di, cmp1) ;
	For (i, 1, cnt)
		if (!di[i].id) add (di[i].y) ;
		else di[i].ans += query (n) - query (di[i].x - 1) ;
	
	memset (T, 0, sizeof T) ;
	sort (1 + di, 1 + cnt + di, cmp2) ;
	For (i, 1, cnt)
		if (!di[i].id) add (di[i].x) ;
		else di[i].ans += query (di[i].y) - query (di[i].x - 1) ;
	
	For (i, 1, cnt) if (di[i].id) output[di[i].id] = di[i].ans ;
	
	For (i, 1, m) printf ("%d\n", output[i]) ;
	
	return 0 ;
}
