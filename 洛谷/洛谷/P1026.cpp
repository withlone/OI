#include<cstdio>
#include<cstring>
#include<algorithm>

using std :: swap ;

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template < typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }
template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 200 + 10 ;

int p ;
int k ;
int s ;
int len ;

int lenth[10] ;

int f[maxn][maxn] ;

char str[maxn] ;
char dir[10][maxn] ;

inline bool chk( int x , int y ) {
	For( i , 0 , lenth[x] - 1 )
		if( dir[x][i] != str[y + i] )return false ;
	return true ;
}

inline int calc( int l , int r ) {
	int res = 0 ;
	For( i , 1 , s ) For( j , l , r - lenth[i] + 1 )
		res += chk( i , j ) ;
	return res ;
}

int main() {
	
	scanf( p ) ; scanf( k ) ;
	For( i , 1 , p )
		scanf( "%s" , str + ( i - 1 ) * 20 + 1 ) ;
	
	len = p * 20 ;
	
	scanf( s ) ;
	For( i , 1 , s )scanf( "%s" , dir[i] ) , lenth[i] = strlen( dir[i] ) ;
	for( int i = 1 ; i <= s ; ++i ) for( int j = i + 1 ; j <= s ; ++j )
		if( !strcmp( dir[i] , dir[j] ) )
			swap( dir[j] , dir[s] ) , --s ;
	memset( f , -0x3f , sizeof f ) ;
	For( i , 1 , len )f[i][1] = calc( 1 , i ) ;
	For( j , 2 , k ) For( i , 1 , len ) For( t , 1 , i - 1 )
		chkmax( f[i][j] , f[t][j - 1] + calc( t + 1 , i ) ) ;
	
	printf( "%d\n" , f[len][k] ) ;
	
	return 0 ;
}
