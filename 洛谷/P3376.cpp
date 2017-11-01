#include<cstring>
#include<cstdio>
#include<queue>

using std :: queue;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )
#define Rep( i , _Begin , _Add ) for( int i=(_Begin);i; i = (_Add) )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In=0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e4 +1;
static const int MAXM = 1e5 +1;

int n , m , s , t;
int H[MAXN] , Nt[MAXM<<1] , To[MAXM<<1] , Dt[MAXM<<1] , Sam[MAXM<<1] , Ct;

int Pre[MAXN] , Cap[MAXM<<1];
bool Vis[MAXN];

bool Bfs();
void Ek();
void Init();
void Ins( int , int , int );

int main(){
	
	Init();
	
	Ek();
	
	return 0;
}

void Ins( int F , int T , int D ){
	Nt[++Ct] = H[F];H[F] = Ct;To[Ct] = T;Dt[Ct] = D;
	Nt[++Ct] = H[T];H[T] = Ct;To[Ct] = F;Dt[Ct] = 0;
	Sam[Ct-1] = Ct;Sam[Ct] = Ct-1;Cap[Ct-1] = Cap[Ct] = D;
}

void Init(){
	Read( n );Read( m );Read( s );Read( t );
	For( i , 1 , m ){
		int x , y , z;
		Read( x );Read( y );Read( z );
		Ins( x , y , z );
	}
}

bool Bfs(){
	queue< int >Que;
	memset( Vis , 0 , n+1 );
	Que.push( s );Vis[s] = true;
	while( !Que.empty() ){
		int x = Que.front();Que.pop();
		Rep( i , H[x] , Nt[i] ){
			int y = To[i];
			if( Vis[y] || Dt[i] <= 0 )continue;
			Pre[y] = i;
			Vis[y] = true;
			Que.push( y );
			if( y == t )return true;
		}
	}
	return false;
}
void Ek(){
	int Maxflow = 0;
	while( Bfs() ){
		int x = t , tmp = 0x7fffffff;
		while( x != s ){
			tmp = min( tmp , Dt[Pre[x]] );
			x = To[Sam[Pre[x]]];
		}
		x = t;
		while( x != s ){
			Dt[Pre[x]] -= tmp;
			Dt[Sam[Pre[x]]] += tmp;
			x = To[Sam[Pre[x]]];
		}
		Maxflow += tmp;
	}
	printf("%d\n",Maxflow);
}
