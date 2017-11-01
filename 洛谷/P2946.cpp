#include<cstdio>

static const int MAXN = 2000 +1;
static const int Mod  = 1e8;

int n,F;
int A[MAXN],f[MAXN][MAXN];

int main(){
	
	scanf("%d%d",&n,&F);
	for( int i=1;i<=n;i++ )scanf("%d",&A[i]);
	f[0][0] = 1;
	for( int i=1;i<=n;i++ )
		for( int j=F;j>=0;j-- )
			f[i][j] = (f[i-1][j] + f[i-1][(j+A[i])%F]) %Mod;
	printf("%d\n",f[n][F]%Mod);
	return 0;
}
