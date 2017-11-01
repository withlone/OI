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

template < typename tp >
inline tp max( const tp& x , const tp& y ) { return x > y ? x : y ; }
template < typename tp >
inline tp min( const tp& x , const tp& y ) { return x < y ? x : y ; }
template < typename tp >
inline bool chkmax( tp& x , const tp& y ) {
	return x >= y ? false : ( x = y , true ) ;
}
template < typename tp >
inline bool chkmin( tp& x , const tp& y ) {
	return x <= y ? false : ( x = y , true ) ;
}

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e4 + 7 ;
static const int maxx = 3e5 + 11 ;
static const int maxm = 5e6 + 11 ;
static const int moder = ( 1 << 14 ) - 1 ;

int n ;
int m ;
int mod ;

int ai[maxn] ;
int bi[maxx] ;

int dis[maxn] ;
bool V[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;
int Dt[maxm] ;

inline void ins( int x , int y , int z ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
}

inline int add( int x , int y ) {
	return ( x + y ) % mod ;
}

inline void spfa( int S ) {
	static int que[moder + 10] ;
	memset( dis , 0x3f , sizeof dis ) ;
	int head = 0 , tail = 0 ;
	que[ ++tail ] = S ; dis[S] = 0 ;
	while( head != tail ) {
		int x = que[ ++head &= moder ] ; V[x] = false ;
		REP( i , Ht[x] , Nt[i] )
			if( dis[to[i]] > dis[x] + Dt[i] ) {
				dis[to[i]] = dis[x] + Dt[i] ;
				if( !V[to[i]] )
					V[to[i]] = true , que[ ++tail &= moder ] = to[i] ;
			}
	}
}

int main() {
	
	freopen( "present.in" , "r" , stdin ) ;
	freopen( "present.out" , "w" , stdout ) ;
	
	mod = ~0U >> 1 ;
	scanf( n ) ; scanf( m ) ;
	FOR( i , 1 , n ) chkmin( mod , scanf( ai[i] ) ) ;
	FOR( i , 1 , m ) scanf( bi[i] ) ;
	
	For( i , 1 , n ) FOR( x , 0 , mod - 1 )
		if( x != add( x , ai[i] ) )
			ins( x , add( x , ai[i] ) , ai[i] ) ;
	
	spfa( 0 ) ;
	
	int ans = 0 ;
	FOR( i , 1 , m )
		if( bi[i] >= dis[ bi[i] % mod ] ) ++ans ;
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
