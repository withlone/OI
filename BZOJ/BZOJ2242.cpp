#include<cstdio>
#include<map>
#include<cmath>
using namespace std;

typedef long long LL;

int A,B,MOD,m;

LL Pow(LL X,LL N){
	LL T = 1;
	for(;N;N>>=1,X=X*X%MOD)
		if(N&1)T=T*X%MOD;
	return T;
}

LL ExGcd(LL a,LL b,LL& X,LL& Y){
	if(!b){
		X=1LL;Y=0;
		return a;
	}
	LL Gcd = ExGcd(b,a%b,X,Y);
	LL T = Y;Y = X-a/b*Y;X = T;
	return Gcd;
}

void BSGS(){
	if(!(A%MOD)){printf("Orz, I cannot find x!\n");return;}
	map <LL,int> Hash;
	m=ceil(sqrt(MOD));
	
	LL T = B%MOD,Ans=1;
	for(int i=0;i<=m;T=T*A%MOD,i++)
		Hash[T] = i;

	T=Pow(A,m);
	for(int i=1;i<=m;i++){
		Ans=Ans*T%MOD;
		if(Hash[Ans]){
			printf("%d\n",(i*m-Hash[Ans]+MOD)%MOD);
			return ;
		}
	}
	printf("Orz, I cannot find x!\n");
}

int main(){
	
	int Type,T;
	scanf("%d%d",&T,&Type);
	while( T-- ){
		scanf("%d%d%d",&A,&B,&MOD);
		switch(Type){
			case 1:printf("%lld\n",Pow(A,B));break;
			case 2:{
				LL Ans,Tmp,Gcd;Gcd=ExGcd(A,MOD,Ans,Tmp);
				if(B%Gcd)printf("Orz, I cannot find x!\n");
				else printf("%lld\n",(B/Gcd*Ans%MOD+MOD)%MOD);
				break;
			}
			case 3:BSGS();break;
		}
	}
	return 0;
}
