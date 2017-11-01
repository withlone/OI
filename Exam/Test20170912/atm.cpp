#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

static const int _len = 1 << 15 ;
char buffer[_len] , *S_T , *T_S ;

char Getchar(){
	if( S_T == T_S )
		T_S = ( S_T = buffer ) + fread( buffer , 1 , _len , stdin ) ;
	return T_S == S_T ? EOF : *S_T++ ;
}

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >
inline void swap( type& x , type& y ){ type t = x ; x = y ; y = t ; }

template< typename type >
inline void scanf( type&in ){
	in = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

static const int maxn = 5e5 + 10 ;

int n ;
int m ;
int S ;
int P ;
int tp ;
int dct ;
int cnt ;

int A[maxn] ;
int B[maxn] ;
int val[maxn] ;
int bar[maxn] ;
int mon[maxn] ;
int idg[maxn] ;

bool V[maxn] ;
int dfn[maxn] ;
int low[maxn] ;
int bel[maxn] ;
int stack[maxn] ;

int F[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxn] ;
int to[maxn] ;

void ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

void tarjan( int x ){
	int y ;
	V[x] = true ; stack[ ++tp ] = x ;
	dfn[x] = low[x] = ++dct ;
	Rep( i , Ht[x] , Nt[i] ){
		y = to[i] ;
		if( !dfn[y] )tarjan( y ) , low[x] = min( low[x] , low[y] ) ;
		else if( V[y] )low[x] = min( low[x] , dfn[y] ) ;
	}
	if( dfn[x] != low[x] )return ;
	++cnt ;
	do{
		y = stack[ tp-- ] ;
		V[y] = false ;
		bel[y] = cnt ;
		mon[cnt] += val[y] ;
	}while( x != y ) ;
}

void tuopo(){
	static int que[maxn] ;
	int head = 0 , tail = 0 ;
	For( i , 1 , cnt )if( !idg[i] )que[ ++tail ] = i ;
	memset( F , -0x3f , sizeof F ) ; F[ bel[S] ] = 0 ;
	while( head != tail ){
		int x = que[ ++head ] ; F[x] += mon[x] ;
		Rep( i , Ht[x] , Nt[i] ){
			if( !--idg[to[i]] )que[ ++tail ] = to[i] ;
			F[to[i]] = max( F[to[i]] , F[x] ) ;
		}
	}
	int ans = 0 ;
	For( i , 1 , P )
		ans = max( ans , F[ bel[ bar[i] ] ] ) ;
	printf("%d\n" , ans ) ;
}

int main(){
	
	freopen( "atm.in" , "r" , stdin ) ;
	freopen( "atm.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ;
	
	For( i , 1 , m )
		scanf( A[i] ) , scanf( B[i] ) ,
		ins( A[i] , B[i] ) ;
	
	For( i , 1 , n )scanf( val[i] ) ;
	
	scanf( S ) ; scanf( P ) ;
	
	For( i , 1 , P )scanf( bar[i] ) ;
	
	For( i , 1 , n )if( !dfn[i] )
		tarjan( i ) ;
	
	Ct = 0 ; memset( Ht , 0 , sizeof Ht ) ;
	
	For( i , 1 , m )if( bel[ A[i] ] != bel[ B[i] ] )
		ins( bel[ A[i] ] , bel[ B[i] ] ) , ++idg[ bel[ B[i] ] ];
	
	tuopo() ;
	
	return 0 ;
}
