#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 6e3 +100;

int n,L,K,Rot;
int Hap[MAXN],Nt[MAXN],H[MAXN],To[MAXN];
int F[MAXN][2];bool Vis[MAXN];

void Dfs( int T,int Fa ){
	for( int i=H[T];i;i=Nt[i] ){
		Dfs( To[i],T );
		F[T][0] += max( F[To[i]][1],F[To[i]][0] );
		F[T][1] += F[To[i]][0];
	}
}

int main(){
	
	scanf("%d",&n);
	for( int i=1;i<=n;i++ )scanf("%d",&F[i][1]);
	for( int i=1;i< n;i++ ){
		scanf("%d%d",&L,&K);
		Vis[L] = true;
		Nt[i] = H[K];
		H[K] = i;
		To[i] = L;
	}
	for( int i=1;i<=n;i++ )if( !Vis[i] ){Rot=i;break;}
	Dfs( Rot,0 );
	
	printf("%d\n",max( F[Rot][0],F[Rot][1] ));
	
	return 0;
}
