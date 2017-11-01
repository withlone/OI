#include<cstdio>
int a[10]={6,2,5,5,4,5,6,3,7,6};
int d[10];
int cl(int x)
{
	int k=0,sum1=0;
	if(x==0)
	return 6;
	while(x>0)
	{
		d[k]=x%10;
		x/=10;
		k++;
	}
	for(int i=0;i<k;i++)
	{
		sum1+=a[d[i]];
	}
	return sum1;
}
int main()
{

	freopen( "matches.in" , "r" , stdin ) ;
	freopen( "matches.out" , "w" , stdout ) ;
	
	int n,sum=0,k;
	scanf("%d",&n);
	int i=0,j=0;
	while(i<=1111)
	{
		while(j<=1111&&j<=i)
		{
			k=i-j;
			if(n-4==cl(i)+cl(k)+cl(j))
			{
				sum++;
			}
			j++;
		}
		i++;
		j=0;
	}
	printf("%d",sum);
	return 0;
} 
