#include<cstdio>
#include<algorithm>
using namespace std;
int a[351];int b[5];
int f[41][41][41][41];
int main()
{
	
	freopen( "tortoise.in" , "r" , stdin ) ;
	freopen( "tortoise.out" , "w" , stdout ) ;
	
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		int x;
		scanf("%d",&x);
		b[x]++;
	}
	for(int i=0;i<=b[1];i++)
		for(int j=0;j<=b[2];j++)
			for(int k=0;k<=b[3];k++)
				for(int l=0;l<=b[4];l++)
				{
					if(i)f[i][j][k][l]=max(f[i][j][k][l],f[i-1][j][k][l]);
					if(j)f[i][j][k][l]=max(f[i][j][k][l],f[i][j-1][k][l]);
					if(k)f[i][j][k][l]=max(f[i][j][k][l],f[i][j][k-1][l]);
					if(l)f[i][j][k][l]=max(f[i][j][k][l],f[i][j][k][l-1]);
					f[i][j][k][l]+=a[1+i+2*j+3*k+4*l];
				}
	printf("%d",f[b[1]][b[2]][b[3]][b[4]]);
	return 0;
}
