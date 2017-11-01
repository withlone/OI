#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 3e4 +1;

int n;
int A[MAXN],B[MAXN],f[MAXN][4];

void Do( int *A ){
	memset( f,30,sizeof f );
	f[0][1] = f[0][2] = f[0][3] = 0;
	for( int i=1;i<=n;i++ )
		for( int j=1;j<=3;j++ )
			for( int k=1;k<=j;k++ )
				f[i][j] = min( f[i][j],f[i-1][k] + (A[i]==j&&k<=j?0:1) );
}

int main(){
	
	scanf("%d",&n);
	for( int i=1;i<=n;i++ )scanf("%d",&A[i]),B[n-i+1] = A[i];
	int Ans = 0x7fffffff;
	Do( A );
	for( int i=1;i<=3;i++ )Ans = min( Ans,f[n][i] );
	Do( B );
	for( int i=1;i<=3;i++ )Ans = min( Ans,f[n][i] );
	printf("%d\n",Ans);
	return 0;
}
