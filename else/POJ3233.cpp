#include<cstdio>
#include<cstring>

const int MAXN = 30;

int n,k,MOD;

struct MATRIX{
	int s[MAXN][MAXN];
	MATRIX(){memset(s,0,sizeof s);}
	MATRIX operator + (MATRIX A){
		MATRIX C;
		for(int i=0;i<n;i++)for(int j=0;j<n;j++)
			C.s[i][j]=(s[i][j]+A.s[i][j])%MOD;
		return C;
	}
	MATRIX operator +=(MATRIX A){
		*this=*this+A;
		return *this;
	}
	MATRIX operator * (MATRIX A){
		MATRIX C;
		for(int i=0;i<n;i++)for(int j=0;j<n;j++)for(int k=0;k<n;k++)
			C.s[i][j]=(C.s[i][j]+s[i][k]*A.s[k][j]%MOD)%MOD;
		return C;
	}
	MATRIX operator *=(MATRIX A){
		*this=*this*A;
		return *this;
	}
	MATRIX operator ^ (int N){
		MATRIX C,D=*this;for(int i=0;i<n;i++)C.s[i][i]=1;
		for(;N;N>>=1,D*=D)
			if(N&1)C*=D;
		return C;
	}
	void print(){
		for(int i=0;i<n;i++,printf("\n"))
		for(int j=0;j<n;j++)printf("%d ",s[i][j]);
	}
}A,S;

void Solve(int i){
	if(i<=1)return;
	Solve(i/2);
	MATRIX B=S^(i>>1),C=B*S;
	if(i&1) A=C*A+A+C;
	else A=B*A+A;
}

int main(){
	
	scanf("%d%d%d",&n,&k,&MOD);
	
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)scanf("%d",&A.s[i][j]),S.s[i][j]=A.s[i][j];
	Solve(k);
	A.print();
	return 0;
}
