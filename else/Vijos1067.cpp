#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MOD  = 7777777;
const int MAXN = 10;
typedef long long LL;

int n,m;
struct MATRIX{
	LL s[MAXN][MAXN];
	MATRIX(){memset(s,0,sizeof s);}
	MATRIX operator * (MATRIX A){
		MATRIX C;
		for(int i=0;i<m;i++)for(int j=0;j<m;j++)for(int k=0;k<m;k++)
			C.s[i][j]=(C.s[i][j]+s[i][k]*A.s[k][j]%MOD)%MOD;
		return C;
	}
	MATRIX operator *=(MATRIX A){
		*this=*this*A;
		return *this;
	}
	MATRIX operator ^ (int A){
		MATRIX C,D=*this;for(int i=0;i<m;i++)C.s[i][i]=1;
		for(;A;A>>=1,D*=D)if(A&1)C*=D;
		return C;
	}
}T,F;

int main(){
	
	scanf("%d%d",&m,&n);
	
	for(int i=0;i<m-1;i++)T.s[i+1][i]=1;
	for(int i=0;i<m  ;i++)T.s[i][m-1]=1;
	F.s[0][0]=1;
	for(int i=1;i<=m;i++)for(int j=i-1;j>=max(0,i-m);j--)F.s[0][i]+=F.s[0][j];
	
	printf("%lld\n",(F*(T^(n))).s[0][0]);
	return 0;
}
