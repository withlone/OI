#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int MAXN = 50000  + 1;
const int MAXM = 200000 + 1;

int n,m,l=1,r,Ans;
int A[MAXN],Put[MAXM],Num[1000000+1];

struct DATA{
	int l,r,Num,Pc;
	bool operator < (DATA T) const {return Pc==T.Pc?r<T.r:l<T.l;}
}Data[MAXM];

void Add(int x){
	Num[x]++;
	if(Num[x]==1) Ans++;
}

void Remove(int x){
	Num[x]--;
	if(!Num[x]) Ans--;
}

int main(){
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	
	scanf("%d",&m);
	
	for(int i=1;i<=m;i++){
		scanf("%d%d",&Data[i].l,&Data[i].r);
		Data[i].Num=i;
		Data[i].Pc=(int)sqrt(Data[i].l);
	}
	sort(1+Data,1+m+Data);
	
	for(int i=1;i<=m;i++){
		while(l<Data[i].l){
			Remove(A[l]);
			l++;
		}
		while(l>Data[i].l){
			l--;
			Add(A[l]);
		}
		while(r<Data[i].r){
			r++;
			Add(A[r]);
		}
		while(r>Data[i].r){
			Remove(A[r]);
			r--;
		}
		Put[Data[i].Num]=Ans;
	}
	
	for(int i=1;i<=m;i++) printf("%d\n",Put[i]);
	
	return 0;
}
