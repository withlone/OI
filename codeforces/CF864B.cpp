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

static const int maxn = 211 ;

int n ;

bool V[maxn] ;
char str[maxn] ;

inline bool upper (char x) {
	return x >= 'A' && x <= 'Z' ;
}

inline bool lower (char x) {
	return x >= 'a' && x <= 'z' ;
}

int main() {
	
	scanf(n) ;
	scanf ("%s", str + 1) ;
	
	int l = 1, r = 0 ,ans = 0 ;
	while (l <= n) {
		while (upper (str[l])) ++l ;
		if (l > n) break ;
		memset (V, 0, sizeof V) ;
		r = l ; int tot = 0 ;
		for (; lower (str[r]) ; ++r )
			if (!V[str[r]])
				V[str[r]] = true, ++tot ;
		l = r ;
		chkmax (ans, tot) ;
	}
	
	printf ("%d\n", ans) ;
	
	return 0 ;
}
