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
static const int maxx = 8e5 + 29 ;

int n ;
int m ;
int dct ;

int Fa[maxn] ;
int val[maxn] ;
int son[maxn] ;
int dep[maxn] ;
int size[maxn] ;

int rnk[maxn] ;
int top[maxn] ;
int ender[maxn] ;

int sum[maxx] ;
int tag[maxx] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins( const int& x , const int& y ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

void dfs1( int x ) {
	size[x] = 1 ;
	REP( i , Ht[x] , Nt[i] ) if( to[i] != Fa[x] ) {
		Fa[to[i]] = x ;
		dep[ to[i] ] = dep[x] + 1 ;
		dfs1( to[i] ) ;
		size[x] += size[to[i]] ;
		if( size[to[i]] > size[son[x]] )son[x] = to[i] ;
	}
}

void dfs2( int x , int chain ) {
	rnk[x] = ++dct ;
	top[x] = chain ;
	if( son[x] )dfs2( son[x] , chain ) ;
	REP( i , Ht[x] , Nt[i] )
		if( to[i] != Fa[x] && to[i] != son[x] )
			dfs2( to[i] , to[i] ) ;
	ender[x] = dct ;
}

inline void pushdown( int rt , int L , int R ) {
	tag[rt << 1] ^= tag[rt] ; tag[rt << 1 | 1] ^= tag[rt] ;
	if( L & 1 )sum[rt << 1] ^= tag[rt] ;
	if( R & 1 )sum[rt << 1 | 1] ^= tag[rt] ;
	tag[rt] = 0 ;
}

void modify( int rt , int l , int r , int L , int R , int x ) {
	if( l >= L && r <= R ) {
		tag[rt] ^= x ;
		if( ( r - l + 1 ) & 1 )sum[rt] ^= x ;
		return ;
	}
	int mid = l + r >> 1 ;
	if( tag[rt] )pushdown( rt , mid - l + 1 , r - mid ) ;
	if( mid >= L )modify( rt << 1 , l , mid , L , R , x ) ;
	if( mid < R )modify( rt << 1 | 1 , mid + 1 , r , L , R , x ) ;
	sum[rt] = sum[rt << 1] ^ sum[rt << 1 | 1] ;
}

int query( int rt , int l , int r , int L , int R ) {
	if( l >= L && r <= R )return sum[rt] ;
	int mid = l + r >> 1 , res = 0 ;
	if( tag[rt] )pushdown( rt , mid - l + 1 , r - mid ) ;
	if( mid >= L )res ^= query( rt << 1 , l , mid , L , R ) ;
	if( mid < R )res ^= query( rt << 1 | 1 , mid + 1 , r , L , R ) ;
	return res ;
}

void build( int rt , int l , int r ) {
	if( l == r )return sum[rt] = val[l] , void() ;
	int mid = l + r >> 1 ;
	build( rt << 1 , l , mid ) ;
	build( rt << 1 | 1 , mid + 1 , r ) ;
	sum[rt] = sum[rt << 1] ^ sum[rt << 1 | 1] ;
}

inline int query( int x , int y ) {
	int res = 0 ;
	while( top[x] != top[y] ) {
		if( dep[top[x]] < dep[top[y]] )swap( x , y ) ;
		res ^= query( 1 , 1 , n , rnk[top[x]] , rnk[x] ) ;
		x = Fa[top[x]] ;
	}
	if( rnk[x] > rnk[y] )swap( x , y ) ;
	return res ^ query( 1 , 1 , n , rnk[x] , rnk[y] ) ;
}

int main() {
	
	freopen( "phase.in" , "r" , stdin ) ;
	freopen( "phase.out" , "w" , stdout ) ;
	
	register int x , y ;
	
	scanf( n ) ;
	FOR( i , 1 , n - 1 )
		scanf( x ) , scanf( y ) , ins( x , y ) , ins( y , x ) ;
	
	dep[1] = 1 ;
	dfs1( 1 ) ;
	dfs2( 1 , 1 ) ;
	
	FOR( i , 1 , n )scanf( val[rnk[i]] ) ;
	
	build( 1 , 1 , n ) ;
	
	scanf( m ) ;
	
	while( m-- ) {
		char opt = getchar() ;
		while( opt != 'C' && opt != 'Q' )opt = getchar() ;
		scanf( x ) ; scanf( y ) ;
		if( opt == 'C' ) {
			modify( 1 , 1 , n , rnk[x] , ender[x] , y ) ;
		} else {
			printf( "%d\n" , query( x , y ) ) ;
		}
	}
		
	return 0 ;
}
