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

static const int maxn = 500 + 10 ;
static const int maxx = 26e4 + 10 ;
static const int maxm = 2e6;
static const int inf = ~0U >> 1 ;

int n ;
int S ;
int T ;
int cnt ;
int ans ;

int C[maxn] ;
int B[maxn][maxn] ;

int Ct = 1 ;
int Ht[maxx] ;
int Nt[maxm] ;
int to[maxm] ;
int cap[maxm] ;

void ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

namespace max_flow_alogirthm{
	
	int cur[maxx] ;
	int dep[maxx] ;
	int que[maxx] ;
	
	bool bfs(){
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
	
}

int main(){
	
	scanf( n ) ; cnt = n ;
	
	For( i , 1 , n )For( j , 1 , n )
		scanf( B[i][j] ) , ans += B[i][j] ;
	
	For( i , 1 , n )
		scanf( C[i] ) , ans -= C[i] ;
	
	For( i , 1 , n )
		if( B[i][i] - C[i] > 0 )
			ins( S , i , B[i][i] - C[i] ) ;
		else if( B[i][i] - C[i] < 0 )
			ins( i , T , C[i] - B[i][i] ) ;
	
	For( i , 1 , n )For( j , i + 1 , n ){
		int t = B[i][j] + B[j][i] , rt = ++cnt ;
		ins( S , rt , t ) ;
		ins( rt , i , inf ) ;
		ins( rt , j , inf ) ;
	}
	
	printf("%d\n" , ans - max_flow_alogirthm :: dinic() ) ;
	
	return 0 ;
}
