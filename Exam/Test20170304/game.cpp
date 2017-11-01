#include<cstdio>

const int MOD  = 1e9+7;
const int MAXN = 3e6+1;
typedef long long LL;

int N,S;
int p[MAXN];

int Calc(LL P){
	int Ans=0;
	for(LL T=P;P<=N;P*=T)
		Ans+=N/P;
	return Ans;
}

bool V[MAXN];
void Make(){
	for(int i=2;i<=N;i++){
		if(!V[i])p[++S]=i;
		for(int j=1;j<=S&&p[j]*i<=N;j++){
			V[p[j]*i]=true;
			if(!(i%p[j]))break;
		}
	}
}

LL Mul(LL A,LL B){
	LL T=1;
	for(;B;B>>=1,A=(A*A)%MOD)
		if(B&1)T=(T*A)%MOD;
	return T;
}

int main(){
	
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d",&N);
	Make();
	
	LL Ans=1;
	for(int i=1;i<=S;i++){
		int K=Calc(p[i]);
		if(K&1)K--;
		Ans=(Ans*Mul(p[i],K))%MOD;
	}
	
	printf("%lld\n",Ans);
	
	return 0;
}
