#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;

const int MAXN = 1000001;
const int MAXT = 700001;

int n,Ans;
priority_queue<int> Que;
pair <int,int> Work[MAXN];

int main(){
	freopen("homework.in","r",stdin);
	freopen("homework.out","w",stdout);
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&Work[i].first,&Work[i].second);
	sort(1+Work,1+n+Work);
	
	int Pos=n;
	for(int i=Work[n].first;i>=1;i--){
		while(Work[Pos].first==i&&Pos) Que.push(Work[Pos--].second);
		if(Que.empty())continue;
		Ans+=Que.top();Que.pop();
	}
	
	printf("%d\n",Ans);
	
	return 0;
}
