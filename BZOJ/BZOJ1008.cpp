#include<cstdio>

typedef long long LL;
const int Mod = 100003;

LL n,m;

LL Pow( LL A,LL B ){
	LL T = 1;
	for( ;B;B>>=1,(A*=A) %=Mod )
		if( B&1 ) (T*=A) %=Mod;
	return T;
}

int main(){
	
	scanf("%lld%lld",&m,&n);
	
	printf("%lld\n",(Pow( m,n )-m*Pow( m-1,n-1 )%Mod+Mod)%Mod);
	return 0;
}
