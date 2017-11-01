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

static const int maxn = 3e3 + 11 ;

int n ;
int ans1 ;
int ans2 ;
int ans3 ;
int ater ;

int output[maxn] ;

int ai[maxn] ;
int id[maxn] ;
int Log[maxn] ;
int bin[maxn] ;
int ST[14][maxn] ;
int at[14][maxn] ;

inline bool cmp1 (const int& x, const int& y) {
	return ai[x] > ai[y] ;
}

inline bool cmp2 (const int& x, const int& y) {
	return x > y ;
}

inline int query (int l, int r) {
	int t = Log[r - l + 1] ;
	if (ST[t][l] > ST[t][r + 1 - bin[t]])
		return ater = at[t][l] , ST[t][l] ;
	else
		return ater = at[t][r + 1 - bin[t]], ST[t][r + 1 - bin[t]] ;
}

int main() {
	
	scanf(n) ;
	bin[0] = 1 ;
	FOR (i, 1, 15) bin[i] = bin[i - 1] << 1 ;
	FOR (i, 2, n) Log[i] = Log[i >> 1] + 1 ;
	
	FOR (i, 1, n) scanf(ai[i]), id[i] = i ;
	
	std :: sort (1 + id, 1 + n + id, cmp1) ;
	std :: sort (1 + ai, 1 + n + ai, cmp2) ;
	
	FOR (i, 1, n) ST[0][i] = ai[i] - ai[i + 1], at[0][i] = i ;
	
	FOR (i, 1, 13) FOR (j, 1, n)
		if (j + bin[i - 1] <= n) {
			if (ST[i - 1][j] > ST[i - 1][j + bin[i - 1]])
				ST[i][j] = ST[i - 1][j],
				at[i][j] = at[i - 1][j] ;
			else
				ST[i][j] = ST[i - 1][j + bin[i - 1]],
				at[i][j] = at[i - 1][j + bin[i - 1]] ;
		}
		else ST[i][j] = ST[i - 1][j], at[i][j] = at[i - 1][j] ;
	
	FOR (i, 1, n) FOR (j, i + 1, n) {
		int a = i, b = j - i, ta = max (a, b), tb = min (a, b) ;
		if (a > (b << 1) || b > (a << 1)) continue ;
		int l = (ta >> 1) + (ta & 1), r = tb << 1 ;
		if (l > r || l + j > n) continue ;
		l += j ; r += j ; chkmin (r, n) ;
		int t1 = ai[i] - ai[i + 1], t2 = ai[j] - ai[j + 1], t3 = query (l, r) ;
		int b1 = ai[ans1] - ai[ans1 + 1], b2 = ai[ans2] - ai[ans2 + 1],
			b3 = ai[ans3] - ai[ans3 + 1] ;
		if (t1 > b1 || t1 == b1 && t2 > b2 ||
			t1 == b1 && t2 == b2 && t3 > b3 )
			ans1 = i, ans2 = j, ans3 = ater ;
	}
	
	FOR (i, 1, ans1) output[id[i]] = 1 ;
	FOR (i, ans1 + 1, ans2) output[id[i]] = 2 ;
	FOR (i, ans2 + 1, ans3) output[id[i]] = 3 ;
	FOR (i, ans3 + 1, n) output[id[i]] = -1 ;
	
	FOR (i, 1, n) printf ("%d ", output[i]) ;
	putchar (10) ;
	
	return 0 ;
}
