#include<set>
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

static const int maxn = 1e5 + 11 ;

int n ;

int ai[maxn] ;

inline bool chk (int x) {
	std :: set <int> bt ;
	if (abs (ai[1] - ai[3]) <= x) bt.insert (ai[1]) ;
	if (abs (ai[2] - ai[3]) <= x) bt.insert (ai[2]) ;
	if (bt.empty()) return false ;
	FOR (i, 3, n) {
		while (!bt.empty() && abs (*bt.begin() - ai[i]) > x)
			bt.erase (*bt.begin()) ;
		while (!bt.empty() && abs (*bt.rbegin() - ai[i]) > x)
			bt.erase (*bt.rbegin()) ;
		if (!bt.empty() && (abs (*bt.begin() - ai[i]) <= x ||
			abs (*bt.rbegin() - ai[i]) <= x))
			bt.insert (ai[i]) ;
		if (bt.empty()) return false ;
	}
	return true ;
}

int main() {
	
	n = scanf(n) + 2 ;
	FOR (i, 1, n) scanf(ai[i]) ;
	
	int l = abs (ai[1] - ai[2]), r = 1e9, res ;
	while (l <= r) {
		int mid = l + r >> 1 ;
		if (chk(mid)) res = mid, r = mid - 1 ;
		else l = mid + 1 ;
	}
	
	printf ("%d\n", res) ;
	
	return 0 ;
}
