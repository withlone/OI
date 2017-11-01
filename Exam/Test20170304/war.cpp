#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 1e6+1;

int N,MAX;long long Ans;
int Father[MAXN];

int Find(int T){return T==Father[T]?T:Father[T]=Find(Father[T]);}
int Gcd(int A,int B){return !B?A:Gcd(B,A%B);}

int main(){
	
	freopen("war.in","r",stdin);
	freopen("war.out","w",stdout);
	scanf("%d",&N);
	for(int i=1,War;i<=N;i++){
		scanf("%d",&War);
		if(Father[War])Ans+=War;
		Father[War]=War;
		MAX=max(MAX,War);
	}
	
	for(int i=MAX,T;i>=1;i--){
		T=0;
		for(int j=1;j<=MAX/i;j++)
			if(Father[i*j]){
				if(!T)T=i*j;
				else{
					int u=Find(T),v=Find(i*j);
					if(u!=v){
						Father[u]=v;
						Ans+=i;
					}
				}
			}
	}
	printf("%lld\n",Ans);
	return 0;
}
