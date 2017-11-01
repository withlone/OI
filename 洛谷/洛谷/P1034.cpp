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

static const int maxn = 61 ;
static const int maxk = 7 ;

int n ;
int k ;
int ans ;

int xi[maxn] ;
int yi[maxn] ;

int ster[maxk][4] ;

#define sizer sizeof ster[0]

inline int calc( const int& i ) {
	return ( ster[i][2] - ster[i][0] ) * ( ster[i][3] - ster[i][1] ) ;
}

inline void modify( const int& i , const int& x ) {
	chkmin( ster[i][0] , xi[x] ) ;
	chkmin( ster[i][1] , yi[x] ) ;
	chkmax( ster[i][2] , xi[x] ) ;
	chkmax( ster[i][3] , yi[x] ) ;
}

inline bool chk( const int& x ) {
	For( i , 1 , x ) FOR( j , 1 , x ) if( i != j )
		if( ster[i][0] <= ster[j][2]
		&& ster[i][3] >= ster[j][1]
		&& ster[i][3] < ster[j][3] )
			return false ;
	return true ;
}

void dfs( int x , int set , int sum ) {
	if( sum > ans )return ;
	int temp[4] ;
	FOR( i , 1 , set ) {
		memcpy( temp , ster[i] , sizer ) ;
		int past = calc( i ) ;
		modify( i , x ) ;
		int now = calc( i ) ;
		if( !chk( set ) )goto end ;
		if( x == n )chkmin( ans , sum - past + now ) ;
		else dfs( x + 1 , set , sum - past + now ) ;
		end :
		memcpy( ster[i] , temp , sizer ) ;
	}
	if( set < k ) {
		modify( ++set , x ) ;
		if( x == n )chkmin( ans , sum ) ;
		else dfs( x + 1 , set , sum ) ;
		memcpy( ster[set] , ster[0] , sizer ) ;
	}
}

int main() {
	
	scanf( n ) ; scanf( k ) ;
	FOR( i , 1 , n )scanf( xi[i] ) , scanf( yi[i] ) ;
	
	FOR( i , 0 , k )
		ster[i][0] = ster[i][1] = 501 ,
		ster[i][2] = ster[i][3] = 0 ;
	
	ans = ~0U >> 1 ;
	dfs( 1 , 0 , 0 ) ;
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
