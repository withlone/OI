#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

template <typename Type> inline void Read(Type &in){
	Type f=1;char ch=getchar();in=0;
	for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())in=in*10+ch-'0';
}

const int MAXN = 3*1e5+1;
const int MAX = 20;

int n,m;
int Pre[MAXN];

int Head[MAXN<<1],Size;
struct EDGE{
	int Next,To,Dis,Number;
}Edge[MAXN<<1];

void Ins(int Number,int From,int To,int Dis){
	Edge[++Size].Next=Head[From];
	Head[From]=Size;
	Edge[Size].To=To;
	Edge[Size].Dis=Dis;
	Edge[Size].Number=Number;
}

int Root;
int Father[MAXN][MAX+1],Dis[MAXN][MAX+1],Deep[MAXN];
bool Vis[MAXN];

void Dfs(int u){
	for(int i=Head[u];i;i=Edge[i].Next){
		int v=Edge[i].To;
		if(Vis[v])continue;Vis[v]=1;Pre[Edge[i].Number]=v;
		Father[v][0]=u;Dis[v][0]=Edge[i].Dis;Deep[v]=Deep[u]+1;
		Dfs(v);
	}
}

int LCA(int &Change,int u,int v){
	if(Deep[u]<Deep[v])swap(u,v);
	int D_Value=Deep[u]-Deep[v];
	for(int i=0;i<=MAX;i++)
		if(D_Value&(1<<i)){
			Change+=Dis[u][i];
			u=Father[u][i];
		}
	if(u==v) return u;
	for(int i=MAX;i>=0;i--)
		if(Father[u][i]!=Father[v][i]){
			Change+=Dis[u][i]+Dis[v][i];
			u=Father[u][i];v=Father[v][i];
		}
	Change+=Dis[u][0]+Dis[v][0];
	return Father[u][0];
}

struct Node{
	int u,v,Dis,Lca;
	bool operator < (Node Tmp) const{return Dis>Tmp.Dis;}
}Data[MAXN];

int Upper(int Tmp){
	int l=1,r=n;
	while(l<r-1){
		int Mid=(l+r)>>1;
		if(Data[Mid].Dis>Tmp) l=Mid;
		else r=Mid;
	}return Data[r].Dis>Tmp?r:l;
}

int Num[MAXN];
void Updata(int u){
	for(int i=Head[u];i;i=Edge[i].Next){
		int v=Edge[i].To;
		if(Deep[v]<Deep[u])continue;
		Updata(v);
		Num[u]+=Num[v];
	}
}

bool Check(int Time){
	memset(Num,0,sizeof Num);
	int End=Upper(Time),Best=Data[1].Dis-Time;
	if(Best<=0) return true;
	for(int i=1;i<=End;i++){
		Num[Data[i].u]++;Num[Data[i].v]++;
		Num[Data[i].Lca]-=2;
	}
	
	Updata(Root);
	
	for(int i=1;i<2*n;i++)
		if(Num[Pre[Edge[i].Number]]==End&&Edge[i].Dis>=Best)
			return true;
	return false;
}

void Binary(){
	int l=0,r=3*1e8+1;
	while(l<r-1){
		int Mid=(l+r)>>1;
		if(Check(Mid)) r=Mid;
		else l=Mid;
	}
	printf("%d\n",Check(l)?l:r);
}

int main(){
	Read(n);Read(m);
	
	for(int i=1,u,v,dis;i<n;i++){
		Read(u);Read(v);Read(dis);
		Ins(i,u,v,dis);Ins(i,v,u,dis);
	}
	
	Vis[Root=1]=1;
	Dfs(Root);
	for(int j=1;j<=MAX;j++)
		for(int i=1;i<=n;i++){
			Father[i][j]=Father[Father[i][j-1]][j-1];
			Dis[i][j]=Dis[i][j-1]+Dis[Father[i][j-1]][j-1];
		}
	
	for(int i=1;i<=m;i++){
		Read(Data[i].u);Read(Data[i].v);
		Data[i].Lca=LCA(Data[i].Dis,Data[i].u,Data[i].v);
	}
	sort(1+Data,1+m+Data);
	
	Binary();
	
	return 0;
}
