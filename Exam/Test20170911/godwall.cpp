#include<cstdio>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

static const int LEN = 1 << 15 ;
char buffer[LEN] , *S , *T ;

inline char Getchar(){
	if( S == T )T = ( S = buffer ) + fread( buffer , 1 , LEN , stdin ) ;
	return S == T ? EOF : *S++ ;
}

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >
inline void swap( type& x , type& y ){ type t = x ; x = y ; y = t ; }
template< typename type >
inline void scanf( type& in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

static const int maxn = 1e3 + 10 ;
static const int maxx = 1e6 + 10 ;
static const int maxm = maxx << 2 ;

int n ;
int m ;
int tp ;
int bct ;
int dct ;
int cnt ;

int num[maxn][maxn] ;

bool V[maxx] ;

int dfn[maxx] ;
int low[maxx] ;
int size[maxx] ;
int stack[maxx] ;

int Ct ;
int Ht[maxx] ;
int Nt[maxm] ;
int to[maxm] ;

void ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

void tarjan( int x ){
	int y ;
	V[x] = true ;
	stack[ ++tp ] = x ;
	dfn[x] = low[x] = ++dct ;
	Rep( i , Ht[x] , Nt[i] ){
		y = to[i] ;
		if( !dfn[y] )tarjan( y ) , low[x] = min( low[x] , low[y] ) ;
		else if( V[y] )low[x] = min( low[x] , dfn[y] ) ;
	}
	if( dfn[x] != low[x] )return ;
	++bct ;
	do{
		V[ y = stack[ tp-- ] ] = false ;
		size[bct]++ ;
	}while( x != y ) ;
}

int main(){
	
	freopen( "godwall.in" , "r" , stdin ) ;
	freopen( "godwall.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ;
	
	For( i , 1 , n )For( j , 1 , m )
		num[i][j] = ++cnt ;
	
	For( i , 1 , n )For( j , 1 , m ){
		int x ;
		scanf( x ) ;
		if( ( x & 1 ) && num[i][j + 1] )
			ins( num[i][j] , num[i][j + 1] ) ; x >>= 1 ;
		if( ( x & 1 ) && num[i][j - 1] )
			ins( num[i][j] , num[i][j - 1] ) ; x >>= 1 ;
		if( ( x & 1 ) && num[i + 1][j] )
			ins( num[i][j] , num[i + 1][j] ) ; x >>= 1 ;
		if( ( x & 1 ) && num[i - 1][j] )
			ins( num[i][j] , num[i - 1][j] ) ; x >>= 1 ;
	}
	
	For( i , 1 , cnt )if( !dfn[i] )
		tarjan( i ) ;
	
	int ans = 0 ;
	For( i , 1 , bct )
		if( size[i] != 1 )
			++ans ;
	
	printf("%d\n" , ans ) ;
	
	return 0 ;
}
