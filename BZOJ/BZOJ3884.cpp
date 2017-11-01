#include<cstdio>

typedef long long LL;

LL Phi(int A){
	LL Ans=A;
	for(int i=2;i*i<=A;i++)
		if(!(A%i))
			for(Ans=Ans/i*(i-1);!(A%i);A/=i);
	return A==1?Ans:Ans/A*(A-1);
}

LL Pow(LL A,int B,int Mod){
	LL T=1;
	for(;B;B>>=1,A=A*A%Mod)
		if(B&1)T=T*A%Mod;
	return T;
}

LL F(int Mod){
	if( Mod==1 ) return 0;
	LL Phi_Mod = Phi(Mod);
	return Pow( 2,F(Phi_Mod)+Phi_Mod ,Mod );
}

int main(){
	
	int T,In;
	scanf("%d",&T);
	
	while( T-- ){
		scanf("%d",&In);
		printf("%lld\n",F(In));
	}
	return 0;
}
