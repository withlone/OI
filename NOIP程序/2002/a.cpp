#include<cstdio>
int card[101];
int main()
{
	
	freopen( "a.in" , "r" , stdin ) ;
	freopen( "a.out" , "w" , stdout ) ;
	
	int n;
	int tot=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&card[i]);
		tot+=card[i];
	}
	tot/=n;
	int t=0;
	for(int i=1;i<=n;i++)
	{
		if(card[i]<tot&&i!=n)
		{
			card[i+1]=card[i+1]-(tot-card[i]);
			card[i]=tot;
			t++;
		}
		if(card[i]>tot)
		{
			card[i+1]=card[i+1]+card[i]-tot;
			card[i]=tot;
			t++;
		}
	}
	printf("%d",t);
	return 0;
}
