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

static const int maxn = 2e5 + 11 ;

int n ;
int tp ;

int ai[maxn] ;
int cnt[maxn] ;
bool V[maxn] ;

int stack[maxn] ;

int main() {
	
	scanf(n) ;
	FOR (i, 1, n) cnt[scanf(ai[i])]++ ;
	
	int ans = 0 ;
	FOR (i, 1, n) if (!cnt[i])
		++ans, stack[++tp] = i ;
	
	tp = 1 ;
	printf ("%d\n", ans) ;
	FOR (i, 1, n)
		if (!stack[tp]) break ;
		else if (cnt[ai[i]] == 1) ;
		else if (V[ai[i]]) cnt[ai[i]]--, ai[i] = stack[tp++] ;
		else {
			if (ai[i] < stack[tp]) V[ai[i]] = true ;
			else cnt[ai[i]]--, ai[i] = stack[tp++] ;
		}
	
	FOR (i, 1, n) printf ("%d ", ai[i]) ; putchar (10) ;
	
	return 0 ;
}
