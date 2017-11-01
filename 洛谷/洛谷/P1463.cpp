#include<cstdio>

typedef long long LL;

LL n,Ans,Num;
int p[13]={2,3,5,7,11,13,17,19,23,29,31,37};

void Dfs(int D,LL Tot,LL Tmp,LL Last){
	if(D==13){
		if(Ans< Tmp&&Tot> Num){Num=Tot;Ans=Tmp;}
		if(Ans>=Tmp&&Tot>=Num){Num=Tot;Ans=Tmp;}
		return;
	}
	LL T=1;
	for(int i=0;i<=Last&&T*Tmp<=n;i++){
		Dfs(D+1,Tot*(i+1),T*Tmp,i);
		T*=p[D];
	}
}

int main(){
	
	scanf("%lld",&n);
	
	Dfs(0,1,1,100);
	
	printf("%lld\n",Ans);
	
	return 0;
}
