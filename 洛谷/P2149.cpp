#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>

using std :: pair ;
using std :: vector ;

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

#define ft first
#define sd second
typedef pair <int, int> __ ;
static const int maxn = 1511 ;
static const int mod = (1 << 11) - 1 ;

int n ;
int m ;

int s1 ;
int t1 ;
int s2 ;
int t2 ;

bool V[maxn] ;
int dis[4][maxn] ;

vector <__> e[maxn] ;
vector <__> :: iterator it ;

inline void spfa (int S, int *dis) {
	static int que[mod + 10] ;
	int head = 0, tail = 0 ;
	memset (dis, 0x3f, sizeof ::dis[0]) ;
	que[++tail] = S ; dis[S] = 0 ;
	while (head ^ tail) {
		int x = que[++head &= mod] ; V[x] = false ;
		for (it = e[x].begin() ; it != e[x].end() ; it++)
			if (dis[it->ft] > dis[x] + it->sd) {
				dis[it->ft] = dis[x] + it->sd ;
				if (!V[it->ft])
					V[it->ft] = true, que[++tail &= mod] = it->ft ;
			}
	}
}

int main() {
	
	scanf(n) ; scanf(m) ;
	scanf(s1) ; scanf(t1) ; scanf(s2) ; scanf(t2) ;
	For (i, 1, m) {
		int x, y, z ;
		scanf(x) ; scanf(y) ; scanf(z) ;
		e[x].push_back (__ (y, z)) ;
		e[y].push_back (__ (x, z)) ;
	}
	
	spfa (s1, dis[0]) ; spfa (t1, dis[1]) ;
	spfa (s2, dis[2]) ; spfa (t2, dis[3]) ;
	
	int ans = 0 ;
	
	For (i, 1, n) For (j, 1, n)
		if (dis[0][i] + dis[1][i] == dis[0][t1] &&
			dis[0][j] + dis[1][j] == dis[0][t1] &&
			dis[2][i] + dis[3][i] == dis[2][t2] &&
			dis[2][j] + dis[3][j] == dis[2][t2] )
			chkmax (ans, std :: abs (dis[0][i] - dis[0][j])) ;
	
	printf ("%d\n", ans) ;
	
	return 0 ;
}
