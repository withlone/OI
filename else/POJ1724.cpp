#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef pair< int , int > par;
static const int maxn = 100 + 10;
static const int maxm = 1e4 + 10;
static const int Inf = 1061109567;

int n;
int m;
int K;

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
int Dt[maxm];
int Tk[maxm];

int A[maxm];
int B[maxm];
int C[maxm];
int D[maxm];

void Ins( int x , int y , int p , int q ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = p;
	Tk[Ct] = q;
}

void read_in(){
	scanf( K ) ; scanf( n ) ; scanf( m ) ;
	For( i , 1 , m )
		scanf( A[i] ) , scanf( B[i] ) , scanf( C[i] ) , scanf( D[i] ) ;
}

bool operator < ( par x , par y ) { return x.first < y.first ; }
bool operator > ( par x , par y ) { return x.first > y.first ; }

int dis[maxn];
bool V[maxn];

void dijkstra(){
	
	For( i , 1 , m )
		Ins( B[i] , A[i] , C[i] , D[i] );
	
	memset( dis , 0x3f , sizeof(int) * ( n + 1 ) );
	
	static priority_queue< par , vector< par > , greater< par > >que;
	que.push( make_pair( dis[n] = 0 , n ) );
	
	while( !que.empty() ){
		int x = que.top().second;que.pop();
		if( V[x] )continue;
		V[x] = true;
		Rep( i , Ht[x] , Nt[i] ){
			int y = To[i];
			if( dis[y] > dis[x] + Dt[i] && !V[y] ){
				dis[y] = dis[x] + Dt[i] ;
				que.push( make_pair( dis[y] , y ) );
			}
		}
	}
}

class node{
	
	public :
		int x;
		int F;
		int G;
		int H;
		int cost;
		
		node(){ x = F = G = H = 0 ; }
		node( int a , int b , int c ){ x = a ; G = b ; cost = c ; H = dis[x] ; F = G + H ; }
		
		bool operator > ( node t ) const { return F > t.F ; }
	
};

int Astar(){
	if( dis[1] == Inf )return -1;
	
	Ct = 0;
	memset( Ht , 0 , sizeof(int) * ( n + 1 ) );
	
	For( i , 1 , m )
		Ins( A[i] , B[i] , C[i] , D[i] ) ;
	
	static priority_queue< node , vector< node > , greater< node > >que;
	
	que.push( (node){ 1 , 0 , 0 } );
	
	while( !que.empty() ){
		node p = que.top();que.pop();
		if( p.x == n )return p.G;
		Rep( i , Ht[p.x] , Nt[i] )
			if( Tk[i] + p.cost <= K )
				que.push( (node){ To[i] , Dt[i] + p.G , Tk[i] + p.cost } );
	}
	
	return -1;
}

int main(){
	
	read_in();
	
	dijkstra();
	
	printf("%d\n" , Astar() );
	
	return 0;
}
