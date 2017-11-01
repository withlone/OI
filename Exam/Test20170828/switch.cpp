#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )
#define Rep( i , _begin , _add ) for( int i = (_begin) ; i ; i = (_add) )

template< typename type >inline type min ( type x , type y ){ return x < y ? x : y ; }
template< typename type >inline void swap( type &x , type &y ){ type t = x ; x = y ; y = t ; }
template< typename type >inline void scanf( type &in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ; ch > '9' || ch < '0' ; ch = getchar() )if( ch == '-' )f = -1 ;
	for( ; ch >='0' && ch <='9' ; ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

typedef long long LL;
static const int maxn = 5e3 + 10;
static const int maxm = 1e6 + 10;

template< class type >
class priority_queue{
	
	private :
		
		int size;
		type T[maxm * 10];
		
	public :
		
		void clear(){ size = 0 ; }
		
		bool empty(){ return !size ; }
		
		type top(){ return T[1] ; }
		
		void push( type x ){
			T[ ++size ] = x ;
			int p = size ;
			while( p != 1 && T[p] < T[p >> 1] ){
				swap( T[p] , T[p >> 1] ) ;
				p >>= 1;
			}
		}
		
		void pop(){
			T[1] = T[ size-- ] ;
			int p = 1 ;
			while( ( p << 1 ) <= size && min( T[p << 1] , T[p << 1 | 1] ) < T[p] ){
				int t = T[p << 1] < T[p << 1 | 1] ? p << 1 : p << 1 | 1;
				swap( T[p] , T[t] );
				p = t;
			}
		}
		
};

class par{
	
	public :
		int first;
		int second;
		
		par(){ first = second = 0 ; }
		par( int a , int b ){ first = a ; second = b ; }
		
		bool operator < ( par t ) const { return first < t.first ; }
		bool operator > ( par t ) const { return first > t.first ; }
};

int n;
		
int cost[maxn];

int Ct;
int Ht[maxn];
int Nt[maxm];
int to[maxm];
LL Dt[maxm];

void Ins( int x , int y , LL z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
}

void read_in(){
	scanf( n ) ;
	
	For( i , 1 , n )scanf( cost[i] ) ;
	
	For( i , 1 , n ){
		int tot , x ;
		scanf( tot );
		For( I , 1 , tot )
			scanf( x ) , Ins( i , x , 1LL * I * cost[i] ) ;
	}
}

void dijkstra(){
	static priority_queue < par > que;
	static LL dis[maxn];
	static bool V[maxn];
	memset( dis , 0x3f , sizeof( LL ) * ( n + 2 ) );
	memset( V , 0 , sizeof( bool ) * ( n + 2 ) );
	que.clear();
	que.push( par( dis[1] = 0 , 1 ) );
	while( !que.empty() ){
		int x = que.top().second ; que.pop() ;
		if( V[x] )continue;
		V[x] = true;
		Rep( i , Ht[x] , Nt[i] )
			if( dis[to[i]] > dis[x] + Dt[i] && !V[to[i]] ){
				dis[to[i]] = dis[x] + Dt[i] ;
				que.push( par( dis[to[i]] , to[i] ) );
			}
	}
	printf("%lld\n" , dis[n + 1] );
}

int main(){
	
	freopen("switch.in","r",stdin);
	freopen("switch.out","w",stdout);
	
	read_in();
	
	dijkstra();
	
	return 0;
}
