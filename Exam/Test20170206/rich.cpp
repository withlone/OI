#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

const int MAXN = 1001;
const int MAXK = 1e5+1;

int n,m;long long Ans=LLONG_MAX;long long Tmp=LLONG_MAX;
int k[MAXN][MAXN],x[MAXN][MAXN],y[MAXN][MAXN];
long long Sum_y[MAXN],Sum_x[MAXN];

int main(){
	freopen("rich.in","r",stdin);
	freopen("rich.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&k[i][j]);
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			Sum_x[j]+=k[i][j];
			Sum_y[n-i+1]+=k[i][j];
		}
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			x[i][j]=j*4-2;
			y[i][j]=(n-i+1)*4-2;
	}
	
	for(int i=0;i<=m*4;i+=4){
		long long Tot=0;
		for(int j=1;j<=m;j++)Tot+=Sum_x[j]*(i-x[j][j])*(i-x[j][j]);
		Tmp=min(Tmp,Tot);
	}
	
	for(int i=0;i<=n*4;i+=4){
		long long Tot=0;
		for(int j=1;j<=n;j++)Tot+=Sum_y[j]*(i-y[j][j])*(i-y[j][j]);
		Ans=min(Ans,Tot);
	}
	
	printf("%lld\n",Ans+=Tmp);
	
	return 0;
}
