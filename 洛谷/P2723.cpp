#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;

const int MAXK = 101;
const int MAXN = 100001;
#define Pair pair<int,int>

int K,N;
int A[MAXK],p[MAXN],Ans[MAXN]={1};
priority_queue<Pair,vector<Pair>,greater<Pair> > Heap;

int main(){
	
	scanf("%d%d",&K,&N);
	
	for(int i=1;i<=K;i++)scanf("%d",&A[i]),Heap.push(make_pair(A[i],i));
	
	for(int i=1;i<=N;i++){
		Pair u = Heap.top();Heap.pop();
		Ans[i] = u.first;
		for(;Heap.top().first==u.first&&!Heap.empty();){
			Pair v = Heap.top();Heap.pop();
			Heap.push(make_pair(Ans[++p[v.second]]*A[v.second],v.second));
		}
		Heap.push(make_pair(Ans[++p[u.second]]*A[u.second],u.second));
	}
	
	printf("%d\n",Ans[N]);
	
	return 0;
}
