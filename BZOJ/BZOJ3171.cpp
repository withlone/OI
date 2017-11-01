#include<cstdio>
#include<cstring>

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

static const int maxn = 15 + 10 ;
static const int maxx = maxn * maxn << 1 ;
static const int maxm = maxx * 6 ;
static const int inf = ~0U >> 1 ;
static const int mod = ( 1 << 9 ) - 1 ;

int n ;
int m ;
int S ;
int T ;

int cnt ;
int num[maxn][maxn] ;

char mp[maxn][maxn] ;

int que[mod + 10] ;
int dis[maxx] ;
int pre[maxx] ;
bool V[maxx] ;

int Ct = 1 ;
int Ht[maxx] ;
int Nt[maxm] ;
int to[maxm] ;
int Dt[maxm] ;
int cap[maxm] ;

void ins( int x , int y , int p , int q ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = p ; cap[Ct] = q ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; Dt[Ct] = -p; cap[Ct] = 0 ;
}

int EK(){
	int ans = 0 ;
	while( true ){
		memset( V , 0 , sizeof V ) ;
		memset( dis , 0x3f , sizeof dis ) ;
		int head = 0 , tail = 0 ;
		que[ ++tail ] = S ; dis[S] = 0 ;
		while( head != tail ){
			int x = que[ ++head &= mod ] ; V[x] = false ;
			Rep( i , Ht[x] , Nt[i] )
				if( dis[to[i]] > dis[x] + Dt[i] && cap[i] ){
					dis[to[i]] = dis[x] + Dt[i] ; pre[to[i]] = i ;
					if( !V[to[i]] )
						V[to[i]] = true , que[ ++tail &= mod ] = to[i] ;
				}
		}
		if( dis[T] == dis[T + 1] )return ans ;
		int maxflow = inf ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			maxflow = min( maxflow , cap[ pre[i] ] );
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			cap[ pre[i] ] -= maxflow , cap[ pre[i] ^ 1 ] += maxflow ;
		ans += dis[T] * maxflow ;
	}
}

int main(){
	
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )
		scanf( "%s" , mp[i] + 1 ) ;
	
	For( i , 1 , n )For( j , 1 , m )
		num[i][j] = ++cnt ;
	
	For( i , 1 , m )num[0][i] = num[n][i] , num[n + 1][i] = num[1][i] ;
	For( i , 1 , n )num[i][0] = num[i][m] , num[i][m + 1] = num[i][1] ;
	
	S = 0 ; T = cnt << 1 | 1 ;
	
	For( i , 1 , cnt )
		ins( S , i , 0 , 1 ) ,
		ins( i + cnt , T , 0 , 1 ) ;
	
	For( i , 1 , n )For( j , 1 , m ){
		ins( num[i][j] , num[i][j - 1] + cnt , 1 * ( mp[i][j] != 'L' ) , 1 ) ;
		ins( num[i][j] , num[i][j + 1] + cnt , 1 * ( mp[i][j] != 'R' ) , 1 ) ;
		ins( num[i][j] , num[i - 1][j] + cnt , 1 * ( mp[i][j] != 'U' ) , 1 ) ;
		ins( num[i][j] , num[i + 1][j] + cnt , 1 * ( mp[i][j] != 'D' ) , 1 ) ;
	}
	
	printf("%d\n" , EK() ) ;
	
	return 0 ;
}
