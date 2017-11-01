#include<cstdio>

const int MAXN = 11;
typedef long long LL;

int n;
LL B[MAXN],m[MAXN];

void Exgcd(LL a,LL b,LL &x,LL &y){
	if(!b){
		x=1;y=0;
		return;
	}
	Exgcd(b,a%b,y,x);
	y-=a/b*x;
}

LL CRT(){
	LL Ans=0;
	LL M=1,Orz1,Orz2;
	for(int i=1;i<=n;i++) M *= m[i];
	
	for(int i=1;i<=n;i++){
		LL Mi = M / m[i];
		Exgcd( Mi , m[i] , Orz1 , Orz2 );
		Ans = (Ans + Mi*Orz1*B[i] %M+M) %M;
	}
	
	return (Ans+M)%M;
}

int main(){
	
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)scanf("%lld%lld",&m[i],&B[i]);
	
	printf("%lld\n",CRT());
	
	return 0;
}
