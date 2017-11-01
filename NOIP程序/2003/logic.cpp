#include<cstdio>
#include<cstring>
#include<cstdlib>

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
inline type max( const type& x , const type& y ) { return x > y ? x : y ; }
template < typename type >
inline type min( const type& x , const type& y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , const type& y ) {
	return x >= y ? false : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x <= y ? false : ( x = y , true ) ;
}

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e3 + 13 ;
static const int maxm = 251 ;
static const int mod = 1e6 + 33 ;
static const int ten = 233 ;

int n ;
int m ;
int P ;
int ans ;

bool V[maxn] ;
bool vis[maxn] ;
bool not_is[maxn] ;
bool useless[maxn] ;

int id[maxn] ;
int len[maxn] ;
int back[mod] ;
int lenr[maxn] ;

char name[maxn][maxn] ;
char test[maxn][maxn] ;
char G[101][maxm][maxm] ;

const char *day[] = { "Monday" , "Tuesday" , "Wednesday" , "Thursday" , "Friday" , "Saturday" , "Sunday" } ;

inline bool chker( char x ) {
	return x >= 'A' && x <= 'Z' || x >= 'a' && x <= 'z' ;
}

inline int hasher( char *x ) {
	int res = 0 ;
	FOR( i , 0 , strlen( x ) - 1 )
		res = ( res * ten + x[i] ) % mod ;
	return res ;
}

inline bool chk( char *x , const int& y , const int& z ) {
	static char t[maxm][maxm] ;
	int ps = 0 , I ;
	for( I = 0 ; ps < y ; ++I ) {
		for( int i = 0 ; chker( x[ps] ) && ps < y ; ++i , ++ps )
			t[I][i] = x[ps] ;
		while( !chker( x[ps] ) && ps < y ) {
			if( x[ps] != ' '
			&& x[ps] != ':' && x[ps] != '.' )goto ender ;
			++ps ;
		}
	}
	if( I > 5 || !back[ hasher( t[0] ) ] )goto ender ;
	if( !strcmp( t[1] , "I" ) ) {
		if( strcmp( t[2] , "am" ) )goto ender ;
		if( !strcmp( t[3] , "guilty" ) ) {
			if( I != 4 )goto ender ;
		} else if( strcmp( t[3] , "not" ) ) goto ender ;
		else if( strcmp( t[4] , "guilty" ) )goto ender ;
		else if( I != 5 )goto ender ;
	} else if( back[ hasher( t[1] ) ] ) {
		if( strcmp( t[2] , "is" ) )goto ender ;
		if( !strcmp( t[3] , "guilty" ) ) {
			if( I != 4 )goto ender ;
		} else if( strcmp( t[3] , "not" ) ) goto ender ;
		else if( strcmp( t[4] , "guilty" ) )goto ender ;
		else if( I != 5 )goto ender ;
	} else if( !strcmp( t[1] , "Today" ) ) {
		if( strcmp( t[2] , "is" ) )goto ender ;
		bool f = false ;
		FOR( i , 0 , 6 )if( !strcmp( day[i] , t[3] ) ) {
			f = true ; break ;
		}
		if( !f || I != 4 )goto ender ;
	} else goto ender ;
	
	lenr[z] = I ;
	FOR( i , 0 , I - 1 )
		memcpy( G[z][i] , t[i] , sizeof t[i] ) ;
	
	For( i , 0 , I - 1 ) FOR( j , 0 , strlen( t[i] ) - 1 )
		t[i][j] = '\0' ;
	
	return true ;
	ender :
	For( i , 0 , I ) FOR( j , 0 , strlen( t[i] ) - 1 )
		t[i][j] = '\0' ;
	return false ;
}

inline bool chk1( const int& x ) {
	if( lenr[x] != 4 )return false ;
	if( strcmp( G[x][1] , "I" ) )return false ;
	return true ;
}

inline bool chk2( const int& x ) {
	if( lenr[x] != 5 )return false ;
	if( strcmp( G[x][1] , "I" ) )return false ;
	return true ;
}

inline bool chk3( const int& x ) {
	if( lenr[x] != 4 )return false ;
	if( !back[ hasher( G[x][1] ) ] )return false ;
	return true ;
}

inline bool chk4( const int& x ) {
	if( lenr[x] != 5 )return false ;
	if( !back[ hasher( G[x][1] ) ] )return false ;
	return true ;
}

inline bool chk5( const int& x ) {
	if( lenr[x] != 4 )return false ;
	if( strcmp( G[x][1] , "Today" ) )return false ;
	return true ;
}

