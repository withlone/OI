#include<cstdio>
#include<algorithm>
using namespace std;

#define TWO for(int i=1;i<=2;i++)
const int MAXN = 100000;
int Heap[MAXN];

void Push(int in)
{
	Heap[++Heap[0]]=in;
	int now=Heap[0];
	while(now>1&&Heap[now]<Heap[now>>1])
	{
		swap(Heap[now],Heap[now>>1]);
		now>>=1;
	}
}

int put()
{
	int pos=1,RETURN=Heap[1];
	Heap[1]=Heap[Heap[0]--];
	while(pos*2<=Heap[0]&&Heap[pos]>min(Heap[pos*2],Heap[pos*2+1]))
	{
		int next=Heap[pos*2]<Heap[pos*2+1]?pos*2:pos*2+1;
		swap(Heap[pos],Heap[next]);
		pos=next;
	}
	return RETURN;
}

int main()
{
	
	freopen( "fruit.in" , "r" , stdin ) ;
	freopen( "fruit.out" , "w" , stdout ) ;
	
	int n,now;
	scanf("%d",&n);
	for(int i=1,Fruit;i<=n;i++,Push(Fruit))
		scanf("%d",&Fruit);
	int ans=0;
	WHILE:
	now=0;
	TWO now+=put();
	ans+=now;
	if(Heap[0])
	{
		Push(now);
		goto WHILE;
	}
	printf("%d",ans);
	return 0;
}
