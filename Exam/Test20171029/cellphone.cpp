#include<set>
#include<cstdio>
#include<algorithm>

using namespace std ;

#define For(i, _l, _r) for (int i = (_l), i##r = (_r) ; i <= (i##r) ; ++i)
#define Lop(i, _l, _r) for (int i = (_l), i##r = (_r) ; i >= (i##r) ; --i)
#define Rep(i, _l, _r) for (int i = (_l) ; i ; i = (_r))

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

typedef long long LL ;
static const int maxn = 2e5 + 11 ;
static const int inf = 1e9 ;

int m ;
LL c ;

char si[11] ;

class data {
	public :
		int l ;
		int r ;
		int v ;
		
		data () { l = r = v = 0 ; }
		data (int a, int b, int c) { l = a ; r = b ; v = c ; }
		
		bool operator < (const data& t) const {
			if (l ^ t.l) return l < t.l ;
			if (r ^ t.r) return r < t.r ;
			return v < t.v ;
		}
} ;

set <data> ster ;
set <data> :: iterator it, nxt ;

inline int g_lt (int l, int r, int v) { return r - ((r - l) / v) * v ; }
inline int g_rt (int l, int r, int v) { return ((r - l) / v) * v + l ;}

inline void construct (int l, int r, int v) {
	r = g_rt (l, r, v) ;
	data newber = data (l, r, v) ;
	it = ster.upper_bound (newber) ;
	if (it != ster.begin()) {
		--it ;
		if (it -> l < l && r < it -> r) {
			data t1 = data (it -> l, g_rt (it -> l, l, it -> v), it -> v) ;
			data t2 = data (g_lt (r, it -> r, it -> v), it -> r, it -> v) ;
			ster.erase (*it) ; ster.insert (t1) ; ster.insert (t2) ;
		}
	}
	ster.insert (newber) ;
}

inline void destruct (int l, int r) {
	it = ster.lower_bound (data (l, 0, 0)) ;
	if (it != ster.begin()) {
		nxt = it-- ;
		if (it -> l >= l) ster.erase (*it) ;
		else if (it -> r >= l) {
			if (it -> r > r) {
				data t2 = data (g_lt (r + 1, it -> r, it -> v),
															it -> r, it -> v) ;
				ster.insert (t2) ;
			}
			data t1 = data (it -> l, g_rt (it -> l, l - 1, it -> v), it -> v) ;
			ster.erase (*it) ; ster.insert (t1) ;
		}
		it = nxt ;
	}
	while (it -> r <= r && it != ster.end())
		nxt = ++it, ster.erase (*(--it)), it = nxt ;
	if (it != ster.end()) {
		if (it -> l <= r) {
			if (it -> l < l) {
				data t2 = data (it -> l, g_rt (it -> l, l - 1, it -> v),
																	it -> v) ;
				ster.insert (t2) ;
			}
			data t1 = data (g_lt (r + 1, it -> r, it -> v), it -> r, it -> v) ;
			ster.erase (*it) ; ster.insert (t1) ;
		}
	}
}

inline int ceil (int x, int y) { return x / y + (x % y != 0) ; }

inline LL query (int x) {
	int res = inf ;
	it = ster.lower_bound (data (x, 0, 0)) ;
	if (it != ster.end()) chkmin (res, it -> l - x) ;
	if (it != ster.begin()) {
		--it ;
		if (it -> r < x) chkmin (res, x - it -> r) ;
		else {
			int k = ceil ((x - it -> l), it -> v) ;
			chkmin (res, it -> l + k * it -> v - x) ;
			if (k) chkmin (res, x - (it -> l + (k - 1) * it -> v)) ;
		}
	}
	return max (0LL, c - 1LL * res * res) ;
}

int main() {
	
	freopen ("cellphone.in", "r", stdin) ;
	freopen ("cellphone.out", "w", stdout) ;
	
	scanf(m) ; scanf(c) ;
	
	while (m--) {
		int x, y, z ;
		scanf ("%s", si) ; scanf(x) ;
		if (si[0] == 'c')
			scanf(y), scanf(z), construct (x, y, z) ;
		else if (si[0] == 'd')
			scanf(y), destruct (x, y) ;
		else
			printf ("%lld\n", query (x)) ;
	}
	
	return 0 ;
}
