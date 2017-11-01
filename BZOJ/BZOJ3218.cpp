#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std ;

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) \
for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

static const int maxn = 5e3 + 10 ;
static const int maxg = 7e4 + 10 ;
static const int maxx = maxg + ( maxn << 1 ) ;
static const int maxm = 5e5 + 10 ;
static const int inf = ~0U >> 1 ;

int n ;
int S ;
int T ;
int cnt ;
int ans ;

int A[maxn] ;
int at[maxn] ;

int a[maxn] ;
int b[maxn] ;
int w[maxn] ;
int li[maxn] ;
int ri[maxn] ;
int pi[maxn] ;

int dep[maxx] ;
int cur[maxx] ;
int que[maxx] ;

struct dir{
	int val ;
	int id ;
	bool operator < ( const dir& t )
		const { return val < t.val ; }
}d[maxn] ;

int Ct = 1 ;
int Ht[maxx] ;
int Nt[maxm] ;
int to[maxm] ;
int cap[maxm] ;

void ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

namespace max_flow{
	
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

namespace president_tree{
	
	int root[maxn] ;
	int Ch[maxx][2] ;
	
	void modify( int pt , int& rt , int l , int r , int x ){
		if( !rt )rt = ++cnt ;
		if( l == r )
			return ins( rt , x , inf ) ;
		int mid = l + r >> 1;
		if( at[x] <= mid )
			Ch[rt][1] = Ch[pt][1] ,
			modify( Ch[pt][0] , Ch[rt][0] , l , mid , x ) ;
		else
			Ch[rt][0] = Ch[pt][0] ,
			modify( Ch[pt][1] , Ch[rt][1] , mid + 1 , r , x ) ;
		if( Ch[rt][0] )
			ins( rt , Ch[rt][0] , inf ) ;
		if( Ch[rt][1] )
			ins( rt , Ch[rt][1] , inf ) ;
	}
	
	void query( int tp , int rt , int l , int r , int L , int R ){
		if( l > R || r < L || !rt )return ;
		if( l >= L && r <= R )
			return ins( tp , rt , inf ) ;
		int mid = l + r >> 1 ;
		query( tp , Ch[rt][0] , l , mid , L , R ) ;
		query( tp , Ch[rt][1] , mid + 1 , r , L , R ) ;
	}
	
}using namespace president_tree ;

int main(){
	
	scanf( n ) ; cnt = n << 1 ;
	
	For( i , 1 , n )
		scanf( a[i] ) , scanf( b[i] ) , scanf( w[i] ) ,
		scanf( li[i] ) , scanf( ri[i] ) , scanf( pi[i] ) ;
	
	For( i , 1 , n )d[i].val = A[i] = a[i] , d[i].id = i ;
	
	sort( 1 + d , 1 + n + d ) ;
	sort( 1 + A , 1 + n + A ) ;
	
	For( i , 1 , n )at[ d[i].id ] = i ;
	
	S = ++cnt ; T = ++cnt ;
	
	For( i , 1 , n ){
		ans += b[i] + w[i] ;
		ins( S , i , b[i] ) ;
		ins( i , T , w[i] ) ;
		ins( i , i + n , pi[i] ) ;
		int x = lower_bound( 1 + A , 1 + n + A , li[i] ) - A ;
		int y = upper_bound( 1 + A , 1 + n + A , ri[i] ) - A - 1 ;
		query( i + n , root[i - 1] , 1 , n , x , y ) ;
		modify( root[i - 1] , root[i] , 1 , n , i ) ;
	}
	
	printf("%d\n" , ans - max_flow :: dinic() ) ;
	
	return 0 ;
}
