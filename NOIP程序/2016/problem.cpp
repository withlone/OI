#include<cstdio>
#define MAXN 2001
int c[MAXN][MAXN];
int f[MAXN][MAXN];
int main()
{
	freopen("problem.in","r",stdin);
	freopen("problem.out","w",stdout);
	int t,k;
	scanf("%d%d",&t,&k);
	for(int i=0;i<MAXN;i++) c[0][i]=1;
	for(int i=1;i<MAXN;i++)
		for(int j=1;j<MAXN;j++)
			c[i][j]=(c[i][j-1]+c[i-1][j-1])%k;
	for(int i=1;i<MAXN;i++)
	{
		for(int j=1;j<i;j++)
		{
			f[j][i]=f[j-1][i]+f[j][i-1]-f[j-1][i-1];
			if(!c[j][i]) f[j][i]++;
		}
		f[i][i]=f[i-1][i];
		if(!c[i][i])f[i][i]++;
	}
	for(int i=1;i<=t;i++)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		if(m>n) m=n;
		printf("%d\n",f[m][n]);
	}
	return 0;
}
