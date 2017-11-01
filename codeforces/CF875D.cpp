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
static const int maxn = 2e5 + 11 ;
static const int maxx = 30 ;

template <typename tp>
class stack {
	private :
		int tpr ;
		tp bt[maxn] ;
	public :
		stack () { tpr = 0 ; }
		inline void push (const tp& x) { bt[++tpr] = x ; }
		inline void clear () { tpr = 0 ; }
		inline void pop () { if (!tpr--) throw ; }
		inline bool empty () { return !tpr ; }
		inline tp top () { return !tpr? throw: bt[tpr] ; }
} ;

int n ;

int ai[maxn] ;
int lmin[maxn] ;
int rmin[maxn] ;
int lmax[maxn] ;
int rmax[maxn] ;
int li[maxn][maxx + 11] ;
int ri[maxn][maxx + 11] ;

stack <int> tk ;

int main() {
	
	scanf(n) ;
	FOR (i, 1, n) scanf(ai[i]) ;
	
	FOR (i, 1, n) {
		while (!tk.empty() && ai[i] > ai[tk.top()])
			rmax[tk.top()] = i - 1, tk.pop() ;
		tk.push (i) ;
	}
	for (; !tk.empty() ; tk.pop()) rmax[tk.top()] = n ;
	
	LOP (i, n, 1) {
		while (!tk.empty() && ai[i] >= ai[tk.top()])
			lmax[tk.top()] = i + 1, tk.pop() ;
		tk.push (i) ;
	}
	for (; !tk.empty() ; tk.pop()) lmax[tk.top()] = 1 ;
	
	FOR (i, 1, n) rmin[i] = n + 1 ;
	FOR (k, 0, 29) {
		ri[n + 1][k] = n + 1 ;
		LOP (i, n, 1)
			if (ai[i + 1] >> k & 1) ri[i][k] = i + 1 ;
			else ri[i][k] = ri[i + 1][k] ;
		FOR (i, 1, n) if (!(ai[i] >> k & 1)) chkmin (rmin[i], ri[i][k]) ;
	}
	FOR (i, 1, n) if (rmin[i] == n + 1) rmin[i] = 0 ;
	FOR (k, 0, 29) {
		FOR (i, 1, n)
			if (ai[i - 1] >> k & 1) li[i][k] = i - 1 ;
			else li[i][k] = li[i - 1][k] ;
		FOR (i, 1, n) if (!(ai[i] >> k & 1)) chkmax (lmin[i], li[i][k]) ;
	}
	
	LL ans = 0LL ;
	FOR (i, 1, n) {
		int l1 = lmax[i], l2 = lmin[i], r1 = rmax[i], r2 = rmin[i] ;
		if (r2 > r1) r2 = 0 ; if (l2 < l1) l2 = 0 ;
		if (l2 && r2)
			ans += 1LL * (l2 - l1 + 1) * (r2 - i)
				+  1LL * (i - l2) * (r1 - r2 + 1)
				+  1LL * (l2 - l1 + 1) * (r1 - r2 + 1) ;
		else if (l2)
			ans += 1LL * (l2 - l1 + 1) * (r1 - i + 1) ;
		else if (r2)
			ans += 1LL * (i - l1 + 1) * (r1 - r2 + 1) ;
	}
	
	printf ("%I64d\n", ans) ;
	
	return 0 ;
}
