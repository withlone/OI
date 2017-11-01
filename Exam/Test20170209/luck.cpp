#include<cstdio>

const int MAXN = 1000000001;
const int MAX = 10;

int L,R,Ans;
int Num[MAX];
int Vis[4];

int pow(int i,int j){
	int t=1;for(int k=1;k<=j;k++)t*=10;return t;
}

void Dfs(int t){
	if(t==10){
		long long Tmp1=0;int Tmp2=0;
		for(int i=1;i<MAX;i++)
		Tmp1+=(long long)(Num[i]*pow(10,MAX-i-1));
		long long Tmp=Tmp1;
		Tmp1*=Tmp1;
		for(int i=1;i<MAX;i++)Tmp2+=Num[i];
		Tmp2*=Tmp2;
		while(Tmp1)Tmp2-=Tmp1%10,Tmp1/=10;
		Ans+=!Tmp2&&Tmp&&Tmp>=L&&Tmp<=R;return;
	}
	for(int i=0;i<=3;i++){
		if(i==3&&Vis[2]||i==2&&Vis[3])continue;
		Vis[i]++;
		Num[t]=i;
		Dfs(t+1);
		Vis[i]--;
	}
}

int main(){
	freopen("luck.in","r",stdin);
	freopen("luck.out","w",stdout);
	
	scanf("%d%d",&L,&R);
	if(R==MAXN-1)Ans++;
	Dfs(1);
	
	printf("%d\n",Ans);
	return 0;
}
