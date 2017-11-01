#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 2e5 +1;
const int MAXM = 1e9 +1;
const int MOD  = 1e9 +7;

int n,m,Ans,Size;
int Length[MAXN];

int main(){
	freopen("tall.in","r",stdin);
	freopen("tall.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&Length[i]);
	
	sort(1+Length,1+n+Length);
	
	int Pos=1;
	long long Ans=1;
	
	for(int i=2;i<=n;i++){
		while(Length[i]>Length[Pos]+m&&Pos<i) Pos++;
		Ans*=i-Pos+1;
		Ans%=MOD;
	}
	
	printf("%lld\n",Ans);
	
	return 0;
}
