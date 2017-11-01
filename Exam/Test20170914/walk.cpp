#include<cstdio>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

static const int len = 1 << 15 ;
char buffer[len] , *beginer , *ender ;

char Getchar(){
	if( beginer == ender )
		ender = ( beginer = buffer ) + fread( buffer , 1 , len , stdin ) ;
	return beginer == ender ? EOF : *beginer++ ;
}

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >
inline void swap( type& x , type& y ){ type t = x ; x = y ; y = t ; }
template< typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }
template< typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }

template< typename type >
inline type scanf( type& in ){
	in = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 1e6 + 10 ;
static const int maxx = 1e3 + 10 ;
static const int maxm = maxn << 1 ;

int n ;
bool fcase ;

int val[maxn] ;
LL dp1[maxn] ;
LL dp2[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

void ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ;
}

void dfs( int x , int f ){
	dp1[x] = val[x] ;
	Rep( i , Ht[x] , Nt[i] )if( to[i] != f ){
		dfs( to[i] , x ) ;
		dp1[x] += max( 0LL , dp1[to[i]] ) ;
		dp2[x] += dp2[to[i]] ;
	}
	chkmax( dp2[x] , dp1[x] ) ;
}

int main(){
	
	freopen( "walk.in" , "r" , stdin ) ;
	freopen( "walk.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	For( i , 1 , n - 1 ){
		int x , y ;
		scanf( x ) ; scanf( y ) ;
		ins( x , y ) ;
	}
	
	For( i , 1 , n )scanf( val[i] ) ;
	
	dfs( 1 , 0 ) ;
	
	printf("%lld\n" , dp2[1] ) ;
	
	return 0 ;
}
