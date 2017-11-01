#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int MAXN = 302;

int n,m,Sx,Sy,Ex,Ey;
char Map[MAXN][MAXN];
int Tp[26][5];
int Mx[] = {0,1,0,-1};
int My[] = {1,0,-1,0};
int g[MAXN][MAXN][3];
bool Vis[MAXN][MAXN];
struct Node{
	int x,y,Dis;
};
queue<Node> Que;

void Bfs(){
	Node New;New.x = Sx;New.y = Sy;New.Dis = 0;
	Vis[Sx][Sy] = true;
	Que.push( New );
	while( !Que.empty() ){
		Node A = Que.front();Que.pop();
		for( int i=0;i<4;i++ ){
			int x = A.x + Mx[i],y = A.y + My[i];
			if( Vis[x][y]||x<1||y<1||x>n||y>m )continue;
			if( Map[x][y]=='=' ){printf("%d\n",A.Dis+1);return;}
			New.x = x;New.y = y;New.Dis = A.Dis+1;
			if( Map[x][y]>='A'&&Map[x][y]<='Z' ){
				if( x==Tp[Map[x][y]-'A'][1]&&y==Tp[Map[x][y]-'A'][2] )
					{New.x = Tp[Map[x][y]-'A'][3];New.y = Tp[Map[x][y]-'A'][4];}
				else{New.x = Tp[Map[x][y]-'A'][1];New.y = Tp[Map[x][y]-'A'][2];}
			}
			Vis[x][y] = true;
			Que.push( New );
		}
	}
}

int main(){
	
	scanf("%d%d",&n,&m);
	for( int i=1;i<=n;i++ )for( int j=0;j<=m;j++ ){
		Map[i][j] = getchar();
		if( Map[i][j]=='@' ) Sx = i,Sy = j;
		if( Map[i][j]=='=' ) Ex = i,Ey = j;
		if( Map[i][j]>='A'&&Map[i][j]<='Z' ){
		Tp[Map[i][j]-'A'][++Tp[Map[i][j]-'A'][0]] = i;
		Tp[Map[i][j]-'A'][++Tp[Map[i][j]-'A'][0]] = j;
		}
		if( Map[i][j]=='#' ) Vis[i][j] = true;
	}
	Bfs();
	return 0;
}
