#include<cstdio>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; i-- )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >
inline void swap( type &x , type &y ){ type t = x ; x = y ; y = t ; }

template< typename type >inline void scanf( type &in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ; ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ; ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

static const int maxn = 9 + 10 ;
static const int maxm = 1e4 + 10 ;
static const int mod = 1e9 + 9 ;

int n ;
int m ;
int k ;
int sx ;
int sy ;

int mp[maxn][maxm] ;
int F[maxn][maxm] ;

void read_in(){
	scanf( n ) ; scanf( m ) ; scanf( k ) ;
	For( i , 1 , k ){
		int x1 , y1 , x2 , y2 ;
		scanf( x1 ) ; scanf( y1 ) ; scanf( x2 ) ; scanf( y2 ) ;
		mp[x1][y1] = mp[x2][y2] = i ;
	}
}

void get_start(){
	For( i , 1 , n )For( j , 1 , m )
		if( !mp[i][j] )
			return sx = i , sy = j , void() ;
}

void dfs( int x , int y , int lx , int ly ){
	if( x > 2 && mp[x - 1][y] == mp[x - 2][y] && lx != x - 2 ){
		( F[x - 2][y] += F[x][y] ) %= mod ;
		swap( mp[x][y] , mp[x - 2][y] ) ;
		dfs( x - 2 , y , x , y ) ;
		swap( mp[x][y] , mp[x - 2][y] ) ;
	}
	if( x < n - 1 && mp[x + 1][y] == mp[x + 2][y] && lx != x + 2 ){
		( F[x + 2][y] += F[x][y] ) %= mod ;
		swap( mp[x][y] , mp[x + 2][y] ) ;
		dfs( x + 2 , y , x , y ) ;
		swap( mp[x][y] , mp[x + 2][y] ) ;
	}
	if( y > 2 && mp[x][y - 1] == mp[x][y - 2] && ly != y - 2 ){
		( F[x][y - 2] += F[x][y] ) %= mod ;
		swap( mp[x][y] , mp[x][y - 2] ) ;
		dfs( x , y - 2 , x , y ) ;
		swap( mp[x][y] , mp[x][y - 2] ) ;
	}
	if( y < m - 1 && mp[x][y + 1] == mp[x][y + 2] && ly != y + 2 ){
		( F[x][y + 2] += F[x][y] ) %= mod ;
		swap( mp[x][y] , mp[x][y - 2] ) ;
		dfs( x , y + 2 , x , y ) ;
		swap( mp[x][y] , mp[x][y - 2] ) ;
	}
}

void calc(){
	int ans = 0 ;
	For( i , 1 , n )For( j , 1 , m )
		ans = ( ans + F[i][j] ) % mod ;
	printf("%d\n" , ( ans - 1 + mod ) % mod ) ;
}

int main(){
	
	freopen("move.in" , "r" , stdin) ;
	freopen("move.out" , "w" , stdout ) ;
	
	read_in() ;
	
	get_start() ;
	
	F[sx][sy] = 1 ;
	
	dfs( sx , sy , 0 , 0 ) ;
	
	calc() ;
	
	return 0 ;
}
