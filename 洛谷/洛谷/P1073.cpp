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

static const int maxn = 1e5 + 19 ;
static const int maxm = 2e6 + 29 ;

int n ;
int m ;

int tp ;
int dnt ;
int cnt ;

int head ;
int tail ;

int idg[maxn] ;
int que[maxn] ;

int dfn[maxn] ;
int low[maxn] ;
int bel[maxn] ;
int stack[maxn] ;
int f[maxn] ;
int g[maxn] ;
bool V[maxn] ;

int A[maxm] ;
int B[maxm] ;
int price[maxn] ;

bool vis[maxn] ;

int Ct ;
int Ht[maxn] ;
int HT[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins( int *Ht , const int& x , const int& y ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

void tarjan( const int& x ) {
	int y ;
	V[x] = true ; stack[ ++tp ] = x ;
	dfn[x] = low[x] = ++dnt ;
	REP( i , Ht[x] , Nt[i] ) {
		y = to[i] ;
		if( !dfn[y] )tarjan( y ) , chkmin( low[x] , low[y] ) ;
		else if( V[y] )chkmin( low[x] , dfn[y] ) ;
	}
	if( dfn[x] != low[x] )return ;
	++cnt ; f[cnt] = ~0U >> 1 , g[cnt] = 0 ;
	do {
		y = stack[ tp-- ] ;
		V[y] = false ;
		bel[y] = cnt ;
		chkmin( f[cnt] , price[y] ) ;
		chkmax( g[cnt] , price[y] ) ;
	} while( x != y ) ;
}

void sign_up( const int& x ) {
	vis[x] = true ;
	REP( i , Ht[x] , Nt[i] ) if( !vis[to[i]] )
		sign_up( to[i] ) ;
}

inline void tuopo( const int& S ) {
	head = 0 ; tail = 0 ;
	que[ ++tail ] = S ;
	while( head != tail ) {
		int x = que[ ++head ] ;
		REP( i , Ht[x] , Nt[i] )
			if( !--idg[to[i]] )que[ ++tail ] = to[i] ;
	}
}

int main() {
	
	scanf( n ) ; scanf( m ) ;
	FOR( i , 1 , n )scanf( price[i] ) ;
	FOR( i , 1 , m ) {
		register int x , y , z ;
		A[i] = scanf( x ) ; B[i] = scanf( y ) ; scanf( z ) ;
		ins( Ht , x , y ) ;
		if( z ^ 1 )ins( Ht , y , x ) ;
	}
	
	FOR( i , 1 , n ) if( !dfn[i] ) tarjan( i ) ;
	
	Ct = 0 ; memset( Ht , 0 , sizeof Ht ) ;
	FOR( i , 1 , m ) if( bel[ A[i] ] != bel[ B[i] ] )
		ins( Ht , bel[ B[i] ] , bel[ A[i] ] ) ;
	
	sign_up( bel[n] ) ;
	
	Ct = 0 ; memset( Ht , 0 , sizeof Ht ) ;
	FOR( i , 1 , m ) if( bel[ A[i] ] != bel[ B[i] ]
		&& vis[ bel[ A[i] ] ] && vis[ bel[ B[i] ] ] )
			ins( Ht , bel[ A[i] ] , bel[ B[i] ] ) ,
			ins( HT , bel[ B[i] ] , bel[ A[i] ] ) ,
			++idg[ bel[ B[i] ] ] ;
	
	tuopo( bel[1] ) ;
	
	For( I , 1 , tail ) {
		int x = que[I] ;
		REP( i , HT[x] , Nt[i] )
			chkmin( f[x] , f[to[i]] ) ;
	}
	LOP( I , tail , 1 ) {
		int x = que[I] ;
		REP( i , Ht[x] , Nt[i] )
			chkmax( g[x] , g[to[i]] ) ;
	}
	
	int ans = 0 ;
	FOR( i , 1 , cnt ) if( vis[i] ) chkmax( ans , g[i] - f[i] ) ;
	
	printf( "%d\n" , ans ) ;
	
	return 0 ;
}
