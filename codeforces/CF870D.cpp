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

static const int maxn = 5e3 + 11 ;

int n ;
int tot ;

int ai[maxn] ;
int bi[maxn] ;
int xi[maxn] ;
int yi[maxn] ;

int output[maxn] ;

int main() {
	
	scanf(n) ;
	FOR (i, 0, n - 1) {
		printf ("? %d %d\n", i, 0) ;
		fflush(stdout) ;
		scanf(xi[i]) ;
	}
	FOR (i, 0, n - 1) {
		printf ("? %d %d\n", 0, i) ;
		fflush(stdout) ;
		scanf(yi[i]) ;
	}
	
	FOR (first, 0, n - 1) {
		ai[0] = first ;
		FOR (i, 0, n - 1) bi[i] = yi[i] xor ai[0] ;
		FOR (i, 0, n - 1) ai[i] = xi[i] xor bi[0] ;
		if (ai[0] != first) goto do_nothing ;
		FOR (i, 0, n - 1)
			if (ai[i] >= n || bi[i] >= n || ai[bi[i]] != i) goto do_nothing ;
		if (++tot == 1) memcpy (output, ai, sizeof output) ;
		do_nothing : ;
	}
	
	printf ("!\n%d\n", tot) ;
	FOR (i, 0, n - 1) printf ("%d ", output[i]) ; putchar (10) ;
	fflush(stdout) ;
	
	return 0 ;
}
