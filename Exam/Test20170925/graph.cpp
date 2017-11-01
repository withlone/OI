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
inline type max( type x , type y ) { return x > y ? x : y ; }
template < typename type >
inline type min( type x , type y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , type y ) { return x > y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , type y ) { return x < y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 2129 ;
static const int maxm = 4099981 ;

int cases ;
int n ;

int idg[maxn] ;

char graph[maxn][maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins( int x , int y ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; idg[y]++ ;
}

inline void init() {
	Ct = 0 ;
	memset( Ht , 0 , sizeof(int) * (n + 1) ) ;
	memset( idg , 0 , sizeof(int) * (n + 1) ) ;
}

inline bool chk_circle() {
	static int que[maxn] ;
	int head = 0 , tail = 0 ;
	FOR( i , 1 , n )if( !idg[i] )que[ ++tail ] = i ;
	while( head != tail ) {
		int x = que[ ++head ] ;
		REP( i , Ht[x] , Nt[i] )
			if( !--idg[to[i]] )que[ ++tail ] = to[i] ;
	}
	return head == n ;
}

int main() {
	
	freopen( "graph.in" , "r" , stdin ) ;
	freopen( "graph.out" , "w" , stdout ) ;
	
	scanf( cases ) ;
	
	while( cases-- ) {
		scanf( n ) ;
		FOR( i , 1 , n )
			scanf( "%s" , graph[i] + 1 ) ;
		init() ;
		For( i , 1 , n ) FOR( j , 1 , n )
			if( graph[i][j] != 'U' )ins( i , j ) ;
		if( !chk_circle() ){ puts( "N" ) ; continue ; }
		init() ;
		For( i , 1 , n ) FOR( j , 1 , n )
			if( graph[i][j] == 'R' )ins( j , i ) ;
			else if( graph[i][j] == 'B' )ins( i , j ) ;
		puts( chk_circle() ? "T" : "N" ) ;
	}
	
	return 0 ;
}
