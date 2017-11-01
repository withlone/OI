#include<cstdio>

template <typename Type> inline void Read(Type &in){
	in=0;Type f=1;char ch=getchar();
	for(;ch <'0'||ch>'9' ;ch=getchar()) if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())in=in*10+ch-'0';in*=f;
}

const int MAXN = 10000005;
typedef long long LL;

int T,MOD,s,Mn;
bool V[MAXN];
int n[MAXN],m[MAXN],p[MAXN],Fac[MAXN],Inv[MAXN],Ans[MAXN];

inline void Make_Prime(){
	for(int i=2;i<=Mn;i++){
		if(!V[i]) p[++s]=i;
		for(int j=1; j<=s && p[j]*i<=Mn ;j++){
			V[p[j]*i] = true;
			if(!(i%p[j]))break;
		}
	}
}

inline void Init(){
	Make_Prime();
	Fac[1]=Inv[1]=Ans[1]=1;
	for(int i=2;i<=Mn;i++)
		Fac[i]=(LL)Fac[i-1]*i%MOD;
	
	for(int i=2; i<=Mn && i!=MOD ;i++)
		Inv[i]=(MOD-(LL)MOD/i%MOD*Inv[MOD%i]%MOD);
	
	for(int i=2;i<=Mn;i++)
		if(!V[i])	Ans[i]=(((1LL*Ans[i-1]*(i-1))%MOD)*Inv[i%MOD]%MOD);
		else Ans[i]=Ans[i-1];
}

int main(){
	
	Read( T );Read( MOD );
	for(int i=1;i<=T;i++) Read( n[i] ),Mn=Mn>n[i]?Mn:n[i],Read( m[i] );
	Init();
	
	for(int i=1;i<=T;i++)
		printf("%lld\n",(1LL*Ans[m[i]])%MOD*(1LL*Fac[n[i]])%MOD);
	
	return 0;
}
