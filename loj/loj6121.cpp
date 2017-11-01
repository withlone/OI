#include<queue>
#include<cstdio>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 10 + 1;
static const int maxk = 150 + 1;

int n;
int m;
int p;
int k;
int s;
int S;
int T;

int x1[maxk];
int x2[maxk];
int y1[maxk];
int y2[maxk];
int g[maxk];
int x_[maxk];
int y_[maxk];
int q[maxk];

void read_in(){
	scanf( n ) ; scanf( m ) ; scanf( p ) ; scanf( k ) ;
	For( i , 1 , k )
		scanf( x1[i] ) , scanf( y1[i] ) , scanf( x2[i] ) , scanf( y2[i] ) , scanf( g[i] ) ;
	scanf( s ) ;
	For( i , 1 , s )
		scanf( x_[i] ) , scanf( y_[i] ) , scanf( q[i] ) ;
}

int dr[maxn][maxn][maxn][maxn];
int ky[maxn][maxn];

void preparation(){
	For( i , 1 , k ){
		int &dr1 = dr[ x1[i] ][ y1[i] ][ x2[i] ][ y2[i] ] ,
			&dr2 = dr[ x2[i] ][ y2[i] ][ x1[i] ][ y1[i] ] ;
		if( dr1 == -1 )continue;
		if( !g[i] )dr1 = dr2 = -1;
		else dr1 = dr2 = ( dr1 | ( 1 << g[i] - 1 ) );
	}
	For( i , 1 , s )
		ky[ x_[i] ][ y_[i] ] |= 1 << q[i] - 1;
}

struct status{
	int x;
	int y;
	int stt;
	int dis;
	status(){ x = y = stt = dis = 0 ; }
	status( int a , int b , int c , int d ){ x = a ; y = b ; stt = c ; dis = d ; }
};

queue < status > que;

int mx[] = { 1 , 0 , -1 , 0 };
int my[] = { 0 , 1 , 0 , -1 };

bool Vis[1 << 10][maxn][maxn];

int bfs(){
	que.push( status( 1 , 1 , 0 , 0 ) );
	Vis[0][1][1] = true;
	while( !que.empty() ){
		status now = que.front();que.pop();
		For( i , 0 , 3 ){
			int x = now.x + mx[i] , y = now.y + my[i] , t = dr[now.x][now.y][x][y];
			if( x >= 1 && x <= n && y >= 1 && y <= m && 
				t != -1 && !( ( now.stt ^ t ) & t ) ){
				status nxt = status( x , y , now.stt | ky[x][y] , now.dis + 1 );
				if( x == n && y == m )return nxt.dis;
				if( Vis[nxt.stt][x][y] )continue;
				Vis[nxt.stt][x][y] = true;
				que.push( nxt );
			}
		}
	}
	return -1;
}

int main(){
	
	read_in();
	
	preparation();
	
	printf("%d\n" , bfs() );
	
	return 0;
}
