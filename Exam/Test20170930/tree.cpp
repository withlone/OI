#include<cstdio>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )
#define FOR( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define LOP( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define REP( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type max( const type& x , const type& y ) { return x > y ? x : y ; }
template < typename type >
inline type min( const type& x , const type& y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , const type& y ) {
	return x >= y ? false : x = y , true ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x <= y ? false : x = y , true ;
}

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 5e5 + 29 ;
static const int maxm = 2e6 + 39 ;
static const int maxx = 524341 ;
static const LL inf = 1e15 ;
static const int mod = ( 1 << 19 ) - 1 ;

int n ;
int m ;

int ki[maxn] ;
int li[maxn] ;
int ri[maxn] ;
int ci[maxn] ;

LL dis[maxn] ;
bool V[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;
int Dt[maxm] ;

inline void ins( const int& x , const int& y , const int& z ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
}

inline LL spfa( const int& S , const int& T ) {
	static int que[maxx] ;
	int head = 0 , tail = 0 ;
	FOR( i , S , T )dis[i] = -inf ;
	que[ ++tail ] = S ; dis[S] = 0LL ;
	while( head != tail ) {
		int x = que[ ++head &= mod ] ; V[x] = false ;
		REP( i , Ht[x] , Nt[i] )
			if( dis[to[i]] < dis[x] + Dt[i] ) {
				dis[to[i]] = dis[x] + Dt[i] ;
				if( !V[to[i]] )
					V[to[i]] = true , que[ ++tail &= mod ] = to[i] ;
			}
	}
	return dis[T] ;
}

int main() {
	
	freopen( "tree.in" , "r" , stdin ) ;
	freopen( "tree.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ;
	FOR( i , 1 , n )scanf( ki[i] ) ;
	FOR( i , 1 , m )scanf( li[i] ) , scanf( ri[i] ) , scanf( ci[i] ) ;
	
	FOR( i , 1 , m )
		ins( li[i] - 1 , ri[i] , ci[i] ) ;
	FOR( i , 1 , n )
		ins( i - 1 , i , 0 ) ,
		ins( i , i - 1 , -ki[i] ) ;
	
	printf( "%lld\n" , spfa( 0 , n ) ) ;
	
	return 0 ;
}
