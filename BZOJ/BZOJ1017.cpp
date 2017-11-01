#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type max( type x , type y ) { return x > y ? x : y ; }
template < typename type >
inline type min( type x , type y ) { return x < y ? x : y ; }
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

inline char get_alp() {
	char ch = getchar() ;
	while( ch > 'Z' || ch < 'A' )ch = getchar() ;
	return ch ;
}

static const int maxn = 100 ;
static const int maxm = 2e3 + 10 ;
static const int maxe = maxn * maxn ;
static const int inf = ~0U >> 1 ;

int n ;
int m ;

int P[maxn] ;
int L[maxn] ;
int M[maxn] ;

int g[maxn][maxm] ;
int f[maxn][maxn][maxm] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxe] ;
int to[maxe] ;
int Dt[maxe] ;
int idg[maxn] ;

inline void ins( int x , int y , int z ) {
	Nt[ ++Ct ] = Ht[x] ;  Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
	idg[y]++ ;
}

void dfs( int x ) {
	if( !Ht[x] ) {
		For( i , 0 , L[x] )
			For( j , 0 , i )
				f[x][j][i * M[x]] = ( i - j ) * P[x] ;
		return ;
	}
	register int son = 0 , y ; L[x] = inf ;
	Rep( i , Ht[x] , Nt[i] ){
		dfs( to[i] ) ;
		L[x] = min( L[x] , L[to[i]] / Dt[i] ) ;
		M[x] += Dt[i] * M[to[i]] ;
	}
	L[x] = min( L[x] , m / M[x] ) ;
	For( i , 0 , L[x] ) {
		son = 0 ;
		memset( g , -0x3f , sizeof g ) ;
		g[0][0] = 0 ;
		Rep( qvq , Ht[x] , Nt[qvq] ) {
			y = to[qvq] ; ++son ;
			For( j , 0 , m )
				For( k , 0 , j )
					chkmax( g[son][j] ,
					g[son - 1][k] + f[y][i * Dt[qvq]][j - k] ) ;
		}
		For( j , 0 , i )
			For( k , 0 , m )
				chkmax( f[x][j][k] , g[son][k] + P[x] * ( i - j ) ) ;
	}
}

int main() {
	
	register int num , x , y ;
	char diff ;
	bool check = false ;
	
	memset( f , -0x3f , sizeof f ) ;
	
	scanf( n ) ; scanf( m ) ;
	
	For( i , 1 , n ) {
		scanf( P[i] ) ;
		diff = get_alp() ;
		if( diff == 'A' ) {
			scanf( num ) ;
			while( num-- ) {
				scanf( x ) ; scanf( y ) ;
				ins( i , x , y ) ;
			}
		}
		else {
			scanf( M[i] ) ; scanf( L[i] ) ;
			L[i] = min( L[i] , m / M[i] ) ;
		}
	}
	
	For( i , 1 , n )if( idg[i] )check = true ;
	
	int ans = 0 ;
	
	if( check ){
		For( i , 1 , n ) if( !idg[i] ) {
			dfs( i ) ;
			For( j , 0 , L[i] )
				For( k , 0 , m )
					chkmax( ans , f[i][j][k] ) ;
		}
	}
	else {
		For( i , 1 , n )
			For( j , 0 , L[i] )
				Lop( k , m , M[i] * j )
					chkmax( g[i][k] , g[i - 1][k - j * M[i]] + j * P[i] ) ;
		For( i , 0 , m )
			chkmax( ans , g[n][i] ) ;
	}
	
	printf("%d\n" , ans ) ;
	
	return 0 ;
}
