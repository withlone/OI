#include<cstdio>

const int MAXK = 16;
const int MAXN = 1000 + 1;

int k,n;
int s,Ex[MAXN];
long long Pow[MAXN];
long long Ans;

void Turn(int A){
	for(;A;A>>=1) Ex[++s]=A&1;
}

int main(){
	scanf("%d%d",&k,&n);
	
	Turn(n);
	Pow[0]=1;
	for(int i=1;i<=s;i++) Pow[i]=Pow[i-1]*k;
	
	for(int i=s;i>=1;i--) Ans+=Ex[i]*Pow[i-1];
	
	printf("%lld\n",Ans);
	
	return 0;
}
