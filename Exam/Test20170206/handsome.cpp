#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 1001;
const int MAXM = 100001;
const int MAX2 = 20;

int n,m,Size,Tot;
int Head[MAXN*2],Father[MAXN][MAX2+1],Deep[MAXN],Dis[MAXN][MAXN],Indgr[MAXN];
bool Vis[MAXN];

struct Node{
	int Next,To,Dis;
}Edge[MAXN*2];

void Ins(int From,int To,int Dis){
	Edge[++Size].Next=Head[From];
	Head[From]=Size;
	Edge[Size].To=To;
	Edge[Size].Dis=Dis;
}

void Dfs(int t){
	for(int i=1;i<=MAX2;i++)
		if(Father[t][i-1])
			Father[t][i]=Father[Father[t][i-1]][i-1];
	for(int i=Head[t];i;i=Edge[i].Next){
		int v=Edge[i].To;
		if(Father[t][0]==v||Vis[v]) continue;Vis[v]=1;
		Father[v][0]=t;
		Deep[v]=Deep[t]+1;
		Dfs(v);
	}
}

int Lca(int u,int v){
	if(Deep[u]<Deep[v]) swap(u,v);
	int Delta=Deep[u]-Deep[v];
	for(int i=0;(1<<i)<=Delta;i++)
		if((1<<i)&Delta)
			u=Father[u][i];
	if(u==v) return u;
	for(int i=MAX2;i;i--)
		if(Father[u][i]!=Father[v][i]){
			u=Father[u][i];v=Father[v][i];
		}
	return Father[u][0];
}

void Find_Dis(int u,int Start,int End){
	if(Dis[u][End]||u==End){
		Tot+=Dis[u][End];
		Dis[Start][End]=Dis[End][Start]=Tot;
		return;
	}
	for(int i=Head[u];i;i=Edge[i].Next){
		int To=Edge[i].To;
		if(Deep[To]>Deep[u])continue;
		Tot+=Dis[u][To];
		Dis[Start][To]=Dis[To][Start]=Tot;
		Find_Dis(To,Start,End);
		Dis[To][End]=Dis[End][To]=Tot-Dis[Start][To];
		break;
	}
}

int Read(){
	int in=0,f=1;
	char ch=getchar();
	for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar()) in=in*10+ch-'0';
	return in*f;
}

int main(){
	freopen("handsome.in","r",stdin);
	freopen("handsome.out","w",stdout);
	
	n=Read();m=Read();
	
	for(int i=1;i<n;i++){
		int u,v,t;
		u=Read();v=Read();t=Read();
		Ins(u,v,t);Ins(v,u,t);
		Dis[u][v]=Dis[v][u]=t;
		Indgr[u]++;Indgr[v]++;
	}
	int Root=0;
	for(int i=1;i<=n;i++)
		if(Indgr[i]==2){
			Root=i;
			break;
		}
	
	Vis[Root]=1;
	Dfs(Root);
	
	for(int i=1;i<=m;i++){
		int u,v;
		u=Read();v=Read();
		int lca=Lca(u,v);
		Tot=0;Find_Dis(u,u,lca);
		Tot=0;Find_Dis(v,v,lca);
		printf("%d\n",Dis[u][lca]+Dis[v][lca]);
	}
	
	return 0;
}
