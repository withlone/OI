#include<cstdio>

const int MAXN = 100001;
typedef long long LL;

int n;LL f[MAXN],Ans;

int main(){
	scanf("%d",&n);
	
	for(int i=n;i>=1;i--){
		f[i]=(1LL*n/i)*(1LL*n/i);
		for(int j=i+i;j<=n;j+=i)f[i]-=f[j];
		Ans+=f[i]*i;
	}
	
	printf("%lld\n",Ans);
	
	return 0;
}
