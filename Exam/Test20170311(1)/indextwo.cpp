#include<cstdio>

typedef long long LL;
LL ExGcd(LL,LL,LL&,LL&);
#include<bits/stdc++.h>
using namespace std;

int main(){
	
	freopen("indextwo.in","r",stdin);
	freopen("indextwo.out","w",stdout);
	
	LL Mod,X,Y,N,M,A,B;LL Tmp,Ans;
	scanf("%lld%lld%lld%lld%lld",&Mod,&X,&Y,&N,&M);
	A = X - Y;B = M - N;
	LL Gcd = ExGcd( B , Mod , Ans , Tmp );
	if( A % Gcd ) {printf("Ohahahahahahaha\n");return 0;}
	A /= Gcd ;Mod /= Gcd;Mod = Mod<0?-Mod:Mod;
	printf("%lld\n",( Ans+Mod )%Mod*(A+Mod)%Mod);
	return 0;
}

LL ExGcd(LL A,LL B,LL &X,LL &Y){
	if(!B){
		X = 1;Y = 0;
		return A;
	}
	LL Gcd = ExGcd( B , A%B , Y , X );
	Y-=A/B*X;
	return Gcd;
}
