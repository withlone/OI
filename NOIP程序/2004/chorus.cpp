#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;
int h[101];
int f[101];
int g[101];
int main()
{
	
	freopen( "chorus.in" , "r" , stdin ) ;
	freopen( "chorus.out" , "w" , stdout ) ;
	
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]);
	for(int i=1;i<=n;i++)
		f[i]=g[i]=1;
	for(int i=1;i<=n;i++)
	{
		int MAX=0;
		for(int j=1;j<i;j++)
			if(h[j]<h[i])
				MAX=max(MAX,f[j]);
		f[i]+=MAX;
	}
	for(int i=n;i>=1;i--)
	{
		int MAX=0;
		for(int j=i+1;j<=n;j++)
			if(h[j]<h[i])
				MAX=max(MAX,g[j]);
		g[i]+=MAX;
	}
	int ans=INT_MAX;
	for(int i=1;i<=n;i++)
		ans=min(ans,n-g[i]-f[i]+1);
	printf("%d",ans);
	return 0;
}
