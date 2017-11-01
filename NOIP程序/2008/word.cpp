#include<cstdio>
#include<cmath>
#include<cstring>
char a[101];
int sushu(int x)
{
	int i=2;
	if(x==2)
	return 1;
	if(x==1)
	return 2;
	if(x==0)
	return 2;
	while(i<=sqrt(x)&&x%i!=0)
	i++;
	if(x%i==0)
	return 2;
	else
	return 1;
}
int main()
{
	
	freopen( "word.in" , "r" , stdin ) ;
	freopen( "word.out" , "w" , stdout ) ;
	
	gets(a);
	int l=strlen(a),sum,max=0,min=101;
	for(int i=0;i<l;i++)
	{
		sum=0;
		for(int j=0;j<l;j++)
		{
			if(a[i]==a[j])
			{
				sum++;
			}
		}
		if(sum>max)
		max=sum;
		if(sum<min)
		min=sum;
	}
	if(sushu(max-min)==1)
	{
		printf("Lucky Word");
		printf("\n%d",max-min);
	}
	else 
	{
		printf("No Answer");
		printf("\n0");
	}
	return 0;
}
