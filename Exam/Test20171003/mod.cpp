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
inline bool chkmax( type& x , const type& y )
	{ return x >= y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , const type& y )
	{ return x <= y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 1e5 + 19 ;
static const int maxm = 4e5 + 31 ;

int n ;
int m ;

int a[maxn] ;

int mx[maxm] ;
LL sum[maxm] ;

inline void up( int rt ) {
	mx[rt] = max( mx[rt << 1] , mx[rt << 1 | 1] ) ;
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1] ;
}

void build( int rt , int l , int r ) {
	if( l == r )return mx[rt] = sum[rt] = a[l] , void() ;
	int mid = l + r >> 1 ;
	build( rt << 1 , l , mid ) ;
	build( rt << 1 | 1 , mid + 1 , r ) ;
	up( rt ) ;
}

void change( int rt , int l , int r , int mod ) {
	if( l == r )return mx[rt] = ( sum[rt] %= mod ) , void() ;
	int mid = l + r >> 1 ;
	if( mx[rt << 1] >= mod )change( rt << 1 , l , mid , mod ) ;
	if( mx[rt << 1 | 1] >= mod )change( rt << 1 | 1 , mid + 1 , r , mod ) ;
	up( rt ) ;
}

void modify( int rt , int l , int r , int L , int R , int mod ) {
	if( l >= L && r <= R ) {
		if( mod <= mx[rt] )change( rt , l , r , mod ) ;
		return ;
	}
	int mid = l + r >> 1 ;
	if( mid >= L )modify( rt << 1 , l , mid , L , R , mod ) ;
	if( mid < R )modify( rt << 1 | 1 , mid + 1 , r , L , R , mod ) ;
	up( rt ) ;
}

void modify( int rt , int l , int r , int x , int y ) {
	if( l == r )return mx[rt] = sum[rt] = y , void() ;
	int mid = l + r >> 1 ;
	if( x <= mid )modify( rt << 1 , l , mid , x , y ) ;
	else modify( rt << 1 | 1 , mid + 1 , r , x , y ) ;
	up( rt ) ;
}

LL query( int rt , int l , int r , int L , int R ) {
	if( l >= L && r <= R )return sum[rt] ;
	int mid = l + r >> 1 ; LL res = 0LL ;
	if( mid >= L )res += query( rt << 1 , l , mid , L , R ) ;
	if( mid < R )res += query( rt << 1 | 1 , mid + 1 , r , L , R ) ;
	return res ;
}

int main() {
	
	freopen( "mod.in" , "r" , stdin ) ;
	freopen( "mod.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ;
	FOR( i , 1 , n )scanf( a[i] ) ;
	
	build( 1 , 1 , n ) ;
	
	while( m-- ) {
		register int op , x , y , z ;
		scanf( op ) ; scanf( x ) ; scanf( y ) ;
		if( op == 2 )modify( 1 , 1 , n , x , y , scanf( z ) ) ;
		else if( op == 1 )printf( "%lld\n" , query( 1 , 1 , n , x , y ) ) ;
		else modify( 1 , 1 , n , x , y ) ;
	}
	
	return 0 ;
}
