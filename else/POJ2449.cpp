#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void swap( Type &x , Type &y ){ Type t = x ; x = y ; y = t ; }
template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e3 + 10;
static const int maxm = 1e5 + 10;
static const int Inf = 1061109567;

int n , m , S , T , K;
int A[maxm] , B[maxm] , C[maxm];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , m )
		scanf( A[i] ) , scanf( B[i] ) , scanf( C[i] ) ;
	scanf( S ) ; scanf( T ) ; scanf( K ) ;
}

int Ct , Ht[maxn] , Nt[maxm] , To[maxm] , Dt[maxm];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = z;
}

bool V[maxn];int dis[maxn];

template< class type >
class priority_queue{

	public :

		priority_queue(){ size = 0 ; }

		int size;
		type T[maxm * 10];

		bool empty(){ return !size ; }

		type top(){ return T[1] ; }

		void push( type x ){
			T[ ++size ] = x;
			int p = size;
			while( p != 1 && T[p] < T[p >> 1] ){
				swap( T[p] , T[p >> 1] );
				p >>= 1;
			}
		}

		void pop(){
			T[1] = T[ size-- ];
			int p = 1;
			while( ( p << 1 ) <= size && min( T[p << 1] , T[p << 1 | 1] ) < T[p] ){
				int t = T[p << 1] < T[p << 1 | 1] ? p << 1 : p << 1 | 1;
				swap( T[p] , T[t] );
				p = t;
			}
		}
		
};

struct par{
	int first , second;
	bool operator < ( par t ) const { return first < t.first ; }
};

void dijkstra(){

	memset( dis , 0x3f , sizeof(int) * ( n + 1 ) );
	
	For( i , 1 , m )Ins( B[i] , A[i] , C[i] ) ;	
	
	static priority_queue< par >que;
	
	que.push( (par){ dis[T] = 0 , T } ) ;
	
	while( !que.empty() ){
		int x = que.top().second;que.pop();
		if( V[x] )continue;
		V[x] = true;
		Rep( i , Ht[x] , Nt[i] ){
			int y = To[i];
			if( dis[y] > dis[x] + Dt[i] && !V[y] ){
				dis[y] = dis[x] + Dt[i];
				que.push( (par){ dis[y] , y } );
			}
		}
	}
	
}

struct node{
	int x , F , G , H;
	bool operator < ( node t ) const { return F < t.F ; }
};

int num[maxn];

int Astar(){

	if( dis[S] == Inf )return -1;
	
	Ct = 0;
	memset( Ht , 0 , sizeof(int) * ( n + 1 ) );
	
	For( i , 1 , m )Ins( A[i] , B[i] , C[i] ) ;
	
	static priority_queue< node >que;
	
	que.push( (node){ S , 0 , 0 , dis[S] } );
	
	if( S == T )++K;
	
	while( !que.empty() ){
		node p = que.top();que.pop();
		++num[p.x];
		if( num[T] == K )return p.G;
		if( num[p.x] > K )continue;
		Rep( i , Ht[p.x] , Nt[i] )
			que.push( (node){ To[i] , Dt[i] + p.G + dis[To[i]] , Dt[i] + p.G , dis[To[i]] } );
	}
	return -1;
}

int main(){

	read_in();
	
	dijkstra();
	
	printf("%d\n" , Astar() );
	
	return 0;
}
