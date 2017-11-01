#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 3e3 +1;

int n,m,u,w,Ct,Num;
int f[MAXN][MAXN];
int Nt[MAXN],H[MAXN],To[MAXN],Dis[MAXN],Size[MAXN];

void Ins( int F,int T,int D ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
	Dis[Ct] = D;
}

void Get( int p ){
	if( p>=n-m+1 )Size[p] = 1,f[p][0]=0;
	for( int i=H[p];i;i=Nt[i] ){
		Get( To[i] );
		Size[p] += Size[To[i]];
	}
}

void Dfs( int p ){
	for( int i=H[p];i;i=Nt[i] ){
		Dfs( To[i] );
		for( int j=Size[p];j;j-- )
			for( int k=0;k<=min( j,Size[To[i]] );k++ )
				f[p][j] = max( f[p][j],f[To[i]][k] + f[p][j-k] - Dis[i] );
	}
}

int main(){
	
	memset( f,-10,sizeof f );
	for( int i=0;i<MAXN;i++ )f[i][0] = 0;
	scanf("%d%d",&n,&m);
	for( int i=1;i<=n-m;i++ ){
		scanf("%d",&Num);
		while( Num-- )scanf("%d%d",&u,&w),Ins( i,u,w );
	}
	for( int i=n-m+1;i<=n;i++ )scanf("%d",&f[i][1]);
	Get( 1 );
	Dfs( 1 );
	for( int i=m;i;i-- )
		if( f[1][i]>=0 ){
			printf("%d\n",i);
			return 0;
		}
}
