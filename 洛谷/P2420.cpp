#include<cstdio>

const int MAXN = 100001;
const int MAX = 17;

int n,m;
bool Vis[MAXN];

struct EDGE{
	int Next,To,Dis;
}Edge[MAXN<<1];
int Head[MAXN<<1],Size;

int Father[MAXN][MAX+1],Dis[MAXN][MAX+1],Deep[MAXN];
void Dfs(int u){
	for(int i=Head[u];i;i=Edge[i].Next){
		int v=Edge[i].To;
		if(Vis[v])continue;Vis[v]=1;
		Father[v][0]=u;Dis[v][0]=Edge[i].Dis;Deep[v]=Deep[u]+1;
		Dfs(v);
	}
}

void Ins(int From,int To,int dis){
	Edge[++Size].Next=Head[From];
	Head[From]=Size;
	Edge[Size].To=To;
	Edge[Size].Dis=dis;
}

int Lca(int u,int v){
	if(Deep[u]<Deep[v]) u^=v^=u^=v;
	int D_Value=Deep[u]-Deep[v],Ans=0;
	for(int i=MAX;i>=0;i--)
		if(D_Value&(1<<i)){
			if(!Ans) Ans=Dis[u][i];
			else Ans^=Dis[u][i];
			u=Father[u][i];
		}
	if(u==v) return Ans;
	for(int i=MAX;i>=0;i--)
		if(Father[u][i]!=Father[v][i]){
			Ans^=Dis[u][i]^Dis[v][i];
			u=Father[u][i];v=Father[v][i];
		}
	return Ans^Dis[u][0]^Dis[v][0];
}

int main(){
	scanf("%d",&n);
	for(int i=1,u,v,dis;i<n;i++){
		scanf("%d%d%d",&u,&v,&dis);
		Ins(v,u,dis);Ins(u,v,dis);
	}
	
	Vis[1]=1;
	Dfs(1);
	for(int j=1;j<=MAX;j++)
		for(int i=1;i<=n;i++){
			Father[i][j]=Father[Father[i][j-1]][j-1];
			Dis[i][j]=Dis[i][j-1]^Dis[Father[i][j-1]][j-1];
		}
	
	scanf("%d",&m);
	while(m--){
		int u,v;
		scanf("%d%d",&u,&v);
		printf("%d\n",Lca(u,v));
	}
	
	return 0;
}
