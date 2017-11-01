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

static const int maxn = 3e5 + 11 ;

int n ;
int m ;

std :: pair <int, int> data[maxn] ;

template <typename tp>
class heap {
	private :
		tp T[maxn] ;
		int size ;
	public :
		heap () { size = 0 ; }
		inline void push (tp x) {
			T[ ++size ] = x ;
			int p = size ;
			while (p != 1 && T[p] < T[p >> 1]) {
				std :: swap (T[p], T[p >> 1]) ;
				p >>= 1 ;
			}
		}
		inline void pop () {
			T[1] = T[ size-- ] ;
			int p = 1 ;
			while ((p << 1) <= size && min (T[p << 1], T[p << 1 | 1]) < T[p] ) {
				int t = T[p << 1] < T[p << 1 | 1]? p << 1: p << 1 | 1 ;
				std :: swap (T[t], T[p]) ;
				p = t ;
			}
		}
		inline tp top () { return T[1] ; }
		inline bool empty () { return !size ; }
} ;

heap < int > boot ;

int main() {
	
	freopen ("work.in", "r", stdin) ;
	freopen ("work.out", "w", stdout) ;
	
	scanf(n) ; scanf(m) ;
	FOR (i, 1, n)
		scanf(data[i].first), scanf(data[i].second) ,
		data[i].second += data[i].first ;
	
	std :: sort (1 + data, 1 + n + data) ;
	
	int ans = 0 ;
	
	FOR (i, 1, n) {
		while (!boot.empty() && data[i].first - boot.top() > m ) boot.pop() ;
		if (!boot.empty() && data[i].first >= boot.top())
			++ans , boot.pop() ;
		boot.push (data[i].second) ;
	}
	
	printf ("%d\n", ans) ;
	
	return 0 ;
}
