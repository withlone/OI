#include<cstdio>
#include<vector>
#include<algorithm>

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

typedef long long LL ;
static const int maxn = 6e5 + 11 ;
static const int maxm = 13 ;

int n ;
int m ;
LL A ;
LL B ;

char bt[maxn][maxm] ;

LL sum[maxn] ;

vector <int> ot[1027] ;
vector <int> :: iterator it ;

inline int ceil (int x, int y) {
	return x / y + (x % y != 0) ;
}

int main() {
	
	freopen ("game.in", "r", stdin) ;
	freopen ("game.out", "w", stdout) ;
	
	scanf ("%d%d%lld%lld", &n, &m, &A, &B) ;
	For (i, 1, n) {
		int status = 0 ;
		scanf ("%s", bt[i] + 1) ;
		For (j, 1, m) status |= (bt[i][j] -= '0') << j - 1 ;
		ot[status].push_back (i) ;
	}
	
	For (i, 1, n) sum[i] = i ;
	
	For (i, 0, (1 << m) - 1) For (j, 1, ot[i].size() - 1)
		sum[ot[i][j]] += sum[ot[i][j - 1]] ;

	LL ans = -1e18 ; int full = (1 + m) * m >> 1 ;
	For (i, 0, (1 << m) - 1) {
		LL temp = 0 ;
		For (j, 0, (1 << m) - 1) if (ot[j].size()) {
			LL t1 = 0 ; int K = 0 ;
			int status = i ^ j ;
			For (k, 1, m) if (status >> k - 1 & 1)
				t1 += k, ++K ;
			if ((2 * K - m) && A) {
				if ((A > 0) ^ (2 * K - m > 0)) {
					int chk = (B * full - t1 * B * 2) / (A * (2 * K - m)) ;
					it = upper_bound (ot[j].begin(), ot[j].end(), chk) ;
					if (it != ot[j].begin()) {
						--it ;
						temp += A * K * sum[*it] ;
						temp += B * t1 * (it - ot[j].begin() + 1) ;
						temp +=
							A * (m - K) * (sum[*(ot[j].end() - 1)] - sum[*it]) ;
						temp += B * (full - t1) * (ot[j].end() - it - 1) ;
					} else {
						temp += A * (m - K) * sum[*(ot[j].end() - 1)] ;
						temp += B * (full - t1) * ot[j].size() ;
					}
				} else {
					int chk =
							ceil ((B * full - t1 * B * 2), (A * (2 * K - m))) ;
					it = lower_bound (ot[j].begin(), ot[j].end(), chk) ;
					if (it != ot[j].begin()) {
						it-- ;
						temp += A * K * (sum[*(ot[j].end() - 1)] - sum[*it]) ;
						temp += B * t1 * (ot[j].end() - it - 1) ;
						temp += A * (m - K) * sum[*it] ;
						temp += B * (full - t1) * (it - ot[j].begin() + 1) ;
					} else {
						temp += A * K * sum[*(ot[j].end() - 1)] ;
						temp += B * t1 * ot[j].size() ;
					}
				}
			} else {
				LL p1 = A * K * sum[*(ot[j].end() - 1)]
						+ B * t1 * ot[j].size() ;
				LL p2 = A * (m - K) * sum[*(ot[j].end() - 1)]
						+ B * (full - t1) * ot[j].size() ;
				temp += max (p1, p2) ;
			}
		}
		chkmax (ans, temp) ;
	}
	
	printf ("%lld\n", ans) ;
	
	return 0 ;
}
