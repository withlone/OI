#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 100001;
typedef long long LL;

int n;LL Ans;
LL Match[MAXN][3],c[MAXN],T[MAXN];

struct DATA{
	int Value,Num;
	bool operator < (DATA Tmp) const {return Value<Tmp.Value;}
}Data[3][MAXN];

int Lowbit(int k){
	return k&-k;
}

void Modify(int x,int k){
	for(;x<=n;x+=Lowbit(x)) c[x]+=k;
}

LL Query(int x){
	LL Ans=0;
	for(;x;x-=Lowbit(x))Ans+=c[x];
	return Ans;
}

LL Work(){
	for(int i=1;i<=n;i++){
		Data[1][i].Value=Match[i][1],Data[1][i].Num=i;
		Data[2][i].Value=Match[i][2],Data[2][i].Num=i;
	}
	sort(1+Data[1],1+n+Data[1]);sort(1+Data[2],1+n+Data[2]);
	for(int i=1;i<=n;i++) T[Data[1][i].Num]=Data[2][i].Num;
	LL Tmp=0;
	for(int i=1;i<=n;i++){
		Modify(T[i],1);
		Tmp+=i-Query(T[i]);Tmp%=99999997;
	}
	
	return Tmp;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&Match[i][1]);
	for(int i=1;i<=n;i++)scanf("%lld",&Match[i][2]);
	
	Ans=Work();
	
	printf("%lld\n",Ans);
	
	return 0;
}
