#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 1000
int h[MAXN];int f[MAXN][MAXN];
int n;int MAX;
int main()
{
	
	freopen( "energy.in" , "r" , stdin ) ;
	freopen( "energy.out" , "w" , stdout ) ;
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]),h[i+n]=h[i];
	for(int i=2*n-1;i>=1;i--)
		for(int j=i+1;j<2*n&&j-i<n;j++)
			for(int k=i;k<j;k++)
			{
				f[i][j]=max(f[i][j],f[i][k]+f[k+1][j]+h[i]*h[j+1]*h[k+1]);
				MAX=max(MAX,f[i][j]);
			}
	printf("%d",MAX);
	return 0;
}
