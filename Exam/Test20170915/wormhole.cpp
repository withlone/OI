#include<map>
#include<queue>
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

static const int maxp = 40 + 10 ;
static const int maxx = 1e4 + 10 ;
static const int maxm = 1e6 + 10 ;
static const int mod = ( 1 << 10 ) - 1 ;
static const int inf = ~0U >> 1 ;

map < int , int > mp ;
priority_queue< int , vector< int > , greater< int > > qt ;

int W ;
int S ;
int P ;
int dt ;
int cnt ;

int A[maxp] ;
int B[maxp] ;

int at[maxx] ;
int dir[maxp << 1] ;
bool Vis[maxx] ;

int dis[maxx] ;
bool V[maxx] ;

int Ct ;
int Ht[maxx] ;
int Nt[maxm] ;
int to[maxm] ;
int Dt[maxm] ;

void ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
	if( !Vis[y] )qt.push( at[y] ) ;
}

int get( int x ){
	if( !mp[x] )mp[x] = ++cnt ;
	int t = mp[x] ;
	at[t] = x ;
	return t ;
}

int spfa(){
	static int que[mod + 10] ;
	int head = 0 , tail = 0 ;
	For( i , 0 , cnt )dis[i] = inf , V[i] = false ;
	que[ ++tail ] = 0 ; dis[0] = 0 ;
	while( head != tail ){
		int x = que[ ++head &= mod ] ; V[x] = false ;
		Rep( i , Ht[x] , Nt[i] )
			if( dis[to[i]] > dis[x] + Dt[i] ){
				dis[to[i]] = dis[x] + Dt[i] ;
				if( !V[to[i]] )
					V[to[i]] = true , que[ ++tail &= mod ] = to[i] ;
			}
	}
	return dis[get( W )] ;
}

void build_edge(){
	mp.clear() ;
	int t = Ct = cnt = 0 ;
	memset( Ht , 0 , sizeof Ht ) ;
	memset( at , 0 , sizeof at ) ;
	memset( Vis , 0 , sizeof Vis ) ;
	For( i , 1 , P )
		ins( t = get( A[i] ) , get( B[i] ) , 0 ) , Vis[t] = true ;
	For( i , 1 , S )ins( 0 , get( i ) , 1 ) ;
	while( !qt.empty() ){
		int x = get( qt.top() ) ; qt.pop() ;
		if( Vis[x] )continue ;
		Vis[x] = true ;
		int y = lower_bound( 1 + dir , 1 + dt + dir , at[x] ) - dir ;
		if( dir[y] - at[x] > S ){
			int t1 = ( dir[y] - at[x] ) / S ;
			t = t1 * S + at[x] ;
			if( dir[y] == t )t -= S , --t1 ;
			if( at[x] >= t )goto nxtdoor ;
			if( t <= W )ins( x , get( t ) , t1 ) ;
		}
		else{
			nxtdoor :
			For( i , 1 , S )
				if( at[x] + i > W )break ;
				else ins( x , get( at[x] + i ) , 1 ) ;
		}
	}
}

int main(){
	
	freopen( "wormhole.in" , "r" , stdin ) ;
	freopen( "wormhole.out" , "w" , stdout ) ;
	
	while( scanf( W ) ){
		scanf( S ) ; scanf( P ) ;
		dir[ dt = 1 ] = W ;
		For( i , 1 , P )
			scanf( A[i] ) , scanf( B[i] ) ,
			dir[ ++dt ] = A[i] , dir[ ++dt ] = B[i] ;
		sort( 1 + dir , 1 + dt + dir ) ;
		dt = unique( 1 + dir , 1 + dt + dir ) - dir - 1 ;
		build_edge() ;
		printf("%d\n" , spfa() ) ;
	}
	
	return 0 ;
}
