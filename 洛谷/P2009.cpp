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

int n ;
int m ;

int dis[maxn][maxn] ;

inline char Getchar() {
	char ch = getchar() ;
	while (!(ch >= 'A' && ch <= 'Z')) ch = getchar() ;
	return ch ;
}

int main () {
	
	scanf(n) ; scanf(m) ;
	For (i, 1, n) dis[i][i - 1] = scanf (dis[i - 1][i]) ;
	dis[0][n - 1] = dis[n - 1][0] = dis[n][n - 1] ;
	dis[n][n - 1] = dis[n - 1][n] = 0 ;
	For (i, 1, m) {
		char x, y ; int z ;
		x = Getchar() ; y = Getchar() ; scanf(z) ;
		x -= 'A' ; y -= 'A' ;
		chkmax (dis[x][y], z) ; dis[y][x] = dis[x][y] ;
	}
	For (i, 0, n - 1) For (j, 0, n - 1) if (!dis[i][j]) dis[i][j] = 1e9 ;
	
	For (k, 0, n - 1) For (i, 0, n - 1) For (j, 0, n - 1)
		chkmin (dis[i][j], dis[i][k] + dis[k][j]) ;
	
	char S, T ;
	S = Getchar() ; T = Getchar() ;
	S -= 'A' ; T -= 'A' ;
	
	printf ("%d\n", dis[S][T]) ;
	
	return 0 ;
}
