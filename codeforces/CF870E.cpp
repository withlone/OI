#include<cstdio>
#include<vector>
#include<algorithm>

#define For(i, _begin, _end) \
for (int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i)
#define Lop(i, _begin, _end) \
for (int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i)
#define Rep(i, _begin, _add) \
for (int i = (_begin) ; i ; i = (_add))
#define FOR(i, _begin, _end) \
for (register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i)
#define LOP(i, _begin, _end) \
for (register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i)
#define REP(i, _begin, _add) \
for (register int i = (_begin) ; i ; i = (_add))

template <typename tp>
inline tp max (const tp& x, const tp& y) { return (x > y)? x: y ; }
template <typename tp>
inline tp min (const tp& x, const tp& y) { return (x < y)? x: y ; }
template <typename tp>
inline bool chkmax (tp& x, const tp& y) {
	return (x >= y) ? (false): (x = y, true) ;
}
template <typename tp>
inline bool chkmin (tp& x, const tp& y) {
	return (x <= y) ? (false): (x = y, true) ;
}

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ; ch> '9' || ch< '0' ; ch = getchar() ) if( ch == '-' ) f = -1 ;
	for( ; ch>='0' && ch<='9' ; ch = getchar() ) in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e5 + 11 ;
static const int maxx = 2e5 + 11 ;
static const int maxm = 4e5 + 11 ;
static const int mod = 1e9 + 7 ;

int n ;
int mx ;
int my ;
int st1 ;
int st2 ;
bool is_ring ;

int xi[maxn] ;
int yi[maxn] ;

bool V[maxn] ;

std :: vector <int> row[maxn] ;
std :: vector <int> line[maxn] ;
std :: vector <int> :: iterator it ;

int same1[maxx] ;
int same2[maxx] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins (int x, int y) {
	Nt[++Ct] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
	Nt[++Ct] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ;
}

inline int dcter (int *x) {
	static int dir[maxn] ;
	FOR (i, 1, n) dir[i - 1] = x[i] ;
	std :: sort (dir, n + dir) ;
	int dt = std :: unique (dir, n + dir) - dir ;
	FOR (i, 1, n) x[i] = std :: lower_bound (dir, dt + dir, x[i]) - dir + 1 ;
	return dt ;
}

void dfs (int x, int f) {
	V[x] = true ;
	same1[st1++] = xi[x] ; same2[st2++] = yi[x] ;
	REP (i, Ht[x], Nt[i]) if (to[i] != f) {
		if (V[to[i]]) is_ring = true ;
		else dfs (to[i], x) ;
	}
}

inline int qpow (int x, int y) {
	int res = 1 ;
	for (; y ; y >>= 1, x = 1LL * x * x % mod)
		if (y & 1) res = 1LL * res * x % mod ;
	return res ;
}

int main() {
	
	scanf(n) ;
	FOR (i, 1, n) scanf(xi[i]) , scanf(yi[i]) ;
	
	mx = dcter (xi) ;
	my = dcter (yi) ;
	
	FOR (i, 1, n)
		row[xi[i]].push_back (i) , line[yi[i]].push_back (i) ;
	
	FOR (i, 1, mx) {
		int lst = 0 ;
		for (it = row[i].begin() ; it != row[i].end() ; it++) {
			if (lst) ins (lst, *it) ;
			lst = *it ;
		}
	}
	FOR (i, 1, my) {
		int lst = 0 ;
		for (it = line[i].begin() ; it != line[i].end() ; it++) {
			if (lst) ins (lst, *it) ;
			lst = *it ;
		}
	}
	
	int ans = 1 ;
	FOR (i, 1, n) if (!V[i]) {
		st1 = st2 = 0 ;
		is_ring = false ;
		dfs (i, 0) ;
		std :: sort (same1, st1 + same1) ; std :: sort (same2, st2 + same2) ;
		int tot = std :: unique (same1, st1 + same1) - same1
				+ std :: unique (same2, st2 + same2) - same2 ;
		ans = 1LL * ans * (qpow (2, tot) - !is_ring) % mod ;
	}
	
	printf ("%d\n", ans) ;
	
	return 0 ;
}
