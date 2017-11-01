#include<cstdio>

typedef long long LL;

LL ExGcd(LL a,LL b,LL &x,LL &y){
	if(!b){
		x=1;y=0;
		return a;
	}
	LL Gcd= ExGcd(b,a%b,x,y);
	LL T  = x;
	    x	 = y;
	    y  = T-a/b*y;
	return Gcd;
}

LL x,y,m,n,L,A,B,T1,T2,Gcd;

int main(){
	
	scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&L);
	A=n-m;B=x-y;
	Gcd=ExGcd(A,L,T1,T2);
	L/=Gcd;L=L<0?-L:L;
	if(B%Gcd) printf("Impossible\n");
	else printf("%lld\n",(B/Gcd*T1%L+L)%L);
	
	return 0;
}
