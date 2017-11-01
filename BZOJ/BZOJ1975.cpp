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

typedef double DB;
static const int maxn = 5e3 + 10;
static const int maxm = 2e5 + 10;
static const DB eps = 1e-10;

template< class type >
class priority_queue{
	
	public :
		int size;
		type T[maxm * 10];
		
		priority_queue(){ size = 0 ; }
		
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

DB abs( DB x ){ return x > 0 ? x : -x ; }
int cmp( DB x , DB y ){ return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ; }

int n;
int m;
DB magic;

int A[maxm];
int B[maxm];
DB C[maxm];

void read_in(){
	scanf( n ) ; scanf( m ) ; scanf( "%lf" , &magic );
	For( i , 1 , m )
		scanf( A[i] ) , scanf( B[i] ) , scanf( "%lf" , &C[i] );
}

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
DB Dt[maxm];

void Ins( int x , int y , DB z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = z;
}

DB dis[maxn];
bool V[maxn];

void spfa(){
	For( i , 1 , m )Ins( B[i] , A[i] , C[i] );
	For( i , 0 , n - 1 )dis[i] = 1e9;
	
	int que[maxn] , H = 0 , T = -1;
	que[ ++T ] = n;
	while( H != ( T + 1 ) % n ){
		int x = que[ H++ ];V[x] = false;
		if( H == n )H = 0;
		Rep( i , Ht[x] , Nt[i] ){
			int y = To[i];
			if( cmp( dis[y] ,dis[x] + Dt[i] ) == 1 ){
				dis[y] = dis[x] + Dt[i];
				if( !V[y] ){
					V[y] = true;
					if( T == n - 1 )que[T = 0] = y;
					else que[ ++T ] = y;
				}
			}
		}
	}
}

class node{
	
	public :
		int x;
		DB G;
		DB H;
		
		node(){ x = G = H = 0 ; }
		node( int a , DB b ){ x = a ; G = b ; H = dis[x] ; }
		
		bool operator < ( node t ) const { return cmp( G + H , t.G + t.H ) == -1 ; }
	
};

int Astar(){
	if( !cmp( dis[0] , dis[1] ) )return 0;
	Ct = 0;
	memset( Ht , 0 , sizeof(int) * ( n + 1 ) );
	For( i , 1 , m )Ins( A[i] , B[i] , C[i] );
	
	static priority_queue< node >que;
	
	que.push( node( 1 , 0 ) );
	
	int res = 0;DB tot = magic;
	
	while( !que.empty() ){
		node p = que.top();que.pop();
		if( p.x == n ){
			magic -= p.G;
			if( cmp( magic , 0 ) != 1 )return res;
			++res;continue;
		}
		Rep( i , Ht[p.x] , Nt[i] )
			if( cmp( p.G + Dt[i] , tot ) != 1 )
				que.push( node( To[i] , p.G + Dt[i] ) );
	}
	return 0;
}

int main(){
	
	read_in();
	
	spfa();
	
	printf("%d\n", Astar() );
	
	return 0;
}
