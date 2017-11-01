#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int MAXN = 50000 + 1;

int n,m,k,l=1,r=0,Ans;
int A[MAXN],Put[MAXN],Num[MAXN];

struct DATA{
	int l,r,Num,At;
	bool operator < (DATA T) const {return At==T.At&&r<T.r||At<T.At;}
}Data[MAXN+1];

int Pow(int x){
	return x*x;
}

void Add(int x){
	Num[x]++;
	Ans+=Pow(Num[x])-Pow(Num[x]-1);
}

void Remove(int x){
	Num[x]--;
	Ans+=Pow(Num[x])-Pow(Num[x]+1);
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&Data[i].l,&Data[i].r);
		Data[i].Num=i;
		Data[i].At=(int)sqrt(Data[i].l);
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
