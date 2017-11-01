#include<cstdio>
#include<cstring>

typedef long long LL;
#define For(i) for(int i=0;i<3;i++)

LL n,MOD;

LL Mul(LL A,LL B){
	LL T=0;
	for(;B;B>>=1,A=(A+A)%MOD)
		if(B&1)
			T=(T+A)%MOD;
	return T;
}

struct MATRIX{
	LL s[3][3];
	MATRIX(){memset(s,0,sizeof s);}
	MATRIX operator *(MATRIX T){
		MATRIX C;
		For(i)For(j)For(k)
			C.s[i][j] = (C.s[i][j]+Mul(T.s[i][k],s[k][j])%MOD)%MOD;
		return C;
	}
	MATRIX operator *=(MATRIX T){*this=*this*T;return *this;}
	MATRIX operator ^(LL N){
		MATRIX A,B;A=B=*this;
		for(--N;N;N>>=1,B*=B)
			if(N&1)A*=B;
		return A;
	}
}F;

int main(){
	
	scanf("%lld%lld",&n,&MOD);
	
	F.s[2][0]=1;
	
	for(LL i=10;;i*=10){
		MATRIX C;C.s[0][0]=i;
		C.s[0][1]=C.s[0][2]=C.s[1][1]=C.s[1][2]=C.s[2][2]=1;
		if(i>n){
			F=F*(C^(n-i/10+1));break;
		}F=F*(C^(i-i/10));
	}
	
	printf("%lld\n",F.s[0][0]);
	
	return 0;
}
