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
static const int maxn = 5e5 + 11 ;
static const int maxm = 2e6 + 11 ;

template <typename tp>
inline void swap (tp& x, tp& y) { tp t = x ; x = y ; y = t ; }

class edge {
	public :
		int x ; int y ; int z ; int w ;
} e[maxm] ;

class pair {
	public :
		int first ; int second ;
		
		pair () { first = second = 0 ; }
		pair (int a, int b) { first = a ; second = b ; }
		bool operator < (const pair& t) const { return first < t.first ; }
} ;

template <class tp>
class min_heap {
	private :
		int size ;
		tp T[maxm * 10] ;
	public :
		min_heap () { size = 0 ; }
		
		inline void push (tp x) {
			T[++size] = x ;
			int p = size ;
			while ((p ^ 1) && T[p] < T[p >> 1]) {
				swap (T[p], T[p >> 1]) ;
				p >>= 1 ;
			}
		}
		inline void pop() {
			T[1] = T[size--] ;
			int p = 1 ;
			while ((p << 1) <= size && min (T[p << 1], T[p << 1 | 1]) < T[p]) {
				int t = (T[p << 1] < T[p << 1 | 1])? (p << 1): (p << 1 | 1) ;
				swap (T[p], T[t]) ;
				p = t ;
			}
		}
		inline tp top () { return T[1] ; }
		inline bool empty () { return !size ; }
} ;

int n ; 
int m ;
int S ;
int T ;
int top ;

int Fa[maxn] ;

bool V[maxn] ;
LL dis[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;
LL Dt[maxm] ;

inline void ins (int x, int y, LL z) {
	Nt[++Ct] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
	Nt[++Ct] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; Dt[Ct] = z ;
}

int find (int t) { return (t == Fa[t])? t: (Fa[t] = find (Fa[t])) ; }

inline void radix_sort (int l, int r, edge *ai) {
	static int ci[65536 + 11] ;
	static edge bi[maxm] ;
	memset (ci, 0, sizeof ci) ;
	For (i, l, r) ci[ai[i].z & 65535]++ ;
	For (i, 1, 65535) ci[i] += ci[i - 1] ;
	Lop (i, r, l) bi[ci[ai[i].z & 65535]--] = ai[i] ;
	For (i, l, r) ai[i] = bi[i] ;
	
	memset (ci, 0, sizeof ci) ;
	For (i, l, r) ci[(ai[i].z >> 16) & 65535]++ ;
	For (i, 1, 65535) ci[i] += ci[i - 1] ;
	Lop (i, r, l) bi[ci[(ai[i].z >> 16) & 65535]--] = ai[i] ;
	For (i, l, r) ai[i] = bi[i] ;
}

inline LL dijkstra (int S, int T) {
	static min_heap <pair> que ;
	memset (dis, 0x7f, sizeof dis) ;
	que.push (pair (dis[S] = 0, S)) ;
	while (!que.empty()) {
		int x = que.top().second ; que.pop() ;
		if (V[x]) continue ;
		V[x] = true ;
		Rep (i, Ht[x], Nt[i])
			if (dis[to[i]] > dis[x] + Dt[i] && !V[to[i]]) {
				dis[to[i]] = dis[x] + Dt[i] ;
				que.push (pair (dis[to[i]], to[i])) ;
			}
	}
	return dis[T] ;
}

int main() {
	
	freopen ("running.in", "r", stdin) ;
	freopen ("running.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ;
	For (i, 1, m)
		scanf(e[i].x), scanf(e[i].y), scanf(e[i].z), scanf(e[i].w) ;
	scanf(S) ; scanf(T) ;
	
	radix_sort (1, m, e) ;
	
	For (i, 1, n) Fa[i] = i ;
	for (register int i = 1 ; i <= m ; ++i) if (find (e[i].x) ^ find (e[i].y)) {
		Fa[find (e[i].x)] = find (e[i].y) ;
		if (find (S) == find (T)) { top = e[i].z ; break ; }
	}
	
	for (register int i = 1 ; i <= m ; ++i) if (e[i].z <= top)
		ins (e[i].x, e[i].y, 1LL * e[i].z * e[i].w) ;
	
	printf ("%d %lld\n", top, dijkstra (S, T)) ;
	
	return 0 ;
}
