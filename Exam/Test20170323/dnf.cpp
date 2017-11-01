#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int Mod  = 1e9 +7;
const int MAXN = 1e3 +3;

int n,k,m;
int Top[MAXN],F[MAXN][MAXN];

int main(){
	
	freopen("dnf.in","r",stdin);
	freopen("dnf.out","w",stdout);
	scanf("%d%d%d",&n,&k,&m);
	for( int i=1;i<=k;i++ )scanf("%d",&Top[i]);
	for( int i=k+1;i<=n;i++ )Top[i] = m;
	F[0][0] = 1;
	
	for( int i=1;i<=n;i++ )for( int j=0;j<=m;j++ )
		F[i][j] = ( 0/*F[i][j]*/ + F[i-1][j] + F[i][!j?m+1:-1] + F[i][j<m-Top[i]?0:m+1] - F[i][j-Top[i]>0?] ) %Mod;
	
	printf("%d\n",F[n][m]%Mod);
	return 0;
}
