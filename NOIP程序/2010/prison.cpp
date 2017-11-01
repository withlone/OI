#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 20000*2+1;
const int MAXM = 100001;

struct Node{
	int u,v;
	long long Grievance;
	bool operator < (Node a) const {return Grievance>a.Grievance;}
}node[MAXM];

int Father[MAXN],n,m;

int Find(int t)
{
	if(t!=Father[t]) return Father[t]=Find(Father[t]);
	return t;
}

int main()
{
	
	freopen( "prison.in" , "r" , stdin ) ;
	freopen( "prison.out" , "w" , stdout ) ;
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=2*n;i++)
		Father[i]=i;
	for(int i=1;i<=m;i++)
		scanf("%d%d%lld",&node[i].u,&node[i].v,&node[i].Grievance);
	sort(1+node,1+m+node);
	for(int i=1,u,v;i<=m;i++)
	{
		u=Find(node[i].u);
		v=Find(node[i].v);
		if(u==v)
		{
			printf("%lld",node[i].Grievance);
			return 0;
		}
		Father[u]=Find(node[i].v+n);
		Father[v]=Find(node[i].u+n);
	}
	printf("0");
	return 0;
}
