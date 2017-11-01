#include<cstdio>
#include<cstdlib>

const int MAXN = 13;

int n,Sum,s;
int f[MAXN][MAXN],Ans[MAXN];

void Init(){
	f[1][1] = 1;
	for( int i=2;i<=n;i++ )
		for( int j=1;j<=i;j++ )
			f[i][j] = f[i-1][j] + f[i-1][j-1];
}

bool Vis[MAXN];
void Dfs( int Dep ){
	if( Dep==n+1 ){
		if( s!=Sum )return;
		for( int i=1;i<=n;i++ )printf("%d ",Ans[i]);
		exit(0);
	}
	for( int i=1;i<=n;i++ )
		if( !Vis[i]&&s+f[n][Dep]*i<=Sum ){
			Vis[i] = 1;
			s += f[n][Dep]*i;
			Ans[Dep] = i;
			Dfs( Dep+1 );
			s -= f[n][Dep]*i;
			Vis[i] = 0;
		}
}

int main(){
	
	scanf("%d%d",&n,&Sum);
	Init();
	Dfs( 1 );
	return 0;
}
