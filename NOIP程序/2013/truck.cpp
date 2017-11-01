#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 10001;
const int MAXM = 50001;
const int MAX = 15;

struct DATA{
	int u,v,Dis;
	bool operator < (DATA Tmp) const {return Tmp.Dis<Dis;}
}Data[MAXM];
int Father[MAXM];
int Find(int t){
	return t==Father[t]?t:Father[t]=Find(Father[t]);
}

struct EDGE{
	int Next,To,Dis;
}Edge[MAXN<<1|1];
int Head[MAXN<<1|1],Size;
void Ins(int From,int To,int Dis){
	Edge[++Size].Next=Head[From];
	Head[From]=Size;
	Edge[Size].To=To;
	Edge[Size].Dis=Dis;
}

int n,m,q;
int Indgr[MAXN];

int Deep[MAXN],f[MAXN][MAX+1],Dis[MAXN][MAX+1];bool Vis[MAXN];
void Dfs(int u){
	for(int i=Head[u];i;i=Edge[i].Next){
		int v=Edge[i].To;
		if(Vis[v]) continue;Vis[v]=1;
		Dis[v][0]=Edge[i].Dis;
		Deep[v]=Deep[u]+1;f[v][0]=u;
		Dfs(v);
	}
}

void Make_Tree(){
	for(int i=1;i<=m;i++) Father[i]=i;
	sort(1+Data,1+m+Data);
	
	for(int i=1;i<=m;i++){
		int u=Find(Data[i].u),v=Find(Data[i].v);
		if(u!=v){
			Father[u]=v;Indgr[Data[i].u]++;Indgr[Data[i].v]++;
			Ins(Data[i].u,Data[i].v,Data[i].Dis);
			Ins(Data[i].v,Data[i].u,Data[i].Dis);
		}
	}
	
	for(int i=1;i<=n;i++)
		if(Indgr[i]<=2&&!Vis[i]){
			Vis[i]=1;
			Dfs(i);
		}
	for(int j=1;j<=MAX;j++)
	for(int i=1;i<=n;i++)
		if(f[i][j-1]!=0){
			f[i][j]=f[f[i][j-1]][j-1];
			Dis[i][j]=min(Dis[i][j-1],Dis[f[i][j-1]][j-1]);
		}
}

int LCA(int u,int v){
	if(Deep[u]<Deep[v]) swap(u,v);
	int D_Value=Deep[u]-Deep[v],Ans=Data[1].Dis;
	for(int i=0;i<=MAX;i++)
		if(D_Value&(1<<i))
			{Ans=min(Ans,Dis[u][i]);u=f[u][i];}
	if(u==v) return Ans;
	for(int i=MAX;i>=0;i--)
		if(f[u][i]!=f[v][i]){
			Ans=min(min(Dis[u][i],Dis[v][i]),Ans);
			u=f[u][i];v=f[v][i];
		}
	return min(Ans,min(Dis[u][0],Dis[v][0]));
}

template <typename Type> inline void Read(Type &in){
	Type f=1;char ch=getchar();in=0;
	for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())in=in*10+ch-'0';in*=f;
}

int main(){
	
	freopen( "truck.in" , "r" , stdin ) ;
	freopen( "truck.out" , "w" , stdout ) ;
	
	Read(n);Read(m);
	for(int i=1;i<=m;i++){
		Read(Data[i].u);Read(Data[i].v);Read(Data[i].Dis);
	}
	Make_Tree();
	
	Read(q);
	for(int i=1,u,v;i<=q;i++){
		Read(u);Read(v);
		printf("%d\n",Find(u)!=Find(v)?-1:LCA(u,v));
	}
	
	return 0;
}
