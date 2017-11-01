#include<cstdio>
#include<cstring>

#define For(i) for(int i=0;i<2;i++)
typedef unsigned long long ULL;
const ULL MOD = 7528443412579576937ULL;

ULL b,d,n;

ULL Mul(ULL A,ULL B){
	ULL T=0;
	for(;B;B>>=1,A=(A+A)%MOD)
		if(B&1)
			T = (T+A)%MOD;
	return T;
}

struct MATRIX{
	ULL s[2][2];
	MATRIX (){memset(s,0,sizeof s);}
	MATRIX operator *(MATRIX T){
		MATRIX C;
		For(i)For(j)For(k)C.s[i][j]=(C.s[i][j]+Mul(T.s[i][k],s[k][j]))%MOD;
		return C;
	}
	MATRIX operator *=(MATRIX T){*this=*this*T;return *this;}
	MATRIX operator ^(ULL N){
		MATRIX C,D;C=D=*this;
		for(--N;N;N>>=1,D*=D)
			if(N&1)
				C*=D;
		return C;
	}
}A,C;

int main(){
	
	scanf("%llu%llu%llu",&b,&d,&n);ULL T=n;if(!n){printf("1\n");return 0;}
	C.s[0][1]=1;C.s[1][1]=b;C.s[1][0]=(d-b*b)/4;
	A.s[0][0]=2;A.s[1][0]=b;
	
	A*=(C^n);
	
	printf("%llu\n",A.s[0][0]-(b*b!=d&&!(T&1)));
	
	return 0;
}
