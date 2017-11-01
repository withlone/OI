#include<cstdio>

template <typename Type> inline void Read(Type &in){
	in=0;Type f=1;char ch=getchar();
	for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())in=in*10+ch-'0';in=in*f;
}

const int MAXN = 300000 +1;
const int MAX  = 19;

int n;
int A[MAXN],Num[MAXN],T[MAXN];

struct E{
	int Nxt,To;
}E[MAXN<<1];
int s,H[MAXN];

void Ins(int From,int To){
	E[++s].Nxt=H[From];
	H[From]=s;
	E[s].To=To;
}

bool V[MAXN];
int F[MAXN][MAX+1],D[MAXN];
void Dfs(int u){
	for(int i=H[u];i;i=E[i].Nxt){
		if(V[E[i].To])continue;V[E[i].To]=true;
		D[E[i].To]=D[u]+1;F[E[i].To][0]=u;
		Dfs( E[i].To );
	}
}

int LCA(int u,int v){
	if(D[u]<D[v]) u^=v^=u^=v;
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
		Num[u] += Num[E[i].To];
	}
}

int main(){
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	for(int i=2;i<=n;i++) T[A[i]]=-1;
	
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		Ins(u,v);Ins(v,u);
	}
	
	V[1] = true;
	Dfs( 1 );
	
	for(int j=1;j<=MAX;j++)for(int i=1;i<=n;i++)F[i][j]=F[F[i][j-1]][j-1];
	
	for(int i=1;i<n;i++){
		int Lca=LCA( A[i] , A[i+1] );
		Num[A[i]]++;Num[A[i+1]]++;Num[Lca]-=2;T[Lca]++;
	}
	
	UD( 1 );
	
	for(int i=1;i<=n;i++) Num[i] += T[i],printf("%d\n",Num[i]);
	
	return 0;
}
