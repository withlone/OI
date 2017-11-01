#include<cstdio>
#include<cstring>

const int MAXM = 21;
typedef long long LL;

int n,m,MOD;
int Ul[MAXM],Next[MAXM];

struct MATRIX{
	int s[MAXM][MAXM];
	
	MATRIX(){memset(s,0,sizeof s);}
	
	MATRIX operator *(MATRIX T){
		MATRIX C;
		for(int i=0;i<m;i++)for(int j=0;j<m;j++)for(int k=0;k<m;k++)
			C.s[i][j] =(C.s[i][j]+s[i][k]*T.s[k][j]%MOD)%MOD;
		return C;
	}
	MATRIX operator *=(MATRIX T){*this=*this*T;return *this;}
	MATRIX operator ^(LL N){
		MATRIX C,D=*this;for(int i=0;i<m;i++)C.s[i][i]=1;
		for(;N;N>>=1,D*=D)
			if(N&1)
				C*=D;
		return C;
	}
}A,F;

int main(){
	
	scanf("%d%d%d",&n,&m,&MOD);
	for(int i=0;i< m;i++)scanf("%1d",&Ul[i]);
	for(int i=1,k=0;i<=m;i++){
		while(k&&Ul[i]!=Ul[k])k=Next[k-1];
		if(Ul[i]==Ul[k])++k;
		Next[i]=k;
	}
	for(int i=m;i>=1;i--)Next[i]=Next[i-1],Ul[i]=Ul[i-1];Next[0]=0;
	for(int i=0;i< m;i++)
		for(int j=0;j<=9;j++){
			int k=i;
			while(k&&j!=Ul[k+1]) k=Next[k];
			if(j==Ul[k+1])k++;
			A.s[i][k]++;
		}
	
	F.s[0][0]=1;F=F*(A^n);
	
	int Ans=0;
	for(int i=0;i<m;i++)Ans=(Ans+F.s[0][i]%MOD)%MOD;
	
	printf("%d\n",Ans);
	return 0;
}
