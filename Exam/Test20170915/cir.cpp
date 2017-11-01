#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template< typename type >
inline type scanf( type& in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 500 + 10 ;
static const int maxx = maxn * maxn ;
static const int maxm = maxx << 2 ;
static const int inf = 1061109567 ;

template< typename type >
class heap{
	private :
		int size ;
		type T[maxm * 5] ;
	public :
		heap(){ size = 0 ; }
		void push( type x ){
			T[ ++size ] = x ;
			int p = size ;
			while( p != 1 && T[p] < T[p >> 1] ){
				swap( T[p] , T[p >> 1] ) ;
				p >>= 1 ;
			}
		}
		void pop(){
			T[1] = T[ size-- ] ;
			int p = 1 ;
			while( ( p << 1 ) <= size
				&& min( T[p << 1] , T[p << 1 | 1] ) < T[p] ){
					int t = T[p << 1] < T[p << 1 | 1] ? p << 1 : p << 1 | 1 ;
					swap( T[p] , T[t] ) ;
					p = t ;
				}
		}
		bool empty(){ return !size ; }
		type top(){ return T[1] ; }
};

int cases ;
int n ;
int m ;
int cnt ;

int num[maxn][maxn] ;
char mp[maxn][maxn] ;

int dis[maxx] ;
bool V[maxx] ;

int Ct ;
int Ht[maxx] ;
int Nt[maxm] ;
int to[maxm] ;
int Dt[maxm] ;

void ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; Dt[Ct] = z ;
}

	static heap< pair< int , int > > que ;
int dijkstra( int S , int T ){
	memset( V , 0 , sizeof V ) ;
	memset( dis , 0x3f , sizeof dis ) ;
	que.push( make_pair( dis[S] = 0 , S ) ) ;
	while( !que.empty() ){
		int x = que.top().second ; que.pop() ;
		if( V[x] )continue ;
		V[x] = true ;
		Rep( i , Ht[x] , Nt[i] )
			if( dis[to[i]] > dis[x] + Dt[i] && !V[to[i]] ){
				dis[to[i]] = dis[x] + Dt[i] ;
				que.push( make_pair( dis[to[i]] , to[i] ) ) ;
			}
	}
	return dis[T] ;
}

int main(){
	
	freopen( "cir.in" , "r" , stdin ) ;
	freopen( "cir.out" , "w" , stdout ) ;
	
	scanf( cases ) ;
	
	while( cases-- ){
		scanf( n ) ; scanf( m ) ;
		For( i , 1 , n )
			scanf( "%s" , mp[i] + 1 ) ;
		cnt = 0 ;
		For( i , 0 , n )For( j , 0 , m )
			num[i][j] = ++cnt ;
		Ct = 0 ; memset( Ht , 0 , sizeof Ht ) ;
		For( i , 1 , n )For( j , 1 , m )
			if( mp[i][j] == '/' ){
				ins( num[i][j - 1] , num[i - 1][j] , 0 ) ;
				ins( num[i - 1][j - 1] , num[i][j] , 1 ) ;
			}
			else{
				ins( num[i][j - 1] , num[i - 1][j] , 1 ) ;
				ins( num[i - 1][j - 1] , num[i][j] , 0 ) ;
			}
		int ans = dijkstra( num[0][0] , num[n][m] ) ;
		if( ans >= inf )puts( "NO SOLUTION") ;
		else printf("%d\n" , ans ) ;
	}
	
	return 0 ;
}
