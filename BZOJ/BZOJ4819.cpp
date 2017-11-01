#include<cmath>
#include<cstdio>
#include<cstring>

using namespace std ;

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) \
for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

typedef double DB ;
static const int maxn = 100 + 10 ;
static const int maxx = maxn << 1 ;
static const int maxm = 1e6 + 10 ;
static const int mod = ( 1 << 8 ) - 1 ;
static const int inf = ~0U >> 1 ;
static const DB eps = 1e-7 ;

int cmp( DB x , DB y ){ return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ; }

int n ;
int S ;
int T ;

int a[maxn][maxn] ;
int b[maxn][maxn] ;

int que[mod + 10] ;
DB dis[maxx] ;
int pre[maxx] ;
bool V[maxx] ;

int Ct = 1 ;
int Ht[maxx] ;
int Nt[maxm] ;
int to[maxm] ;
DB Dt[maxm] ;
int cap[maxm] ;

void ins( int x , int y , DB p , int q ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = p ; cap[Ct] = q ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; Dt[Ct] = -p; cap[Ct] = 0 ;
}

DB EK(){
	DB ans = 0 ;
	while( true ){
		memset( V , 0 , sizeof V ) ;
		For( i , S , T + 1 )dis[i] = inf ;
		int head = 0 , tail = 0 ;
		que[ ++tail ] = S ; dis[S] = 0 ;
		while( head != tail ){
			int x = que[ ++head &= mod ] ; V[x] = false ;
			Rep( i , Ht[x] , Nt[i] )
				if( cmp( dis[to[i]] , dis[x] + Dt[i] ) == 1 && cap[i] ){
					dis[to[i]] = dis[x] + Dt[i] ; pre[to[i]] = i ;
					if( !V[to[i]] )
						V[to[i]] = true , que[ ++tail &= mod ] = to[i] ;
				}
		}
		if( !cmp( dis[T] , dis[T + 1] ) )return ans ;
		int maxflow = inf ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			maxflow = min( maxflow , cap[ pre[i] ] ) ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			cap[ pre[i] ] -= maxflow , cap[ pre[i] ^ 1 ] += maxflow ;
		ans += dis[T] * maxflow ;
	}
}

bool chk( DB x ){
	Ct = 1 ; memset( Ht , 0 , sizeof Ht ) ;
	For( i , 1 , n )
		ins( S , i , 0 , 1 ) ,
		ins( i + n , T , 0 , 1 ) ;
	For( i , 1 , n )For( j , 1 , n )
		ins( i , j + n , x * b[i][j] - a[i][j] , 1 ) ;
	return EK() < 0 ;
}

int main(){
	
	scanf( n ) ;
	
	For( i , 1 , n )For( j , 1 , n )scanf( a[i][j] ) ;
	For( i , 1 , n )For( j , 1 , n )scanf( b[i][j] ) ;
	
	S = 0 ; T = n << 1 | 1 ;
	
	DB l = 0 , r = 1e6 ;
	while( cmp( l , r ) ){
		DB mid = ( l + r ) / 2.0 ;
		if( chk( mid ) )l = mid ;
		else r = mid ;
	}
	
	printf("%.6lf\n" , l ) ;
	
	return 0 ;
}
