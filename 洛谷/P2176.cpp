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

static const int maxn = 111 ;
static const int maxm = 1e4 + 11 ;
static const int mod = (1 << 7) - 1 ;

int n ;
int m ;
int top ;

int Ct = 1 ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;
int Dt[maxm] ;

int f[maxn] ;

int stack[maxn] ;

bool V[maxn] ;
int dis[maxn] ;
int idg[maxn] ;
int que[mod + 11] ;
bool vis[maxm] ;

inline void ins (int x, int y, int z) {
	Nt[++Ct] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
}

inline int spfa () {
	int head = 0, tail = 0 ;
	memset (V, 0, sizeof V) ;
	memset (dis, 0x3f, sizeof dis) ;
	que[++tail] = 1 ; dis[1] = 0 ;
	while (head ^ tail) {
		int x = que[++head &= mod] ; V[x] = false ;
		Rep (i, Ht[x], Nt[i])
			if (dis[to[i]] > dis[x] + Dt[i]) {
				dis[to[i]] = dis[x] + Dt[i] ;
				if (!V[to[i]])
					V[to[i]] = true, que[++tail &= mod] = to[i] ;
			}
	}
	return dis[n] ;
}

inline void tuopo() {
	static int que[maxn] ;
	int head = 0, tail = 0 ;
	que[++tail] = 1 ; f[1] = 1 ;
	while (head ^ tail) {
		int x = que[++head] ;
		Rep (i, Ht[x], Nt[i]) if (vis[i]) {
			f[to[i]] += f[x] ;
			if (!--idg[to[i]]) que[++tail] = to[i] ;
		}
	}
	For (I, 1, tail) {
		int x = que[I] ;
		Rep (i, Ht[x], Nt[i]) if (vis[i])
			if (f[to[i]] == f[x]) stack[++top] = i >> 1 ;
	}
}

int main() {
	
	scanf(n) ; scanf(m) ;
	For (i, 1, m) {
		int x, y, z ;
		scanf(x) ; scanf(y) ; scanf(z) ;
		ins (x, y, z) ; ins (y, x, z) ;
	}
	
	int least = spfa() ;
	For (i, 2, Ct)
		if (dis[to[i]] == dis[to[i ^ 1]] + Dt[i]) vis[i] = true, idg[to[i]]++ ;
	
	tuopo() ;
	
	int ans = 0 ;
	For (i, 1, top) {
		int t = stack[i] ;
		Dt[t << 1] = (Dt[t << 1 | 1] <<= 1) ;
		chkmax (ans, spfa()) ;
		Dt[t << 1] = (Dt[t << 1 | 1] >>= 1) ;
	}
	
	printf ("%d\n", ans - least) ;
	
	return 0 ;
}