inline void last_chker() {
	int Today = -1 , guilty = 0 , cnt = 0 ;
	memset( vis , 0 , sizeof(bool) * (n + 1) ) ;
	memset( not_is , 0 , sizeof(bool) * (n + 1) ) ;
	FOR( i , 1 , P ) {
		int tp = back[ hasher( G[i][0] ) ] ;
		if( V[tp] ) {
			if( chk1( i ) || chk3( i ) || chk5( i ) )
				vis[i] = true , id[ ++cnt ] = i ;
		} else if( chk2( i ) || chk4( i ) )
			vis[i] = true , id[ ++cnt ] = i ;
	}
	FOR( i , 1 , P ) if( !vis[i] && !useless[i] )
		id[ ++cnt ] = i ;
	FOR( I , 1 , cnt ) {
		int i = id[I] ;
		int tp = back[ hasher( G[i][0] ) ] ;
		if( V[tp] ) {
			if( chk1( i ) ) {
				if( not_is[tp] )return ;
				if( !guilty )guilty = tp ;
				else if( guilty != tp )return ;
			} else if( chk2( i ) ) {
				if( guilty == tp )return ;
				not_is[tp] = true ;
			} else if( chk3( i ) ) {
				if( not_is[ back[ hasher( G[i][1] ) ] ] )return ;
				if( !guilty )guilty = back[ hasher( G[i][1] ) ] ;
				else if( guilty != back[ hasher( G[i][1] ) ] )return ;
			} else if( chk4( i ) ) {
				if( guilty == back[ hasher( G[i][1] ) ] )return ;
				not_is[ back[ hasher( G[i][1] ) ] ] = true ;
			} else if( chk5( i ) ) {
				if( Today == -1 ) {
					FOR( j , 0 , 6 ) if( !strcmp( day[j] , G[i][3] ) ) {
						Today = j ; break ;
					}
					if( Today == -1 )return ;
				} else if( strcmp( day[Today] , G[i][3] ) )return ;
			} else return ;
		}
		else {
			if( chk1( i ) ) {
				if( guilty == tp )return ;
				not_is[tp] = true ;
			} else if( chk2( i ) ) {
				if( not_is[tp] )return ;
				if( !guilty )guilty = tp ;
				else if( guilty != tp )return ;
			} else if( chk3( i ) ) {
				if( guilty == back[ hasher( G[i][1] ) ] )return ;
				not_is[ back[ hasher( G[i][1] ) ] ] = true ;
			} else if( chk4( i ) ) {
				if( !guilty )guilty = back[ hasher( G[i][1] ) ] ;
				else if( guilty != back[ hasher( G[i][1] ) ] )return ;
			} else if( chk5( i ) ) {
				if( Today != -1 && 
					!strcmp( day[Today] , G[i][3] ) )return ;
			} else return ;
		}
	}
	
	if( !guilty )
	FOR( i , 1 , n )
		if( !not_is[i] ) {
			if( guilty )return ;
			guilty = i ;
		}
	
	if( !ans )ans = guilty ;
	else if( ans != guilty ) {
		puts( "Cannot Determine" ) ;
		exit( 0 ) ;
	}
}

void dfs( const int& x , const int& tot ) {
	if( x == n + 1 )return tot == m ? last_chker() : void() ;
	V[x] = false ;
	dfs( x + 1 , tot ) ;
	V[x] = true ;
	dfs( x + 1 , tot + 1 ) ;
}

inline bool chk_special() {
	FOR( i , 1 , P )
		if( !useless[i] )return false ;
	return true ;
}

int main() {
	
	freopen( "logic.in" , "r" , stdin ) ;
	freopen( "logic.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ; scanf( P ) ;
	
	m = n - m ;
	
	FOR( i , 1 , n )
		scanf( "%s" , name[i] ) , back[ hasher( name[i] ) ] = i ;
	
	scanf( "\n" ) ;
	FOR( i , 1 , P ) {
		start :
		fgets( test[i] , maxn , stdin ) ;
		if( strlen( test[i] ) == 1 )goto start ;
		len[i] = strlen( test[i] ) - 1 ;
		while( test[i][ len[i] ] == '\n' || test[i][ len[i] ] == '\r' )
			len[i]-- ;
		if( !chk( test[i] , len[i] , i ) )useless[i] = true ;
	}
	
	dfs( 1 , 0 ) ;
	
	if( !ans && chk_special() )puts( "Cannot Determine" ) ;
	else if( !ans )puts( "Impossible" ) ;
	else printf( "%s\n" , name[ans] ) ;
	
	return 0 ;
}
