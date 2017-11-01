#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef pair< int , int > par;
static const int maxn = 50 + 10;
static const int maxm = 2500 + 10;

int n , S , T , ans;
int obs[maxn] , size;
int sign[maxn][maxn];

int H[maxn] , Nt[maxm] , To[maxm] , Dt[maxm] , Ct;
void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = z;
}

struct heap{
	
	int size;
	par T[maxm];
	
	void clear(){ memset( T , 0 , sizeof T ) ; size = 0 ; }
	
	void push( par x ){
		T[ ++size ] = x;
		int p = size;
		for( ; p != 1 && T[p] < T[p >> 1] ; p >>= 1 )
			swap( T[p] , T[p >> 1] );
	}
	
	par top(){ return T[1] ; }
	
	bool empty(){ return !size; }
	
	void pop(){
		T[1] = T[ size-- ];
		int p = 1;
		while( ( p << 1 ) <= size && T[p] > min( T[p << 1] , T[p << 1 | 1] ) ){
			int t = ( T[p << 1] < T[p << 1 | 1] ? p << 1 : p << 1 | 1 );
			swap( T[p] , T[t] );
			p = t;
		}
	}
	
}Hp;

bool V[maxn] , Vis[maxn];
int dis[maxn] , pre[maxn];
void Dijkstra(){
	Hp.clear();
	For( i , 1 , n )dis[i] = 1e9 , pre[i] = 0;
	dis[S] = 0;
	Hp.push( make_pair( 0 , S ) );
	while( !Hp.empty() ){
		int x = Hp.top().second;Hp.pop();
		if( V[x] )continue;
		V[x] = true;
		Rep( i , H[x] , Nt[i] ){
			int y = To[i];
			if( V[y] || dis[y] < dis[x] + Dt[i] || Vis[i] )continue;
			pre[y] = x;
			dis[y] = dis[x] + Dt[i];
			Hp.push( make_pair( dis[y] , y ) );
		}
	}
}

int path[maxm] , cnt;
int second_min_path(){
	int x = T;
	while( x != S )
		Rep( i , H[x] , Nt[i] ){
			int y = To[i];
			if( pre[x] == y ){ path[ ++cnt ] = sign[y][x] ; x = y ; break ; }
		}
	
	int res = 1e9;
	For( i , 1 , cnt ){
		Vis[ path[i] ] = true;
		For( j , 1 , n )V[j] = false;
		Dijkstra();
		if( dis[T] > ans )res = min( res , dis[T] );
		Vis[ path[i] ] = false;
	}
	return res;
}

int main(){
	
	Read( n );Read( S );Read( T );
	
	For( i , 1 , n )For( j , 1 , n ){
		int x;Read( x );
		if( x )Ins( i , j , x ) , sign[i][j] = Ct;
	}
	
	Read( size );
	For( i , 1 , size )Read( obs[i] ) , V[ obs[i] ] = true;
	
	Dijkstra();
	
	printf("%d",dis[T]);
	
	For( i , 1 , n )V[i] = false;
	Dijkstra();
	printf(" %d",ans = dis[T]);
	
	printf(" %d\n",second_min_path());
	
	return 0;
}
