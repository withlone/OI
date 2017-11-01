#include<cstdio>
#include<cstring>

const int MAXN = 100+1;
const int MAXM = 10 +1;

int n,m,k,In;
struct MATRIX{
	int s[MAXN][MAXN];
	MATRIX(){memset(s,0,sizeof s);}
	MATRIX operator *(MATRIX A){
		MATRIX C;
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)for(int k=1;k<=n;k++)
			C.s[i][j]+=s[i][k]*A.s[k][j];
		return C;
	}
	MATRIX operator *=(MATRIX A){
		*this=*this*A;
		return *this;
	}
	MATRIX operator ^ (int A){
		MATRIX C=*this,D=*this;
		for(--A;A;A>>=1,D*=D)
			if(A&1)C*=D;
		return C;
	}
	MATRIX operator ^=(int A){
		*this=*this^A;
		return *this;
	}
	void print(){for(int i=1;i<=n;i++)printf("%d ",s[i][1]);}
}T[MAXM],A,B;

int main(){
	
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)for(int j=1;j<=n;j++){
		scanf("%d",&In);T[i].s[j][In]=1;
	}
	for(int i=1;i<=n;i++)A.s[i][1]=i;
	B=T[1];
	for(int i=2;i<=m;i++)
		B=T[i]*B;
	B^=k/m;
	for(int i=1;i<=k%m;i++)
		B=T[i]*B;
	
	(B*A).print();
	return 0;
}
