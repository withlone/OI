#include<cstdio>
#include<algorithm>

using namespace std ;

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
inline bool chkmax( tp& x , const tp& y ) {
	return ( x >= y ) ? false : ( x = y , true ) ;
}
template < typename tp >
inline bool chkmin( tp& x , const tp& y ) {
	return ( x <= y ) ? false : ( x = y , true ) ;
}

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 2e5 + 11 ;
static const int maxm = 8e5 + 11 ;
static const int inf = 2e9 ;

int n ;

int pi[maxn] ;
int ci[maxn] ;

int f[maxn] ;

pair < int , int > T1[maxm] , T2[maxm] ;

pair < int , int > update( int rt , int l , int r , int rmax ) {
	if( l == r ) return T1[rt].second > rmax ? T1[rt] : make_pair( inf , 0 ) ;
	int mid = l + r >> 1 ;
	if( T1[rt << 1 | 1].second <= rmax )
		return update( rt << 1 , l , mid , rmax ) ;
	pair < int , int > t = update( rt << 1 | 1 , mid + 1 , r , rmax ) ;
	return make_pair( min( t.first , T2[rt].first ) , t.second ) ;
}

inline void up( int rt , int l , int r ) {
	T2[rt] = update( rt << 1 , l , l + r >> 1 , T1[rt << 1 | 1].second ) ;
	T1[rt] = make_pair( min( T1[rt << 1 | 1].first , T2[rt].first )
					, max( T1[rt << 1].second , T1[rt << 1 | 1].second ) ) ;
}

void modify( int rt , int l , int r , int x , pair < int , int > c ) {
	if( l == r ) return T1[rt] = c , void() ;
	int mid = l + r >> 1 ;
	if( x <= mid ) modify( rt << 1 , l , mid , x , c ) ;
	else modify( rt << 1 | 1 , mid + 1 , r , x , c ) ;
	up( rt , l , r ) ;
}

void query( int rt , int l , int r , int R , pair < int , int >& c ) {
	if( r <= R ) {
		if( !c.second ) c = T1[rt] ;
		else {
			pair < int , int > t = update( rt , l , r , c.second ) ;
			chkmin( c.first , t.first ) ;
			chkmax( c.second , T1[rt].second ) ;
		}
		return ;
	}
	int mid = l + r >> 1 ;
	if( mid < R ) query( rt << 1 | 1 , mid + 1 , r , R , c ) ;
	query( rt << 1 , l , mid , R , c ) ;
}

void build( int rt , int l , int r ) {
	T1[rt] = T2[rt] = make_pair( inf , 0 ) ;
	if( l == r ) return ;
	int mid = l + r >> 1 ;
	build( rt << 1 , l , mid ) ;
	build( rt << 1 | 1 , mid + 1 , r ) ;
}

int main() {
	
	freopen( "knows.in" , "r" , stdin ) ;
	freopen( "knows.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	FOR( i , 1 , n ) scanf( pi[i] ) ;
	FOR( i , 1 , n ) scanf( ci[i] ) ;
	
	build( 1 , 1 , n ) ;
	
	int mn = inf ;
	
	FOR( i , 1 , n ) {
		f[i] += ci[i] ;
		if( mn < pi[i] ) {
			pair < int , int > res = make_pair( inf , 0 ) ;
			query( 1 , 1 , n , pi[i] - 1 , res ) ;
			f[i] += res.first ;
		} else mn = pi[i] ;
		modify( 1 , 1 , n , pi[i] , make_pair( f[i] , i ) ) ;
	}
	
	printf( "%d\n" , T1[1].first ) ;
	
	return 0 ;
}
