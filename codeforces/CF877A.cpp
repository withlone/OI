#include<cstdio>
#include<cstring>

#define For(i, _l, _r) for (int i = (_l), i##r = (_r) ; i <= (i##r) ; ++i)
#define Lop(i, _l, _r) for (int i = (_l), i##r = (_r) ; i >= (i##r) ; --i)
#define Rep(i, _l, _r) for (int i = (_l) ; i ; i = (_r))

template <typename tp> inline tp max (tp x, tp y) { return x > y? x: y ; }
template <typename tp> inline tp min (tp x, tp y) { return x < y? x: y ; }
template <typename tp>
inline bool chkmax (tp& x, tp y) { return (x >= y)? false: (x = y, true) ; }
template <typename tp>
inline bool chkmin (tp& x, tp y) { return (x <= y)? false: (x = y, true) ; }

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ; ch> '9' || ch< '0' ; ch = getchar() ) if( ch == '-' ) f = -1 ;
	for( ; ch>='0' && ch<='9' ; ch = getchar() ) in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 111 ;

char si[maxn] ;
char name[11][11] ;

inline bool match (int x, int y) {
	For (i, 0, strlen (name[x]) - 1)
		if (name[x][i] ^ si[y + i]) return false ;
	return true ;
}

int main() {
	
	scanf ("%s", si) ;
	memcpy (name[0], "Danil", sizeof name[0]) ;
	memcpy (name[1], "Olya", sizeof name[0]) ;
	memcpy (name[2], "Slava", sizeof name[0]) ;
	memcpy (name[3], "Ann", sizeof name[0]) ;
	memcpy (name[4], "Nikita", sizeof name[0]) ;
	
	int ans = 0 ;
	For (i, 0, 4) For (j, 0, strlen (si) - strlen (name[i]) )
		if (match (i, j)) ++ans ;
	
	puts ((ans == 1)? "YES": "NO") ;
	
	return 0 ;
}
