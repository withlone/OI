#include<cstdio>
#include<cstring>

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
inline tp max( const tp& x , const tp& y ) { return x > y ? x : y ; }
template < typename tp >
inline tp min( const tp& x , const tp& y ) { return x < y ? x : y ; }
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

static const int maxn = 17 ;
static const int maxm = 103 ;

int cases ;
int ready ;

bool right[maxm] ;

int cd[maxn] ;
int cnt[maxm] ;
int tot[maxm] ;

int spe[] = { 10 , 90 , 11 , 91 , 12 , 92 , 13 , 23 , 33 , 43 , 53 , 63 , 73 } ;

char output[3] ;
char mah[maxn][3] ;

inline int go_to( char x ) {
	if( x == 'm' ) return 0 ;
	if( x == 's' ) return 1 ;
	if( x == 'p' ) return 2 ;
	return 3 ;
}

inline char go_back( int x ) {
	if( !x ) return 'm' ;
	if( x == 1 ) return 's' ;
	if( x == 2 ) return 'p' ;
	return 'c' ;
}

inline int change_to( char *x ) {
	return ( x[0] - '0' ) * 10 + go_to( x[1] ) ;
}

inline void change_back( char *x , int y ) {
	x[0] = y / 10 + '0' ; x[1] = go_back( y % 10 ) ;
}

inline bool in( int x ) {
	FOR( i , 1 , cd[0] ) if( x == cd[i] ) return true ;
	return false ;
}

inline bool chk1() {
	int res = 0 ;
	FOR( i , 1 , cd[0] )
		if( cnt[ cd[i] ] == 1 ) ++res ;
		else if( cnt[ cd[i] ] >= 3 ) return false ;
	return res == 1 ;
}

inline bool chk2() {
	int res = 0 ;
	FOR( i , 0 , 12 )
		if( !cnt[ spe[i] ] ) ++res ;
	return res <= 1 ;
}

inline bool chker() {
	tot[ready] -= 2 ;
	FOR( i , 1 , cd[0] ) if( cd[i] % 10 == 3 ) {
		if( tot[ cd[i] ] && tot[ cd[i] ] != 3 ) return false ;
		tot[ cd[i] ] = 0 ;
	}
	static int mn[3] ;
	mn[0] = mn[1] = mn[2] = 10 ;
	FOR( i , 1 , cd[0] ) if( cd[i] % 10 != 3 )
		chkmin( mn[ cd[i] % 10 ] , cd[i] / 10 ) ;
	For( I , 0 , 2 ) if( mn[I] != 10 ) {
		For( i , mn[I] , 9 ) {
			register int x = i * 10 + I ;
			if( tot[x] >= 3 ) tot[x] -= 3 ;
			if( i <= 7 ) {
				while( tot[x] && tot[x + 10] && tot[x + 20] )
					tot[x]-- , tot[x + 10]-- , tot[x + 20]-- ;
			}
		}
	}
	FOR( i , 1 , cd[0] ) if( tot[ cd[i] ] ) return false ;
	return true ;
}

inline bool chk() {
	For( i , 1 , cd[0] ) if( cnt[ cd[i] ] >= 2 ) {
		ready = cd[i] ;
		FOR( j , 1 , cd[0] ) tot[ cd[j] ] = cnt[ cd[j] ] ;
		memcpy( tot , cnt , sizeof tot ) ;
		if( chker() ) return true ;
	}
	return false ;
}

inline void solve() {
	int ans = 0 ;
	memset( right , 0 , sizeof right ) ;
	if( chk1() ) {
		++ans ;
		FOR( i , 1 , cd[0] ) if( cnt[ cd[i] ] == 1 )
			right[ cd[i] ] = true ;
	}
	if( chk2() ) {
		int res = 0 ;
		FOR( i , 0 , 12 ) res += !cnt[ spe[i] ] ;
		if( !res ) {
			printf( "13" ) ;
			FOR( i , 0 , 12 )
				change_back( output , spe[i] ) , printf( " %s" , output ) ;
			putchar( 10 ) ;
		} else {
			printf( "1" ) ;
			FOR( i , 0 , 12 ) if( !cnt[ spe[i] ] )
				change_back( output , spe[i] ) , printf( " %s\n" , output ) ;
		}
		return ;
	}
	For( i , 1 , 9 ) FOR( j , 0 , 3 ) {
		int x = i * 10 + j , f = false ;
		if( cnt[x] == 4 || right[x] ) continue ;
		cnt[x]++ ;
		if( !in( x ) ) cd[ ++cd[0] ] = x , f = true ;
		if( chk() ) right[x] = true , ++ans ;
		cnt[x]-- ;
		if( f ) cd[0]-- ;
	}
	if( !ans ) puts( "Nooten" ) ;
	else {
		printf( "%d" , ans ) ;
		For( i , 1 , 9 ) FOR( j , 0 , 3 ) if( right[ i * 10 + j ] )
			change_back( output , i * 10 + j ) , printf( " %s" , output ) ;
		putchar( 10 ) ;
	}
}

int main() {
	
	freopen( "mahjong.in" , "r" , stdin ) ;
	freopen( "mahjong.out" , "w" , stdout ) ;
	
	scanf( cases ) ;
	
	while( cases-- ) {
		FOR( i , 1 , 13 ) scanf( "%s" , mah[i] ) ;
		cd[0] = 0 ;
		FOR( i , 1 , 13 )
			if( !in( change_to( mah[i] ) ) )
				cd[ ++cd[0] ] = change_to( mah[i] ) ;
		memset( cnt , 0 , sizeof cnt ) ;
		FOR( i , 1 , 13 ) ++cnt[ change_to( mah[i] ) ] ;
		solve() ;
	}
	
	return 0 ;
}
