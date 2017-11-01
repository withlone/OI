#include<cstdio>
#include<cstring>

const int MAXN = 100;
const int MOD  = 2009;

int n,T,N;
char s[MAXN];

struct MATRIX{
	int s[MAXN][MAXN];
	MATRIX(){memset(s,0,sizeof s);}
	MATRIX operator *(MATRIX A){
		MATRIX C;
		for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)for(int k=1;k<=N;k++)
			C.s[i][j]=(C.s[i][j]+s[i][k]*A.s[k][j]%MOD)%MOD;
		return C;
	}
	MATRIX operator *=(MATRIX A){*this=*this*A;return *this;}
	MATRIX operator ^(int A){
		MATRIX C,D=*this;for(int i=1;i<=N;i++)C.s[i][i]=1;
		for(;A;A>>=1,D*=D)
			if(A&1)C*=D;
		return C;
	}
}G;

int main(){
	
	scanf("%d%d",&n,&T);
	N=10*(n-1)+9;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=8;j++)
			G.s[10*(i-1)+j][10*(i-1)+j+1]=1;
	
	for(int i=1;i<=n;i++)
		for(int j=1,In;j<=n;j++){
			scanf("%1d",&In);
			if(In)G.s[10*(i-1)+In][10*(j-1)+1]=1;
		}
	
	printf("%d\n",(G^T).s[1][10*(n-1)+1]);
	
	return 0;
}
