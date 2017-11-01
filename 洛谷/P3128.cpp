#include<cstdio>

template <typename Type> inline Type max(Type T1,Type T2){return T1>T2?T1:T2;}
template <typename Type> inline void Read(Type &in){
	in=0;Type f=1;char ch=getchar();
	for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())in=in*10+ch-'0';in*=f;
}

const int MAXN = 50000 +1;
const int MAXM = 100000+1;
const int MAX  = 16;

int n,m,Ans,Root;
int N[MAXN],T[MAXN];

struct EDGE{
	int Nxt,To;
}E[MAXN<<1];
int s,H[MAXN<<1];

void Ins(int From,int To){
	E[++s].Nxt=H[From];
	H[From]=s;
	E[s].To=To;
}

bool V[MAXN];int F[MAXN][MAX+1],D[MAXN];
void Dfs(int u){
	for(int i=H[u];i;i=E[i].Nxt){
		if(V[E[i].To])continue;V[E[i].To]=1;
		F[E[i].To][0]=u;D[E[i].To]=D[u]+1;
		Dfs( E[i].To );
	}
}

int LCA(int u,int v){
	if(D[v]>D[u]) u^=v^=u^=v;
	int Df=D[u]-D[v];
	for(int i=MAX;i>=0;i--)if(Df&(1<<i))
			u=F[u][i];
	if(u==v) return u;
	for(int i=MAX;i>=0;i--)if(F[u][i]!=F[v][i])
		u=F[u][i],v=F[v][i];
	return F[u][0];
}

void UD(int u){
	for(int i=H[u];i;i=E[i].Nxt){
		if(D[E[i].To]<D[u])continue;
		UD( E[i].To );
		N[u] += N[E[i].To];
	}
}

int main(){
	
	Read( n );Read( m );
	
	for(int i=1,u,v;i<n;i++){
		Read( u );Read( v );
		Ins( u , v );Ins( v , u );
	}
	
	V[Root = 1]=1;
	Dfs( Root );
	
	for(int j=1;j<=MAX;j++)
		for(int i=1;i<=n;i++)
			F[i][j]=F[F[i][j-1]][j-1];
	
	for(int i=1,u,v;i<=m;i++){
		Read( u );Read( v );
		int Lca=LCA( u , v );
		N[u]++;N[v]++;N[Lca]-=2;T[Lca]++;
	}
	
	UD( Root );
	
	for(int i=1;i<=n;i++) N[i] += T[i],Ans=max(Ans,N[i]);
	
	printf("%d\n",Ans);
	
	return 0;
}
