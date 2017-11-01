#include<cstdio>
typedef long long LL;
int na[11][11];LL f[11][11];
int exp(int t)
{
	LL a=1LL;
	for(int i=2;i<=t;i++)
		a*=10;
	return a;
}
int max(int a,int b)
{
	return a>b?a:b;
}
int main()
{
	
	freopen( "t2.in" , "r" , stdin ) ;
	freopen( "t2.out" , "w" , stdout ) ;
	
	int n,k;LL num;
	scanf("%d%d%lld",&n,&k,&num);
	for(int i=1;i<=n;i++)
	{
		na[n-i+1][n-i+1]=num%10;
		num/=10;
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
				na[i][j]=na[i][j-1]*10+na[j][j];
	for(int i=1;i<=n;i++)
			f[i][0]=na[1][i];
	for(int K=1;K<=k;K++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=i;j++)
				f[i][K]=max(f[i][K],f[j][K-1]*na[j+1][i]);
	printf("%lld",f[n][k]);
	return 0;
}
