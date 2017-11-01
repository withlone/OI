#include<cstdio>

const int MAXK = 51;
const int MAXN = 1000001;

int n,k,Size=1;
int Pos1=1,Pos2=1;
int Ans[MAXN];

int main(){
	freopen("amaze.in","r",stdin);
	freopen("amaze.out","w",stdout);
	
	scanf("%d%d",&k,&n);
	Ans[1]=k;
	for(int i=2;i<=n;i++)
		if(Ans[Pos1]*2+1<Ans[Pos2]*3+1)
			Ans[i]=Ans[Pos1++]*2+1;
		else if(Ans[Pos1]*2+1==Ans[Pos2]*3+1)
			{Ans[i]=Ans[Pos1++]*2+1;Pos2++;}
		else Ans[i]=Ans[Pos2++]*3+1;
	
	printf("%d\n",Ans[n]);
	
	return 0;
}
