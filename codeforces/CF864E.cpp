#include<cstdio>
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

static const int maxn = 2e3 + 11 ;
static const int maxm = 111 ;

int n ;

int py[maxn] ;

int f[maxm][maxn] ;
std :: pair <int, int> g[maxm][maxn] ;

class boot {
	public :
		int t ;
		int d ;
		int p ;
		int id ;
		
		bool operator < (const boot& x) const {
			return d < x.d ;
		}
} bt[maxm] ;

void print (std :: pair <int, int> play) {
	if (!play.first) return ;
	std :: pair <int, int> pre = g[play.first][play.second] ;
	print (pre) ;
	if (play.second != pre.second) py[++py[0]] = bt[play.first].id ;
}

int main() {
	
	scanf(n) ;
	FOR (i, 1, n) scanf(bt[i].t), scanf(bt[i].d), scanf(bt[i].p), bt[i].id = i ;
	
	std :: sort (1 + bt, 1 + n + bt) ;
	
	FOR (i, 1, n) FOR (j, 0, 2000) {
		f[i][j] = f[i - 1][j] ; g[i][j] = std :: pair <int, int> (i - 1, j) ;
		if (j >= bt[i].t && j < bt[i].d)
			if (chkmax (f[i][j], f[i - 1][j - bt[i].t] + bt[i].p))
				g[i][j] = std :: pair <int, int> (i - 1,j - bt[i].t) ;
	}
	int ans = 0 ; std :: pair <int, int> begin ;
	FOR (i, 0, 2000) if (chkmax (ans, f[n][i]))
		begin = std :: pair <int, int> (n, i) ;
	printf ("%d\n", ans) ;
	
	print (begin) ;
	printf ("%d\n", py[0]) ;
	FOR (i, 1, py[0]) printf ("%d ", py[i]) ; putchar (10) ;
	
	return 0 ;
}
