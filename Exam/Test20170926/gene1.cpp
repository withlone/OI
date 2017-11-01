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
	{ return x > y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , const type& y )
	{ return x < y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1000003 ;

int n ;

int f[maxn] ;
int nxt[maxn] ;

char gene[maxn] ;

inline void getnext() {
	int k = 0 ;
	FOR( i , 1 , strlen( gene ) - 1 ) {
		while( k > 0 && gene[i] != gene[k] )k = nxt[k - 1] ;
		if( gene[i] == gene[k] )++k ;
		nxt[i] = k ;
	}
}

int main() {
	
	freopen( "gene.in" , "r" , stdin ) ;
	freopen( "gene.out" , "w" , stdout ) ;
	
	scanf( "%s" , gene ) ;
	n = strlen( gene ) ;
	
	getnext() ;
	
	long long ans = 0 ;
	FOR( i , 0 , strlen( gene ) - 1 ) {
		if( nxt[i] )f[i] = f[ nxt[i] - 1 ] + 1 ;
		else f[i] = 1 ;
		ans += f[i] ;
	}
	
	printf( "%lld\n" , ans ) ;
	
	return 0 ;
}
