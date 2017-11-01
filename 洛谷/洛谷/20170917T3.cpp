#include<cstdio>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 5e5 + 10 ;
static const int maxm = maxn << 1 ;
static const int maxx = 2e7 + 10 ;
static const int mod = 1e9 + 7 ;

int n ;
int dt ;
int cc ;
int cnt ;

int root[maxn] ;
int result[maxn] ;

int sz[maxx] ;
int sum[maxx] ;
int Ch[maxx][2] ;

int val[maxn] ;
int dir[maxn] ;
int key[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins( int x , int y ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

int merge( int x , int y , int& ans ) {
	if( !( x * y ) )return x ^ y ;
	ans = ( ans + 1LL * sz[Ch[x][0]] * sum[Ch[y][1]] % mod ) % mod ;
	ans = ( ans + 1LL * sz[Ch[y][0]] * sum[Ch[x][1]] % mod ) % mod ;
	if( !( Ch[x][0] + Ch[x][1] + Ch[y][0] + Ch[y][1] ) )
		ans = ( ans + 1LL * sz[x] * sum[y] % mod ) % mod ;
	sz[x] += sz[y] ; sum[x] = ( sum[x] + sum[y] ) % mod ;
	Ch[x][0] = merge( Ch[x][0] , Ch[y][0] , ans ) ;
	Ch[x][1] = merge( Ch[x][1] , Ch[y][1] , ans ) ;
	return x ;
}

int insert( int& rt , int l , int r , int x , int& ans ) {
	if( !rt ) rt = ++cnt ;
	sz[rt]++ ; sum[rt] = ( sum[rt] + dir[x] ) % mod ;
	if( l == r )return sz[rt] ;
	int mid = l + r >> 1 ;
	if( x <= mid ) {
		( ans += sum[Ch[rt][1]] ) %= mod ;
		return insert( Ch[rt][0] , l , mid , x , ans ) ;
	}
	return insert( Ch[rt][1] , mid + 1 , r , x , ans ) + sz[Ch[rt][0]] ;
} 

int dfs( int x , int f ) {
	Rep( i , Ht[x] , Nt[i] ) if( to[i] != f ) {
		( result[x] += dfs( to[i] , x ) ) %= mod ;
		root[x] = merge( root[x] , root[to[i]] , result[x] ) ;
	}
	cc = 1LL * insert( root[x] , 1 , dt , key[x] , result[x] ) * val[x] % mod ;
	return result[x] = ( result[x] + cc ) % mod ;
}

int main() {
	
	register int x , y ;
	
	scanf( n ) ;
	
	For( i , 1 , n - 1 ) {
		scanf( x ) ; scanf( y ) ;
		ins( x , y ) ; ins( y , x ) ;
	}
	
	For( i , 1 , n )dir[i] = scanf( val[i] ) ;
	
	sort( 1 + dir , 1 + n + dir ) ;
	dt = unique( 1 + dir , 1 + n + dir ) - dir - 1 ;
	
	For( i , 1 , n )
		key[i] = lower_bound( 1 + dir , 1 + dt + dir , val[i] ) - dir ;
	
	dfs( 1 , 0 ) ;
	
	int ans = 0 ;
	For( i , 1 , n )
		ans = ( ans + result[i] ) % mod ;
	
	printf("%d\n" , ans ) ;
	
	return 0 ;
}
