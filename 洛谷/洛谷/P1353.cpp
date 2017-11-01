#include<cstdio>
#include<algorithm>
using namespace std;

static const int MAXN = 1e4 +1;

int n,m,Ans;
int A[MAXN],f[MAXN][501];

int main(){
	
	scanf("%d%d",&n,&m);
	for( int i=1;i<=n;i++ )scanf("%d",&A[i]);
	for( int i=1;i<=n;i++ ){
		f[i][0] = max( f[i-1][0],f[i][0] );
		for( int j=1;j<=m;j++ ){
			f[i][j] = f[i-1][j-1] + A[i];
			if( n-i>=j )f[i+j][0] = max( f[i+j][0],f[i][j] );
		}
	}
	printf("%d\n",f[n][0]);
	return 0;
}
