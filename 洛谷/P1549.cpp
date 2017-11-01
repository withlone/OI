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
inline bool chkmax( type& x , const type& y ) {
	return x > y ? false : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x < y ? false : ( x = y , true ) ;
}
template < typename type >
inline void swap( type& x , type& y ) { type t = x ; x = y ; y = t ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 13 ;
static const int maxm = 203 ;

int n ;
int N ;
int cnt ;
int anser = ~0U >> 1 ;
bool f ;

bool V[maxm] ;
int pr[maxm] ;

bool use[maxm] ;
int num[maxn][maxn] ;
int ans[maxn][maxn] ;

inline void init() {
	For( i , 2 , 200 ) {
		if( !V[i] )pr[ ++cnt ] = i ;
		for( register int j = 1 ; j <= cnt && pr[j] * i <= 200 ; ++j ) {
			V[ pr[j] * i ] = true ;
			if( !( i % pr[j] ) )break ;
		}
	}
}

inline bool chk_at( int x , int y , int z ) {
	if( x != 1 && V[ num[x - 1][y] + z ] )return false ;
	if( y != 1 && V[ num[x][y - 1] + z ] )return false ;
	return true ;
}

inline void display() {
	int tot = -num[1][1] ;
	FOR( i , 1 , n )tot += num[1][i] + num[i][1] ;
	if( f && tot > anser )return ;
	anser = tot ;
	return f = true , memcpy( ans , num , sizeof ans ) , void() ;
}

void dfs( int x , int y , int sumer ) {
	if( sumer > anser )return ;
	if( y == n + 1 )return dfs( x + 1 , 1 , sumer ) ;
	FOR( i , 2 , N ) if( !use[i] && chk_at( x , y , i ) ) {
		use[i] = true ; num[x][y] = i ;
		if( x == n && y == n )display() ;
		dfs( x , y + 1 , ( x == 1 || y == 1 ) * i + sumer ) ;
		use[i] = false ;
	}
}

int main() {
	
	init() ;
	
	scanf( n ) ;
	N = n * n ;
	
	num[1][1] = use[1] = 1 ;
	dfs( 1 , 2 , 1 ) ;
	
	if( f )
		For( i , 1 , n ) {
			FOR( j , 1 , n )printf( "%d " , ans[i][j] ) ;
			putchar( 10 ) ;
		}
	else
		puts( "NO" ) ;
	
	return 0 ;
}
