#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;

const int MAXN = 1e5+1;

#define Pair pair<long long,int>

int n;long long Ans,Tmp;
long long w[MAXN],l[MAXN],d[MAXN],Sum[MAXN];

priority_queue<Pair,vector<Pair>,greater<Pair> > Heap;

int main(){
	freopen("Bomb.in","r",stdin);
	freopen("Bomb.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;Sum[i]=Sum[i-1]+w[i],i++)
		scanf("%lld%lld%lld",&d[i],&w[i],&l[i]);
	
	for(int i=1;i<=n;i++){
		for(;!Heap.empty()&&Sum[i]>Heap.top().first;Heap.pop()) Tmp-=d[Heap.top().second];
		Heap.push(make_pair(Sum[i-1]+l[i],i));Tmp+=d[i];
		if(Tmp<Ans||!Ans)
			Ans=Tmp;
	}
	
	printf("%lld\n",Ans);
	
	return 0;
}
