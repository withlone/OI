#include<cstdio>

const int MAXN = 1000000<<1|1;
typedef long long LL;

int n,Mod,s;LL Ans=1;
int p[MAXN],Fac[MAXN],Sum[MAXN];
bool V[MAXN]={1,1};

void Make(){
	for(int i=2;i<=(n<<1);i++){
		if(!V[i]){
			p[++s]=i;
			Fac[i]=i;
		}
		for(int j=1;j<=s&&p[j]*i<=(n<<1);j++){
			V[p[j]*i]=true;
			Fac[p[j]*i]=i;
			if(!(i%p[j]))break;
		}
	}
}

LL Pow(LL A,int B){
	LL T=1;
	for(;B;B>>=1,A=A*A%Mod)
		if(B&1)T=T*A%Mod;
	return T;
}

int main(){
	
	scanf("%d%d",&n,&Mod);
	Make();
	
	for(int i=2;i<=n;i++)Sum[i]=-1;
	for(int i=n+2;i<=(n<<1);i++)Sum[i]=1;
	for(int i=(n<<1);i>=2;i--)
		if(Fac[i]<i){
			Sum[Fac[i]]+=Sum[i];
			Sum[i/Fac[i]]+=Sum[i];
		}
		else Ans=Ans*Pow(i,Sum[i])%Mod;
	
	printf("%lld\n",Ans);
	return 0;
}
