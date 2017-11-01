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

typedef long long LL ;
static const int maxn = 1e3 + 10 ;
static const int maxm = 2e6 + 10 ;
static const int inf = ~0U >> 1 ;

int n ;
int S ;
int T ;
int ans ;

int A[maxn] ;
int B[maxn] ;

int cur[maxn] ;
int dep[maxn] ;

int Ct = 1 ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;
int cap[maxm] ;

void ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

bool bfs(){
	static int que[maxn] ;
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

int dfs( int x , int maxflow ){
	if( x == T )return maxflow ;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[to[i]] == dep[x] + 1 && cap[i] ){
			int t = dfs( to[i] , min( maxflow , cap[i] ) ) ;
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0 ;
}

int dinic(){
	int res = 0 , t ;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur ) ;
		while( t = dfs( S , inf ) )res += t ;
	}
	return res ;
}

int gcd( int x , int y ){ return !y ? x : gcd( y , x % y ) ; }

int main(){
	
	scanf( n ) ;
	For( i , 1 , n )scanf( A[i] ) ;
	For( i , 1 , n )scanf( B[i] ) , ans += B[i] ;
	
	S = 0 ; T = n + 1 ;
	For( i , 1 , n )
		if( A[i] & 1 )
			ins( S , i , B[i] ) ;
		else
			ins( i , T , B[i] ) ;
	For( i , 1 , n )For( j , i + 1 , n )
		if( gcd( A[i] , A[j] ) == 1 ){
			LL t1 = 1LL * A[i] * A[i] + 1LL * A[j] * A[j] ;
			LL t2 = (LL)sqrt( t1 ) ;
			if( t1 == t2 * t2 ){
				if( A[i] & 1 )
					ins( i , j , inf ) ;
				else
					ins( j , i , inf ) ;
			}
		}
	
	printf("%d\n" , ans - dinic() );
	
	return 0 ;
}
