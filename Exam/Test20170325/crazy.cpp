#include<cstdio>
#include<cstring>

#define For(i) for( int i=0;i<4;i++ )
typedef long long LL;
const int MAXN = 1e5 +1;
const int Mod  = 1e9 +7;

LL n;

struct MATRIX{
	LL s[4][4];
	MATRIX(){memset(s,0,sizeof s);}
	MATRIX operator * ( MATRIX A ){
		MATRIX C;
		For(i)For(j)For(k)
			(C.s[i][j]+=s[i][k]*A.s[k][j]%Mod) %=Mod;
		return C;
	}
	MATRIX operator *=( MATRIX A ){
		*this = *this * A;
		return *this;
	}
	MATRIX operator ^ ( LL N ){
		if( N<=0 ) return *this;
		MATRIX C,D=*this;For(i)C.s[i][i] = 1;
		for( ;N;N>>=1,D*=D )
			if( N&1 )C*=D;
		return C;
	}
	MATRIX operator ^=( LL N ){
		*this = *this ^ N;
		return *this;
	}
}Ans,Tmp;

int main(){
	
	freopen("crazy.in","r",stdin);
	freopen("crazy.out","w",stdout);
	scanf("%lld",&n);
	Tmp.s[0][0] = Tmp.s[1][1] = Tmp.s[1][2] = Tmp.s[1][3] = Tmp.s[2][0] = Tmp.s[3][3] = 1;
	Tmp.s[0][1] = Tmp.s[0][3] = 2;
	Tmp.s[2][1] = Tmp.s[2][3] = 3;
	Tmp ^= (n-3);
	Ans.s[0][0] = 1;Ans.s[0][1] = 4;Ans.s[0][2] = 1;Ans.s[0][3] = 6;
	Ans *= Tmp;
	printf("%lld\n",Ans.s[0][3]);
	return 0;
}
