#include<cstdio>

typedef long long LL;
const int MAXN = 1e6+1;

int n;LL Ans;

int main(){

	freopen("divisor.in","r",stdin);
	freopen("divisor.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++)Ans+=n/i;
	
	printf("%lld\n",Ans);
	return 0;
}
