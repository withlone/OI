#include<map>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )
#define FOR( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define LOP( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define REP( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename tp >
inline bool chkmax( tp& x , const tp& y ) {
	return x >= y ? false : ( x = y , true ) ;
}
template < typename tp >
inline bool chkmin( tp& x , const tp& y ) {
	return x <= y ? false : ( x = y , true ) ;
}

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 200 + 11 ;
static const int maxm = 1e6 + 11 ;

int n ;
int ans ;

int dis[maxm] ;

char begin[maxn] ;
char end[maxn] ;

char ai[maxn][maxn] ;
char bi[maxn][maxn] ;

int nxt[maxn] ;

map < string , bool > mp ;

class mine {
	public :
		char s[maxn] ;
		int dis ;
		mine() { memset( s , 0 , sizeof s ) ; dis = 0 ; }
} ;

inline void get_nxt( char *x ) {
	int k = 0 ;
	FOR( i , 1 , strlen( x ) - 1 ) {
		while( k && x[k] != x[i] ) k = nxt[k - 1] ;
		if( x[k] == x[i] ) ++k ;
		nxt[i] = k ;
	}
}

inline void kmp( char *S , char *T , int *res , int& n ) {
	get_nxt( S ) ;
	n = 0 ;
	int m = strlen( S ) , k = 0 ;
	FOR( i , 0 , strlen( T ) - 1 ) {
		while( k && S[k] != T[i] ) k = nxt[k - 1] ;
		if( S[k] == T[i] ) ++k ;
		if( k == m ) res[ ++n ] = i - k + 1 ;
	}
}

inline void bfs() {
	queue < mine > que ; mine nxt , t , temp ;
	static char stack[maxn] ;
	int at[maxn] , len , tp ;
	memcpy( nxt.s , begin , sizeof begin ) ; nxt.dis = 0 ;
	while( !que.empty() ) que.pop() ;
	que.push( nxt ) ; mp[begin] = true ;
	while( !que.empty() ) {
		temp = t = que.front() ; que.pop() ;
		For( i , 1 , n ) {
			kmp( ai[i] , t.s , at , len ) ;
			if( len ) {
				tp = 0 ;
				FOR( j , 0 , strlen( bi[i] ) - 1 ) stack[ ++tp ] = bi[i][j] ;
			}
			For( j , 1 , len ) {
				int x = at[j] , back = tp ;
				FOR( k , x + strlen( ai[i] ) , strlen( t.s ) - 1 )
					stack[ ++tp ] = t.s[k] ;
				FOR( k , x , x + tp - 1 )
					t.s[k] = stack[k - x + 1] ;
				FOR( k , x + tp , maxn - 1 ) t.s[k] = '\0' ;
				if( mp[t.s] ) {
					t = temp ; tp = back ;
					continue ;
				}
				mp[t.s] = true ;
				memcpy( nxt.s , t.s , sizeof t.s ) ; nxt.dis = t.dis + 1 ;
				que.push( nxt ) ;
				if( !strcmp( t.s , end ) )
					return printf( "%d\n" , nxt.dis ) , void() ;
				t = temp ; tp = back ;
			}
		}
	}
	puts( "NO ANSWER!" ) ;
}

int main() {
	
	freopen( "b.in" , "r" , stdin ) ;
	freopen( "b.out" , "w" , stdout ) ;
	
	scanf( "%s%s" , begin , end ) ;
	
	for( n = 1 ; scanf( "%s%s" , ai[n] , bi[n] ) != EOF ; ++n ) ;
	--n ;
	
	bfs() ;
	
	return 0 ;
}
