#include<cstdio>

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

typedef long long LL ;
static const int maxn = 1e5 + 11 ;

int n ;
int m ;
int q ;

int ai[maxn] ;

LL gi[maxn] ;
LL di[maxn] ;
int ki[maxn] ;

double ept[maxn] ;

int main() {
	
	freopen ("segment.in", "r", stdin) ;
	freopen ("segment.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ; scanf(q) ;
	FOR (i, 1, n) scanf(ai[i]) ;
	FOR (i, 1, m) {
		int op, l, r, x ;
		scanf(op) ; scanf(l) ; scanf(r) ; scanf(x) ;
		if (op == 1)
			di[l] += x, di[r + 1] -= x ;
		else ki[l]++, ki[r + 1]--, gi[l] += x, gi[r + 1] -= x ;
	}
	
	FOR (i, 2, n) di[i] += di[i - 1], gi[i] += gi[i - 1], ki[i] += ki[i - 1] ;
	
	FOR (i, 1, n) {
		if (!ki[i])
			ept[i] = di[i] + ai[i] ;
		else 
			ept[i] = gi[i] * 1.0 / ki[i] + di[i] * 1.0 / (ki[i] + 1) ;
		ept[i] += ept[i - 1] ;
	}
	
	while (q--) {
		int l, r ;
		scanf(l) ; scanf(r) ;
		printf ("%.3lf\n", ept[r] - ept[l - 1]) ;
	}
	
	return 0 ;
}
