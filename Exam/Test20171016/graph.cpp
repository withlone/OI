#include<cstdio>
#include<cstring>

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

static const int maxn = 111 ;
static const int inf = 1061109567 ;

int n ;
int m ;
int e ;
int q ;

class graph {
	public :
		int dis[maxn][maxn] ;
		
		graph () { memset (dis, 0x3f, sizeof dis) ; }
		
} boot , ans ;

graph operator + (const graph& x, const graph& y) {
	graph res ;
	FOR (i, 1, n) FOR (j, 1, n) FOR (k, 1, n)
		chkmin (res.dis[i][j], x.dis[i][k] + y.dis[k][j]) ;
	return res ;
}

int main() {
	
	freopen ("graph.in", "r", stdin) ;
	freopen ("graph.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ; scanf(e) ;
	FOR (i, 1, m) {
		int x, y, z ;
		scanf(x) ; scanf(y) ; scanf(z) ;
		boot.dis[x][y] = boot.dis[y][x] = z ;
	}
	
	ans = boot ;
	for (--e ; e ; e >>= 1, boot = boot + boot)
		if (e & 1) ans = ans + boot ;
	
	scanf(q) ;
	
	while (q--) {
		int x, y ;
		scanf(x) ; scanf(y) ;
		int output = ans.dis[x][y] ;
		if (output == inf) output = -1 ;
		printf ("%d\n", output) ;
	}
	
	return 0 ;
}
