#include<cstdio>

const int MAXN = 1e6+1;
typedef long long LL;

int n;

int main(){
	
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	
	while(~scanf("%d",&n)){
		LL Ans=0;
		for(int i=1;i*i<=n;i++)if(!(n%i)){
			Ans+=i;
			if(i*i!=n)Ans+=n/i;
		}
		if(n&1)Ans+=2;
		printf("%lld\n",Ans);
	}
	
	return 0;
}
