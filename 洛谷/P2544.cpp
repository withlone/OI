#include<cstdio>
#include<cstring>
#include<cmath>

typedef long long LL;

LL x,y,MOD;
LL A[2],B[2],S[2][2],C[2][2];

void Mul(){
	memcpy(C,S,sizeof C);memset(S,0,sizeof S);
	for(int i=0;i<2;i++)for(int j=0;j<2;j++)
	for(int k=0;k<2;k++)(S[i][j] += C[i][k]*C[k][j]%MOD)%=MOD;
}

void Work(LL n){
	S[0][1]=S[1][1]=S[1][0]=1;
	
	for(--n;n;n>>=1,Mul())
		if(n&1){
			B[0] = ( A[0]*S[0][0]%MOD + A[1]*S[0][1]%MOD )%MOD;
			B[1] = ( A[0]*S[1][0]%MOD + A[1]*S[1][1]%MOD )%MOD;
			memcpy(A,B,sizeof A);
		}
}

int main(){
	
	scanf("%lld%lld%lld",&x,&y,&MOD);
	
	A[0]=((LL)(x*(1+sqrt(5)))/2+x-1)%MOD;
	A[1]=((A[0]*2-x+1)%MOD+MOD)%MOD;
	Work(y);
	
	printf("%lld\n",A[0]);
	return 0;
}
