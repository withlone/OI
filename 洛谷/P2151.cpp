#include<cstdio>
#include<cstring>

const int MAXN = 21;
const int MAXM = 61;
const int MOD  = 45989;

int n,m,T,A,B,Ans;

struct EDGE{
	int Next,To,Same;
}E[MAXM<<1];
int H[MAXM<<1],S;
void Ins(int From,int To){
	E[++S].Next=H[From];
	H[From]=S;
	E[S].To=To;
}

struct MATRIX{
	int s[MAXM<<1][MAXM<<1];
	MATRIX(){memset(s,0,sizeof s);}
	MATRIX operator *(MATRIX A){
		MATRIX C;
		for(int i=1;i<=S;i++)for(int j=1;j<=S;j++)for(int k=1;k<=S;k++)
			C.s[i][j]=(C.s[i][j]+s[i][k]*A.s[k][j]%MOD)%MOD;
		return C;
	}
	MATRIX operator *=(MATRIX A){*this=*this*A;return *this;}
	MATRIX operator ^ (int N){
		MATRIX C,D=*this;for(int i=1;i<=S;i++)C.s[i][i]=1;
		for(;N;N>>=1,D*=D)if(N&1)
			C*=D;
		return C;
	}
}G,F;

int main(){
	
	scanf("%d%d%d%d%d",&n,&m,&T,&A,&B);
	
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		Ins(u,v);E[S].Same=S+1;
		Ins(v,u);E[S].Same=S-1;
	}
	for(int i=H[A];i;i=E[i].Next) F.s[1][i]++;
	
	for(int i=1;i<=S;i++)
		for(int j=H[E[i].To];j;j=E[j].Next)
			if(j!=E[i].Same) G.s[i][j]++;
	F=F*(G^(T-1));
	
	for(int i=1;i<=S;i++)if(E[i].To==B)
		(Ans+=F.s[1][i])%=MOD;
	
	printf("%d\n",Ans);
	return 0;
}
