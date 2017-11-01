#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) \
for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

typedef long long LL ;
static const int maxn = 40 + 10 ;
static const int maxx = 2e3 + 10 ;
static const int maxm = maxx * 10 ;
static const LL inf = 1LL << 60 ;

int cases ;
int n ;
int m ;
int S ;
int T ;

LL A[maxn][maxn] ;

int cnt ;
int num[maxn][maxn] ;

int cur[maxx] ;
int dep[maxx] ;

int Ct = 1 ;
int Ht[maxx] ;
int Nt[maxm] ;
int to[maxm] ;
LL cap[maxm] ;

void ins( int x , int y , LL z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

void preparation(){
	cnt = 0 ;
	For( i , 1 , n )For( j , 1 , m )
		num[i][j] = ++cnt ;
}

bool bfs(){
	static int que[maxx] ;
	int head = 0 , tail = 0 ;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head != tail ){
		int x = que[ ++head ] ;
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[to[i]] && cap[i] ){
				dep[to[i]] = dep[x] + 1 ;
				if( to[i] == T )return true ;
				que[ ++tail ] = to[i] ;
			}
	}
	return false ;
}

LL dfs( int x , LL maxflow ){
	if( x == T )return maxflow ;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[to[i]] == dep[x] + 1 && cap[i] ){
			LL t = dfs( to[i] , min( maxflow , cap[i] ) ) ;
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0 ;
}

LL dinic(){
	LL res = 0 , t ;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur ) ;
		while( t = dfs( S , inf ) )res += t ;
	}
	return res ;
}

bool chk( LL x ){
	LL res = 0 ;
	Ct = 1 ; memset( Ht , 0 , sizeof Ht ) ;
	memset( num , 0 , sizeof num ) ;
	preparation() ;
	S = ++cnt ; T = ++cnt ;
	For( i , 1 , n )For( j , 1 , m )
		if( ( i & 1 ) ^ ( j & 1 ) ){
			ins( S , num[i][j] , x - A[i][j] ) ;
			res += x - A[i][j] ;
			if( num[i - 1][j] )
				ins( num[i][j] , num[i - 1][j] , inf ) ;
			if( num[i + 1][j] )
				ins( num[i][j] , num[i + 1][j] , inf ) ;
			if( num[i][j - 1] )
				ins( num[i][j] , num[i][j - 1] , inf ) ;
			if( num[i][j + 1] )
				ins( num[i][j] , num[i][j + 1] , inf ) ;
		}
		else
			ins( num[i][j] , T , x - A[i][j] ) ;
	return res == dinic() ;
}

int main(){
	
	scanf( cases ) ;
	
	while( cases-- ){
		
		LL l = 0 , r = inf , ans = -1 ;
		LL num1 = 0 , num2 = 0 , sum1 = 0 , sum2 = 0 ;
		
		scanf( n ) ; scanf( m ) ;
		For( i , 1 , n )For( j , 1 , m ){
			scanf( A[i][j] ) ;
			if( ( i & 1 ) ^ ( j & 1 ) )
				num1++ , sum1 += A[i][j] ;
			else
				num2++ , sum2 += A[i][j] ;
			l = max( l , A[i][j] ) ;
		}
		
		if( num1 != num2 ){
			LL t = ( sum1 - sum2 ) / ( num1 - num2 ) ;
			if( t < l || !chk( t ) )puts("-1") ;
			else printf("%lld\n" , num1 * t - sum1 ) ;
		}
		else{
			if( sum1 != sum2 ){ puts("-1") ; continue ; }
			while( l <= r ){
				LL mid = l + r >> 1;
				if( chk( mid ) )ans = mid , r = mid - 1 ;
				else l = mid + 1 ;
			}
			printf("%lld\n" , num1 * ans - sum1 ) ;
		}
		
	}
	
	return 0 ;
}
