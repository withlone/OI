#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[200001];
int ans[10001];
int main()
{
	
	freopen( "count.in" , "r" , stdin ) ;
	freopen( "count.out" , "w" , stdout ) ;
	
	memset(ans,0,sizeof(ans));
	int n,k=0,l=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	sort(1+a,1+n+a);
	for(int i=1;i<=n;i++)
	{
		int j=i+1;
		if(i==1||a[i]!=a[i-1])
		{
			l++;
			a[l]=a[i];
			k++;
		}
		while(a[i]==a[i+1])
		{
			i++;
			ans[k]++;
		}
	}
	for(int i=1;i<=k;i++)
	{
		printf("%d %d\n",a[i],ans[i]+1);
	}
	return 0;
}
