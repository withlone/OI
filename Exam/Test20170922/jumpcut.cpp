#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template < typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 1e5 + 10 ;

int cases ;
int a ;
int S ;
int ct ;
int cnt ;
LL ans ;
bool f ;

int seq[maxn] ;
int cmp[maxn] ;
int array[maxn] ;
int extra[maxn] ;
bool V[maxn] ;

inline void diver( int S ) {
	for( cnt = 0 ; S ; S /= 10 )
		seq[ ++cnt ] = S % 10 ;
}

inline int get( int i ) { return extra[i] - extra[i - 1] ; }

inline bool chk() {
	memset( V , 0 , sizeof V ) ;
	For( i , 1 , cnt )V[ array[i] ] = true ;
	int tct = 0 ;
	For( i , 1 , ct )if( !V[i] )extra[ ++tct ] = i ;
	For( i , 3 , tct )
		if( get( i ) != get( i - 1 ) )return false ;
	return true ;
}

void dfs( int x , int pos ) {
	if( x == cnt + 1 )return f = chk() , void() ;
	For( i , pos , ct )
		if( cmp[i] == seq[x] ) {
			array[x] = i ;
			dfs( x + 1 , i + 1 ) ;
			if( f )return ;
		}
}

inline bool chk( LL x , int S ) {
	for( ct = 0 ; x ; x /= 10 )
		cmp[ ++ct ] = x % 10 ;
	f = false ;
	dfs( 1 , 1 ) ;
	return f ;
}

inline LL get() {
	For( i , 1 , 1e6 ) {
		LL x = 1LL * a * i ;
		if( chk( x , S ) )return x ;
	}
}

int main() {
	
	freopen( "jumpcut.in" , "r" , stdin ) ;
	freopen( "jumpcut.out" , "w" , stdout ) ;
	
	scanf( cases ) ;
	
	while( cases-- ) {
		scanf( a ) ; scanf( S ) ;
		diver( S ) ;
		printf( "%lld\n" , get() ) ;
	}
	
	return 0 ;
}
