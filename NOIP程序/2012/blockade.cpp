#include<cstdio>
#include<cstring>
#include<climits>
#include<algorithm>
using namespace std;

const int MAXN = 50001;
const int MAX = 16;

int n,m;
int Army[MAXN];

struct EDGE{
	int Next,To,Dis;
}Edge[MAXN<<1];
int Size,Head[MAXN<<1];
void Ins(int From,int To,int Dis){
	Edge[++Size].Next=Head[From];
	Head[From]=Size;
	Edge[Size].To=To;
	Edge[Size].Dis=Dis;
} 

bool Vis[MAXN];int Father[MAXN][MAX+1],Dis[MAXN][MAX+1],Deep[MAXN];
void Dfs(int u){
	for(int i=Head[u];i;i=Edge[i].Next){
		int v=Edge[i].To;
		if(Vis[v]) continue;Vis[v]=1;
		Father[v][0]=u;Dis[v][0]=Edge[i].Dis;Deep[v]=Deep[u]+1;
		Dfs(v);
	}
}

struct Point{
	int Dis,p;
	bool operator < (Point Tmp) const {return Dis<Tmp.Dis;}
}Remain[MAXN],NotVis[MAXN];
int Rsize,Nsize;bool Have[MAXN];

void Updata(int u){
	bool p=1,q=0;
	for(int i=Head[u];i;i=Edge[i].Next){
		int v=Edge[i].To;
		if(Deep[v]<Deep[u]) continue;
		Updata(v);
		p=p&Have[v];
		q=1;
	}
	Have[u]=Have[u]|(p&q&&u!=1);
}

bool Check(int Time){
	memset(Have,0,sizeof Have);
	Rsize=Nsize=0;
	for(int i=1;i<=m;i++){
		int u=Army[i],Now_Time=0,Son=Army[i];
		for(int j=MAX;j>=0;j--)
			if(Father[u][j]&&Now_Time+Dis[u][j]<=Time){
				Now_Time+=Dis[u][j];u=Father[u][j];
			}
		if(u!=1) Have[u]=1;
		else{
			for(int j=MAX;j>=0;j--)if(Father[Son][j]>1)Son=Father[Son][j];
			Remain[++Rsize].p=Son;
			Remain[Rsize].Dis=Time-Now_Time;
		}
	}
	sort(1+Remain,1+Rsize+Remain);
	Updata(1);
	for(int i=Head[1];i;i=Edge[i].Next)
		if(!Have[Edge[i].To]) NotVis[++Nsize].p=Edge[i].To,NotVis[Nsize].Dis=Edge[i].Dis;
	sort(1+NotVis,1+Nsize+NotVis);
	
	int Pos=1;
	for(int i=1;i<=Rsize;i++){
		if(!Have[Remain[i].p]) Have[Remain[i].p]=1;
		else if(Remain[i].Dis>=NotVis[Pos].Dis) Have[NotVis[Pos].p]=1;
		while(Have[NotVis[Pos].p]&&Pos<=Nsize) Pos++;
	}
	return Pos==Nsize+1;
}

void Divide(){
	int l=0,r=INT_MAX;
	while(l<r-1){
		int Mid=(l+r)>>1;
		if(Check(Mid)) r=Mid;
		else l=Mid;
	}
	if(Check(l)) printf("%d\n",l);
	else printf("%d\n",r);
}

int main(){
	
	freopen( "blockade.in" , "r" , stdin ) ;
	freopen( "blockade.out" , "w" , stdout ) ;
	
	scanf("%d",&n);
	int Tmp=0;
	for(int i=1,u,v,Read;i<n;i++){
		scanf("%d%d%d",&u,&v,&Read);
		Ins(u,v,Read);Ins(v,u,Read);
		if(u==1||v==1) Tmp++;
	}
	
	Vis[1]=1;Dfs(1);
	for(int j=1;j<=MAX;j++)for(int i=1;i<=n;i++){
		Father[i][j]=Father[Father[i][j-1]][j-1];
		Dis[i][j]=Dis[i][j-1]+Dis[Father[i][j-1]][j-1];
	}
	
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d",&Army[i]);
	if(m<Tmp){printf("-1\n");return 0;}
	
	Divide();
	
	return 0;
}
