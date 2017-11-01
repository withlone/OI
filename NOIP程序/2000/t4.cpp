#include<cstdio>
#define fr(i) for(int i=1;i<=n;i++)
int n;int m[11][11];
int f[11][11][11][11];
int max(int a,int b,int c,int d)
{
	int MAX=0;
	if(a>MAX)MAX=a;
	if(b>MAX)MAX=b;
	if(c>MAX)MAX=c;
	if(d>MAX)MAX=d;
	return MAX;
}
int main()
{
	
	freopen( "t4.in" , "r" , stdin ) ;
	freopen( "t4.out" , "w" , stdout ) ;
	
	scanf("%d",&n);
	int a,b,c;
	do
	{
		scanf("%d%d%d",&a,&b,&c);
		m[a][b]=c;
	}while(a+b+c>0);
	fr(i)
		fr(j)
			fr(k)
				fr(l)
				{
					f[i][j][k][l]=max(f[i-1][j][k-1][l],
										f[i][j-1][k][l-1],
										f[i-1][j][k][l-1],
										f[i][j-1][k-1][l])+m[i][j];
					if(i!=k||j!=l)	f[i][j][k][l]+=m[k][l];
				}
	printf("%d",f[n][n][n][n]);
	return 0;
}
