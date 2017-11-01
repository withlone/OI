#include<cstdio>
#include<algorithm>
using namespace std;
int Map[51][51];
int f[51][51][51][51];
int main()
{
	
	freopen( "message.in" , "r" , stdin ) ;
	freopen( "message.out" , "w" , stdout ) ;
	
	int m,n;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&Map[i][j]);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=m;k++)
				for(int l=1;l<=n;l++)
				{
					f[i][j][k][l]=max(f[i][j][k][l],max(f[i-1][j][k-1][l],max(f[i][j-1][k][l-1],max(f[i-1][j][k][l-1],f[i][j-1][k-1][l]))))+Map[i][j];
					if(i!=k||j!=l) f[i][j][k][l]+=Map[k][l];
				}
	printf("%d",f[m][n][m][n]);
	return 0;
}
