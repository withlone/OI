#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

static const int len = 1 << 15 ;
char buffer[len] , *beginer , *ender ;

inline char Getchar(){
	if( beginer == ender )
		ender = ( beginer = buffer ) + fread( buffer , 1 , len , stdin ) ;
	return beginer == ender ? EOF : *beginer++ ;
}

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }

template< typename type >
inline type scanf( type& in ){
	in = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 20 + 10 ;
static const int maxd = 100 + 10 ;
static const int maxm = 800 + 10 ;
static const int mod = ( 1 << 5 ) - 1 ;

int d ;
int n ;
int m ;
int k ;
int D ;

LL F[maxd] ;

bool limit[maxn] ;
bool cnot[maxn][maxd] ;
int cost[maxd][maxd] ;

int dis[maxn] ;
bool V[maxn] ;

int Ct = 1 ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;
int dt[maxm] ;

inline void ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; dt[Ct] = z ;
}

int spfa(){
	static int que[mod + 10] ;
	int head = 0 , tail = 0 ;
	memset( V , 0 , sizeof V ) ;
	memset( dis , 0x3f , sizeof dis ) ;
	que[ ++tail ] = 1 ; dis[1] = 0 ;
	while( head != tail ){
		int x = que[ ++head &= mod ] ; V[x] = false ;
		Rep( i , Ht[x] , Nt[i] )
			if( dis[to[i]] > dis[x] + dt[i] && !limit[to[i]] ){
				dis[to[i]] = dis[x] + dt[i] ;
				if( !V[to[i]] )
					V[to[i]] = true , que[ ++tail &= mod ] = to[i] ;
			}
	}
	return dis[n] ;
}

LL dp(){
	For( i , 1 , d )F[i] = 1LL * cost[1][i] * i ;
	For( i , 1 , d )
		For( j , 1 , i - 1 )
			F[i] = min( F[i] , F[j] + k + 1LL * cost[j + 1][i] * ( i - j ) ) ;
	return F[d] ;
}

int main(){
	
	register int x , y , z ;
	
	scanf( d ) ; scanf( n ) ; scanf( k ) ; scanf( m ) ;
	
	For( i , 1 , m ){
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		ins( x , y , z ) ; ins( y , x , z ) ;
	}
	
	scanf( D ) ;
	
	while( D-- ){
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		For( j , y , z )cnot[x][j] = true ;
	}
	
	For( i , 1 , d ){
		memset( limit , 0 , sizeof limit ) ;
		For( j , i , d ){
			For( s , 1 , n )limit[s] |= cnot[s][j] ;
			cost[i][j] = spfa() ;
		}
	}
	
	printf("%lld\n" , dp() ) ;
	
	return 0 ;
}
