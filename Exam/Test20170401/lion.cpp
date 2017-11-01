#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 1e4 +1;

int n,m;
int A[MAXN],B[MAXN],f[MAXN];

int main(){
	
	freopen("lion.in","r",stdin);
	freopen("lion.out","w",stdout);
	scanf("%d%d",&n,&m);
	for( int i=1;i<=n;i++ )scanf("%d%d",&A[i],&B[i]);
	for( int i=1;i<=n;i++ )
		for( int j=A[i];j<=m;j++ )
			f[j] = max( f[j],f[j-A[i]] + B[i] );
	printf("%d\n",f[m]);
	return 0;
}
