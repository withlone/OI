#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int MAXN = 16;
const int INF  = 2e7;

int n,m,Ct,Tt,Begin;
char Map[MAXN][MAXN];

struct Node{
	int x,y;
}Data[MAXN];
Node Open( int A,int B ){
	Node New;New.x = A;New.y = B;
	return New;
}

int Mx[]={0,1,0,-1};
int My[]={1,0,-1,0};
int Dis[MAXN][MAXN][MAXN][MAXN];
void Bfs( Node A ){
	queue< Node > Que;
	Que.push( A );Dis[A.x][A.y][A.x][A.y]=0;
	while( !Que.empty() ){
		Node u = Que.front();Que.pop();
		for( int i=0;i<4;i++ ){
			int x = u.x + Mx[i],y = u.y + My[i];
			if( x<1||x>n||y<1||y>m||Dis[A.x][A.y][x][y]!=INF||Map[x][y]=='D' )continue;
			Que.push( Open(x,y) );
			Dis[A.x][A.y][x][y] = Dis[A.x][A.y][u.x][u.y] +1;
		}
	}
}

int f[MAXN][1<<MAXN];
bool Check( int Tp ){
	int Res = -1;
	memset( f,-1,sizeof f );
	f[1][1] = Tp;
	for( int St=0;St<(1<<Ct);St++ )
		for( int j=1;j<=Ct;j++ ){
			if( -1==f[j][St]||!( (1<<j-1)&St ) )continue;
			if( (St&Tt)==Tt )Res = max( Res,f[j][St] );
			for( int i=1;i<=Ct;i++ ){
				if( i==j||(1<<i-1)&St )continue;
				int Tmp = Dis[Data[j].x][Data[j].y][Data[i].x][Data[i].y];
				if( Tmp==INF )continue;
				Tmp = f[j][St] - Tmp;
				if( Tmp<0 )continue;
				int New = St|(1<<i-1);
				f[i][New] = max( f[i][New],Tmp );
				if( Map[Data[i].x][Data[i].y]=='G' )f[i][New] = Tp;
			}
		}
	return Res>=0;
}

void DiD( int l,int r ){
	while( l<r ){
		int Mid = l+r >>1;
		if( Check( Mid ) ) r = Mid;
		else l = Mid+1;
	}
	printf("%d\n",Check(l)?l:r);
}

int main(){
	
	while( ~scanf("%d%d",&n,&m),n+m ){
		Ct = 1;Tt = 1;
		for( int i=1;i<=n;i++ )for( int j=0;j<=m;j++ ){
			Map[i][j] = getchar();
			if( Map[i][j]=='F' )Data[1].x=i,Data[1].y=j;
			if( Map[i][j]=='Y' )Tt |= 1<<Ct;
			if( Map[i][j]=='Y'||Map[i][j]=='G' )Data[++Ct].x=i,Data[Ct].y=j;
		}
		for( int i=0;i<MAXN;i++ )for( int j=0;j<MAXN;j++ )for( int I=0;I<MAXN;I++ )for( int J=0;J<MAXN;J++ )Dis[i][j][I][J] = INF;
		for( int i=1;i<=Ct;i++ )Bfs( Data[i] );
		if( !Check(1000) )printf("-1\n");
		else DiD( 0,1000 );
	}
	return 0;
}
