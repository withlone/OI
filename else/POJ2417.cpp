#include<cstdio>
#include<cmath>
#include<map>
using namespace std;

typedef long long LL;

int A,B,MOD,m;
map <LL,int> Hash;

void Make(){
	LL T = B%MOD;
	for(int i=0;i<=m;T=T*A%MOD,i++)
		Hash[T] = i;
}

LL Mul(int N){
	LL Ans = 1,T = A;
	for(;N;N>>=1,T=T*T%MOD)
		if(N&1)Ans=Ans*T%MOD;
	return Ans;
}

void Find(){
	LL T = Mul(m),Ans = 1;
	for(int i=1;i<=m;i++){
		Ans=Ans*T%MOD;
		if(Hash[Ans]){
			printf("%d\n",(i*m-Hash[Ans]+MOD)%MOD);
			return ;
		}
	}
	printf("no solution\n");
}

int main(){

	while(scanf("%d%d%d",&MOD,&A,&B)==3){
		if(!(A%MOD)){printf("no solution\n");continue;}
		Hash.clear();
		m=ceil(sqrt(MOD));
		Make();
		Find();
	}
	return 0;
}
