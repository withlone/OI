#include<cstdio>
#include<cstring>
#include<algorithm>
#include<climits>
using namespace std;

const int MAXN = 301;

int n,m,Map[MAXN][MAXN],Dis[MAXN],Ans;
bool Vis[MAXN];

int main() {
	
	memset(Map,0x7f,sizeof Map);
	memset(Dis,0x7f,sizeof Dis);
	
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,dis;i<=m;i++) {
		scanf("%d%d%d",&u,&v,&dis);
		Map[u][v]=Map[v][u]=dis;
	}
	Dis[1]=0;
	for(int i=1;i<=n;i++) {
		int Pos=0;
		for(int j=1;j<=n;j++)
			if(!Vis[j]&&Dis[j]<Dis[Pos])
				Pos=j;
		Vis[Pos]=1;
		Ans=max(Ans,Dis[Pos]);
		for(int j=1;j<=n;j++)
			if(!Vis[j])
				Dis[j]=min(Dis[j],Map[Pos][j]);
	}
	
	printf("%d %d",n-1,Ans);
	
	return 0;
}
