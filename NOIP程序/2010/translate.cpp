#include<cstdio>
#include<cstring>
int b[101];
int main()
{

	freopen( "translate.in" , "r" , stdin ) ;
	freopen( "translate.out" , "w" , stdout ) ;
	
	memset(b,-1,sizeof(b));
	int m,n,a,sum=0,k=1,j;
	scanf("%d %d",&m,&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		for(j=1;j<=m;j++)
		{
			if(b[j]==a)
			break;
		}
		if(j>m)
		{
			sum++;
			b[k]=a;
			k++;
			if(k>m)
			k=1;
		}
}
	printf("%d",sum);
	return 0;
}
