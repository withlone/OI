#include<cstdio>

const int MOD = 1e9+7;
const int MAXN = 1e5+1;
typedef long long LL;
LL Mul(LL A,int B){
	LL T=1;
	for(;B;B>>=1,A=A*A%MOD)
		if(B&1)T=T*A%MOD;
	return T;
}

int N,A,X;LL Ans=1;
int main(){

	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	
	scanf("%d",&N);
	
	for(int i=1;i<=N;i++){
		scanf("%d%d",&A,&X);
		if(A==1)printf("%lld\n",(Ans*=X)%=MOD);
		else printf("%lld\n",(Ans*=Mul(X,MOD-2))%=MOD);
	}
	return 0;
}
