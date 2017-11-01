#include<set>
#include<cstdio>
#include<algorithm>

using std :: set ;

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
static const int max1 = 1e5 + 11 ;
static const int max2 = 4e5 + 11 ;
static const int max3 = 3e7 + 11 ;

int n ;
int m ;

int l1 ;
int r1 ;
int l2 ;
int r2 ;
int modi ;

int cnt ;

int ci[max1] ;
int wi[max1] ;

int lst[max1] ;
int nxt[max1] ;

int head[max1] ;

set <int> poi[max1] ;

LL tag[max3] ;
int ch[max3][2];

class segment_tree {
	public :
		int root ;
		
		void modify (int& rt, int l, int r) {
			if (!rt) rt = ++cnt ;
			if (l >= l2 && r <= r2) return tag[rt] += modi, void() ;
			int mid = l + r >> 1 ;
			if (mid >= l2) modify (ch[rt][0], l, mid) ;
			if (mid <  r2) modify (ch[rt][1], mid + 1, r) ;
		}
		
		LL query (int rt, int l, int r) {
			if (l == r) return tag[rt] ;
			int mid = l + r >> 1 ;
			if (r1 <= mid) return tag[rt] + query (ch[rt][0], l, mid) ;
			return tag[rt] + query (ch[rt][1], mid + 1, r) ;
		}
} T[max2] ;

#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r

void modify (int rt, int l, int r) {
	if (l >= l1 && r <= r1) return T[rt].modify (T[rt].root, 1, n), void() ;
	int mid = l + r >> 1 ;
	if (mid >= l1) modify (lson) ;
	if (mid <  r1) modify (rson) ;
}

LL query (int rt, int l, int r) {
	if (l == r) return T[rt].query (T[rt].root, 1, n) ;
	int mid = l + r >> 1 ;
	if (l1 <= mid) return T[rt].query (T[rt].root, 1, n) + query (lson) ;
	return T[rt].query (T[rt].root, 1, n) + query (rson) ;
}

int main() {
	
	freopen ("color.in", "r", stdin) ;
	freopen ("color.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ;
	
	For (i, 1, n) {
		scanf(ci[i]) ;
		nxt[head[ci[i]]] = i ; lst[i] = head[ci[i]] ; head[ci[i]] = i ;
		poi[ci[i]].insert (i) ; poi[i].insert (n + 1) ; poi[i].insert (0) ;
	}
	
	For (i, 1, n) nxt[head[ci[i]]] = n + 1 ;
	For (i, 1, n) scanf(wi[i]) ;
	
	For (x, 1, n) {
		l1 = lst[x] + 1, r1 = l2 = x, r2 = n, modi = wi[ci[x]] ;
		modify (1, 1, n) ;
	}
	
	while (m--) {
		int op, x, y ;
		scanf(op) ; scanf(x) ; scanf(y) ;
		if (op == 1) {
			if (ci[x] == y) continue ;
			l1 = lst[x] + 1, r1 = l2 = x, r2 = nxt[x] - 1, modi = -wi[ci[x]] ;
			modify (1, 1, n) ;
			nxt[lst[x]] = nxt[x] ; lst[nxt[x]] = lst[x] ;
			int t1 = *poi[y].lower_bound (x) ;
			set <int> :: iterator it = poi[y].upper_bound (x) ; --it ;
			int t2 = *it ;
			nxt[x] = t1 ; lst[x] = t2 ; nxt[t2] = lst[t1] = x ;
			l1 = lst[x] + 1, r1 = l2 = x, r2 = nxt[x] - 1, modi = wi[y] ;
			modify (1, 1, n) ;
			poi[ci[x]].erase (x) ; poi[y].insert (x) ;
			ci[x] = y ;
		} else l1 = x, r1 = y, printf ("%lld\n", query (1, 1, n)) ;
	}
	
	return 0 ;
}
