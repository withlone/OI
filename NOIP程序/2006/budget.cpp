#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 61
int v[MAXN];int p[MAXN];int q[MAXN];int w[MAXN];
int sub[MAXN][3];
int f[32000+1];
int main()
{
	
	freopen( "budget.in" , "r" , stdin ) ;
	freopen( "budget.out" , "w" , stdout ) ;
	
	int n,m;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&v[i],&p[i],&q[i]);
		w[i]=v[i]*p[i];
		if(q[i])
			sub[q[i]][++sub[q[i]][0]]=i;
	}
	for(int i=1;i<=n;i++)
		for(int j=m;j>=v[i];j--)
		{
			if(q[i]) continue;
			f[j]=max(f[j],f[j-v[i]]+w[i]);
			if(!sub[i][0]) continue;
			int a=sub[i][1],b=sub[i][2];
			if(j>=v[i]+v[a]&&a)	
				f[j]=max(f[j],f[j-v[i]-v[a]]+w[i]+w[a]);
			if(j>=v[i]+v[b]&&b)
				f[j]=max(f[j],f[j-v[i]-v[b]]+w[i]+w[b]);
			if(j>=v[i]+v[a]+v[b]&&b)
				f[j]=max(f[j],f[j-v[i]-v[a]-v[b]]+w[i]+w[a]+w[b]);
		}
	printf("%d",f[m]);
	return 0;
}
