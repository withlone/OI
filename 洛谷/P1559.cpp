#include<cstdio>
#include<cstring>

#define For(i, _l, _r) for (int i = (_l), i##r = (_r) ; i <= (i##r) ; ++i)
#define Lop(i, _l, _r) for (int i = (_l), i##r = (_r) ; i >= (i##r) ; --i)
#define Rep(i, _l, _r) for (int i = (_l) ; i ; i = (_r))

template <typename tp> inline tp max (tp x, tp y) { return x > y? x : y; }
template <typename tp> inline tp min (tp x, tp y) { return x < y? x : y; }
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

static const int maxn = 31 ;
static const int maxx = 111 ;
static const int maxm = 1111 ;
static const int mod = (1 << 9) - 1 ;
static const int inf = ~0U >> 1 ;

int n ;
int S ;
int T ;

int pi[maxn][maxn] ;
int qi[maxn][maxn] ;

bool V[maxx] ;
int dis[maxx] ;
int que[mod + 10] ;
int pre[maxx] ;

int Ct = 1 ;
int Ht[maxx] ;
int Nt[maxm] ;
int to[maxm] ;
int Dt[maxm] ;
int cap[maxm] ;

inline void ins (int x, int y, int z) {
	Nt[++Ct] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ; cap[Ct] = 1 ;
	Nt[++Ct] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; Dt[Ct] = -z ; cap[Ct] = 0 ;
}

inline int EK() {
	int res = 0 ;
	while (true) {
		memset (V, 0, sizeof V) ;
		memset (pre, 0, sizeof pre) ;
		memset (dis, -0x3f, sizeof dis) ;
		int head = 0, tail = 0 ;
		que[++tail] = S ; dis[S] = 0 ;
		while (head ^ tail) {
			int x = que[++head &= mod] ; V[x] = false ;
			Rep (i, Ht[x], Nt[i])
				if (dis[to[i]] < dis[x] + Dt[i] && cap[i]) {
					dis[to[i]] = dis[x] + Dt[i] ; pre[to[i]] = i ;
					if (!V[to[i]])
						V[to[i]] = true, que[++tail &= mod] = to[i] ;
				}
		}
		if (dis[T] == dis[T + 1]) return res ;
		int maxflow = inf ;
		for (int i = T ; i ^ S ; i = to[pre[i] ^ 1])
			chkmin (maxflow, cap[pre[i]]) ;
		for (int i = T ; i ^ S ; i = to[pre[i] ^ 1])
			cap[pre[i]] -= maxflow, cap[pre[i] ^ 1] += maxflow ;
		res += maxflow * dis[T] ;
	}
	throw ;
}

int main() {
	
	scanf(n) ;
	For (i, 1, n) For (j, 1, n) scanf(pi[i][j]) ;
	For (i, 1, n) For (j, 1, n) scanf(qi[i][j]) ;
	
	For (i, 1, n) For (j, 1, n)
		ins (i, j + n, pi[i][j] * qi[j][i]) ;
	S = 0 ; T = n << 1 | 1 ;
	For (i, 1, n) ins (S, i, 0), ins (i + n, T, 0) ;
	
	printf ("%d\n", EK()) ;
	
	return 0 ;
}
