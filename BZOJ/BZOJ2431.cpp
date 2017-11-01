#include<cstdio>
#include<algorithm>
using namespace std;

static const int MAXN = 1e3 +1;
static const int Mod  = 1e4;

int n,k;
int f[MAXN][MAXN],Sum[MAXN][MAXN];

int main(){
	
	scanf("%d%d",&n,&k);
	for( int i=1;i<=n;i++ )f[i][0] = 1,Sum[i][0] = 1;
	for( int i=1;i<=n;i++ )
		for( int j=1;j<=k;j++ ){
			f[i][j] = ( Sum[i-1][j] - (j-i<0?0:Sum[i-1][j-i])+Mod )%Mod;
			Sum[i][j] = ( Sum[i][j-1] + f[i][j] )%Mod;
		}
	printf("%d\n",f[n][k]);
	return 0;
}
