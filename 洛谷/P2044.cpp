#include<cstdio>
#include<cstring>

typedef long long LL;

LL m,n,MOD;
LL A[2],B[2],S[2][2];

LL Mul(LL X,LL Y){
	LL T=X;X=0;
	for(;Y;Y>>=1,T=(T+T)%MOD)
		if(Y&1)
			X=(X+T)%MOD;
	return X;
}

void Pow(){
	LL C[2][2];
	memcpy(C,S,sizeof C);memset(S,0,sizeof S);
	for(int i=0;i<2;i++)for(int j=0;j<2;j++)
	for(int k=0;k<2;k++)S[i][j]=(S[i][j]+Mul(C[i][k],C[k][j]))%MOD;
}

int main(){
	
	S[0][0]=S[1][0]=1;
	scanf("%lld%lld%lld%lld%lld%lld",&MOD,&S[1][1],&A[0],&A[1],&n,&m);
	S[1][1]%=MOD;A[0]%=MOD;A[1]%=MOD;
	
	for(;n;n>>=1,Pow())
		if(n&1){
			B[0] = ( Mul(A[0],S[0][0]) + Mul(A[1],S[0][1]) )%MOD;
			B[1] = ( Mul(A[0],S[1][0]) + Mul(A[1],S[1][1]) )%MOD;
			memcpy(A,B,sizeof A);
		}
	
	printf("%lld\n",A[1]%m);
	
	return 0;
}
