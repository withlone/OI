#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int MAXN = 101;

int n,m,Sx,Sy;
char Map[MAXN][MAXN];
bool Vis[MAXN][MAXN];
int Mx[] = {0,1,0,-1};
int My[] = {1,0,-1,0};

struct Node{
	int x,y;
};

void Bfs(){
	int Ans = 1;
	queue< Node > Que;
	Node New;New.x = Sx;New.y = Sy;Vis[Sx][Sy] = true;
	Que.push( New );
	while( !Que.empty() ){
		Node A = Que.front();Que.pop();
		for( int i=0;i<4;i++ ){
			int x = A.x + Mx[i],y = A.y + My[i];
			if( !x||!y||x>n||y>m||Map[x][y]=='#'||Vis[x][y] )continue;
			Ans++;
			Vis[x][y] = true;
			New.x = x;New.y = y;
			Que.push( New );
		}
	}
	printf("%d\n",Ans);
}

int main(){
	
	while( ~scanf("%d%d",&m,&n) ){
		if( !( m+n ) )return 0;
		memset( Vis,0,sizeof Vis );
		memset( Map,'#',sizeof Map );
		for( int i=1;i<=n;i++ )for( int j=0;j<=m;j++ ){
			Map[i][j] = getchar();
			if( Map[i][j]=='@' )Sx = i,Sy = j;
		}
		Bfs();
	}
}
