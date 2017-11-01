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

template < typename type >
inline type max( const type& x , const type& y ) { return x > y ? x : y ; }
template < typename type >
inline type min( const type& x , const type& y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , const type& y )
	{ return x >= y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , const type& y )
	{ return x <= y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e6 + 33 ;
static const int mod = 1e9 + 7 ;

int n ;

char s[maxn] ;

int f[maxn][5] ;

inline int add( int x , const int& y ) {
	x += y ; if( x >= mod )x -= mod ; return x ;
}

int main() {
	
	freopen( "mine.in" , "r" , stdin ) ;
	freopen( "mine.out" , "w" , stdout ) ;
	
	scanf( "%s" , s ) ;
	n = strlen( s ) ;
	
	switch( s[0] ) {
		case '?' : f[0][0] = f[0][1] = f[0][4] = 1 ; break ;
		case '*' : f[0][0] = 1 ; break ;
		case '0' : f[0][1] = 1 ; break ;
		case '1' : f[0][4] = 1 ; break ;
		case '2' : return puts( "0" ) , 0 ; break ;
	}
	
	FOR( i , 1 , n - 1 )
		if( s[i] == '?' ) {
			f[i][0] = add( add( f[i - 1][4] , f[i - 1][3] ) , f[i - 1][0] ) ;
			f[i][1] = f[i][4] = add( f[i - 1][2] , f[i - 1][1] ) ;
			f[i][2] = f[i][3] = f[i - 1][0] ;
		}
		else if( s[i] == '*' )
			f[i][0] = add( add( f[i - 1][4] , f[i - 1][3] ) , f[i - 1][0] ) ;
		else if( s[i] == '0' )
			f[i][1] = add( f[i - 1][2] , f[i - 1][1] ) ;
		else if( s[i] == '1' )
			f[i][2] = f[i - 1][0] ,
			f[i][4] = add( f[i - 1][1] , f[i - 1][2] ) ;
		else if( s[i] == '2' )
			f[i][3] = f[i - 1][0] ;
	
	int ans = 0 ;
	
	FOR( i , 0 , 2 )
		ans = add( ans , f[n - 1][i] ) ;
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
