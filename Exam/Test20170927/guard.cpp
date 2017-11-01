#include<cstdio>
#include<cstring>
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

template < typename type >
inline bool chkmax( type& x , const type& y ) {
	return x > y ? false : x = y , true ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x < y ? false : x = y , true ;
}

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 2e4 + 11 ;

int n ;
int m ;
int cases ;

int at[maxn] ;

int lst[maxn] ;
int nxt[maxn] ;

int b[maxn] ;
bool V[maxn] ;

class guard {
	public :
		int a ;
		int c ;
		
		bool operator < ( const guard& x )
			const { return a == x.a ? c < x.c : a < x.a ; }
} gd[maxn] ;

class ___ {
	public :
		int b ;
		int id ;
		
		bool operator < ( const ___& x )
			const { return b < x.b ; }
} dr[maxn] ;

inline void del( int x ) {
	V[x] = true ;
	nxt[ lst[x] ] = nxt[x] ;
	lst[ nxt[x] ] = lst[x] ;
}

inline bool chk() {
	memset( V , 0 , sizeof(bool) * (m + 1) ) ;
	
	FOR( i , 1 , n )
		if( !V[ at[ gd[i].c ] ] && dr[ at[ gd[i].c ] ].b > gd[i].a )
			del( at[ gd[i].c ] ) ;
		else {
			int x = upper_bound( 1 + b , 1 + m + b , gd[i].a ) - b - 1 ;
			while( V[x] && x )x = lst[x] ;
			if( x )del( x ) ;
		}
	
	FOR( i , 1 , m )
		if( !V[i] )return false ;
	return true ;
}

int main() {
	
	freopen( "guard.in" , "r" , stdin ) ;
	freopen( "guard.out" , "w" , stdout ) ;
	
	scanf( cases ) ;
	
	while( cases-- ) {
		scanf( n ) ; scanf( m ) ;
		FOR( i , 1 , n )scanf( gd[i].a ) ;
		FOR( i , 1 , m )scanf( dr[i].b ) , dr[i].id = i ;
		FOR( i , 1 , n )scanf( gd[i].c ) ;
		sort( 1 + gd , 1 + n + gd ) ;
		sort( 1 + dr , 1 + m + dr ) ;
		FOR( i , 1 , m )at[ dr[i].id ] = i , b[i] = dr[i].b ;
		FOR( i , 1 , m )lst[i] = i - 1 , nxt[i] = i + 1 ;
		nxt[m] = 0 ;
		puts( chk() ? "Success" : "Fail" ) ;
	}
	return 0 ;
}
