#include<cstdio>

static const int MAXN = 1e3 +2;
static const int Mod  = 10007;
#define abs(t) t>=0?t:-t

int A,B,k,n,m;
int C[MAXN][MAXN];

void Init(){
	C[0][0] = 1;
	for( int i=1;i<=k+1;i++ )
		for( int j=1;j<=k+1;j++ )
			C[i][j] = (C[i-1][j] + C[i-1][j-1])%Mod;
}
int Pow( int x,int y ){
	int Res = 1;
	for( ;y;y>>=1,x = x*x%Mod )
		if( y&1 )Res = Res*x %Mod;
	return Res;
}

int main(){
	
	scanf("%d%d%d%d%d",&A,&B,&k,&n,&m);
	A %= Mod;B %= Mod;
	Init();
	printf("%d\n",((Pow(A,n)%Mod*Pow(B,m)%Mod)%Mod*C[k+1][abs(k-n+1)]+Mod)%Mod);
	return 0;
}
