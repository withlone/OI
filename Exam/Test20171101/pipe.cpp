#include<cstdio>
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

typedef long long LL ;
static const int max1 = 1e5 + 11 ;
static const int max2 = 2e5 + 11 ;
static const int max3 = 18 + 3 ;

class edge {
	public :
		int x ; int y ; int z ; int id ;
		
		bool operator < (const edge& t) const { return z < t.z ; }
} e[max2] ;

int n ;
int m ;

LL mst ;

int fat[max1] ;

int dep[max1] ;

int Fa[max3][max1] ;
int dx[max3][max1] ;

LL output[max2] ;

int Ct ;
int Ht[max1] ;
int Nt[max2] ;
int to[max2] ;
int Dt[max2] ;

inline void ins (int x, int y, int z) {
	Nt[++Ct] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
	Nt[++Ct] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; Dt[Ct] = z ;
}

int find (int t) { return (t == fat[t])? t: (fat[t] = find (fat[t])) ; }

void dfs (int x) {
	Rep (i, Ht[x], Nt[i]) if (to[i] ^ Fa[0][x]) {
		Fa[0][to[i]] = x ;
		dep[to[i]] = dep[x] + 1 ;
		dx[0][to[i]] = Dt[i] ;
		dfs (to[i]) ;
	}
}

inline int query (int x, int y) {
	if (dep[x] < dep[y]) x ^= y ^= x ^= y ;
	int delta = dep[x] - dep[y], res = 0 ;
	For (i, 0, 18) if (delta >> i & 1)
		chkmax (res, dx[i][x]), x = Fa[i][x] ;
	if (x == y) return res ;
	Lop (i, 18, 0) if (Fa[i][x] ^ Fa[i][y])
		chkmax (res, max (dx[i][x], dx[i][y])),
		x = Fa[i][x], y = Fa[i][y] ;
	return max (res, max (dx[0][x], dx[0][y])) ;
}

int main() {
	
	freopen ("pipe.in", "r", stdin) ;
	freopen ("pipe.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ;
	For (i, 1, m)
		scanf(e[i].x), scanf(e[i].y), scanf(e[i].z), e[i].id = i ;
	
	sort (1 + e, 1 + m + e) ;
	
	For (i, 1, n) fat[i] = i ;
	For (i, 1, m) {
		int fx = find (e[i].x), fy = find (e[i].y) ;
		if (fx ^ fy)
			fat[fx] = fy, ins (e[i].x, e[i].y, e[i].z), mst += e[i].z ;
	}
	
	dep[1] = 1 ;
	dfs (1) ;
	
	For (i, 1, 18) For (j, 1, n)
		Fa[i][j] = Fa[i - 1][Fa[i - 1][j]],
		dx[i][j] = max (dx[i - 1][j], dx[i - 1][Fa[i - 1][j]]) ;
	
	For (i, 1, m)
		output[e[i].id] = mst - query (e[i].x, e[i].y) + e[i].z ;
	
	For (i, 1, m) printf ("%lld\n", output[i]) ;
	
	return 0 ;
}
