#include<cstdio>

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
	return x > y ? false : x = y , true ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x < y ? false : x = y , true ;
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

static const int maxn = 2e5 + 3 ;
static const int maxm = 4e5 + 9 ;
static const int mod = 10007 ;

int n ;

int ans1 ;
int ans2 ;

int val[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins( const int& x , const int& y ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

inline int add( int x , const int& y ) {
	x += y ; if( x >= mod ) x -= mod ; return x ;
}

inline void dfs( int x , int f ) {
	int first = 0 , second = 0 , sum = 0 , tmp = 0 ;
	REP( i , Ht[x] , Nt[i] ) if( to[i] != f ) {
		if( first >= val[to[i]] )
			chkmax( second , val[to[i]] ) ;
		else second = first , first = val[to[i]] ;
		sum += val[to[i]] ;
	}
	REP( i , Ht[x] , Nt[i] ) if( to[i] != f ) {
		chkmax( ans1 , val[to[i]] * val[f] ) ;
		if( val[to[i]] == first )
			chkmax( ans1 , val[to[i]] * second ) ;
		else chkmax( ans1 , val[to[i]] * first ) ;
		ans2 = add( ans2 , val[to[i]] * val[f] % mod ) ;
		tmp = add( tmp , 1LL * val[to[i]] * ( sum - val[to[i]] ) % mod ) ;
		dfs( to[i] , x ) ;
	}
	ans2 = add( ans2 , tmp * 5004 % mod ) ;
}


int main() {
	
	freopen( "link.in" , "r" , stdin ) ;
	freopen( "link.out" , "w" , stdout ) ;
	
	register int x , y ;
	
	scanf( n ) ;
	FOR( i , 1 , n - 1 ) {
		scanf( x ) ; scanf( y ) ;
		ins( x , y ) , ins( y , x ) ;
	}
	
	FOR( i , 1 , n )scanf( val[i] ) ;
	
	dfs( 1 , 0 ) ;
	
	printf( "%d %d\n" , ans1 , ( ans2 << 1 ) % mod ) ;
	
	return 0 ;
}
