#include<cstdio>
int main()
{
	
	freopen( "save.in" , "r" , stdin ) ;
	freopen( "save.out" , "w" , stdout ) ;
	
	int money,m,tot=0,x=0;
	float t;
	for(int i=1;i<=12;i++)
	{
		scanf("%d",&money);
		m=300-money+x;
		if(m<0)
		{
			printf("-%d",i);
			return 0;
		}
		else
		{
			tot+=m/100*100;
			x=m-m/100*100;
		}
	}
	t=tot*1.2+x;
	printf("%.0f",t);
	return 0;
}
