#include<cstdio>
#include<vector>
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
inline tp max (const tp& x, const tp& y) { return x > y ? x : y ; }
template <typename tp>
inline tp min (const tp& x, const tp& y) { return x < y ? x : y ; }
template <typename tp>
inline bool chkmax (tp& x, const tp& y) {
	return (x >= y) ? false: (x = y, true) ;
}
template <typename tp>
inline bool chkmin (tp& x, const tp& y) {
	return (x <= y) ? false: (x = y, true) ;
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
int S ;
int exa ;
LL ans ;

std :: pair<int , int> data[maxn] ;
std :: vector<std :: pair<int, int> > ctr ;
std :: vector<std :: pair<int, int> > :: iterator it ;

int main() {
	
	scanf(n) ; scanf(S) ;
	FOR(i, 1, n) {
		int a, b, s ;
		scanf(s) ; scanf(a) ; scanf(b) ;
		ans += 1LL * s * b ;
		exa = (exa + s) % S ;
		ctr.push_back (std :: pair<int, int> (b - a, s)) ;
	}
	
	if (exa)
		ctr.push_back (std :: pair<int, int> (0, S - exa)) ;
	
	std :: sort (ctr.begin(), ctr.end()) ;
	
	int tot = S ;
	LL sum = 0LL ;
	for (it = ctr.begin() ; it != ctr.end() ; it++) {
		int val = -(*it).first, s = (*it).second ;
		if (tot - s > 0) {
			tot -= s ;
			sum += 1LL * val * s ;
		} else {
			sum += 1LL * val * tot ;
			s -= tot ;
			ans += max (0LL, sum) ;
			ans += (s / S) * max (1LL * S * val, 0LL) ;
			tot = S - s % S ;
			sum = 1LL * (s % S) * val ;
		}
	}
	
	printf( "%I64d\n" , ans ) ;
	
	return 0 ;
}
