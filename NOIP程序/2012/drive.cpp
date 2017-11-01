#include<cstdio>
#include<climits>
#include<set>
#include<map>
#include<algorithm>
using namespace std;

const int MAXN = 100001;
const int MAXM = 10001;
const int MAX = 17;
typedef long long LL;

int n,m,Min1,Min2,x0,Ans;LL Ans1,Ans2,T1,T2;
int H[MAXN],Next_A[MAXN],Next_B[MAXN],A_Dis[MAXN],B_Dis[MAXN];
int Father[MAXN][MAX+1],Fa[MAXN][MAX+1],Fb[MAXN][MAX+1];
bool Flag;

set <int> Set;
set <int> :: iterator it;
map <int,int> Map;

void Do(int i){
	Min2=Min1;Min1=abs(*it-H[i]);
	Next_A[i]=Next_B[i];Next_B[i]=Map[*it];
}

void Query(int u,int Tmp,int i){
	T1=T2=0;
	for(int j=MAX;j>=0;j--)
		if(Father[u][j]&&Tmp-Fa[u][j]-Fb[u][j]>=0){
			Tmp-=Fa[u][j]+Fb[u][j];
			T1+=Fa[u][j];T2+=Fb[u][j];
			u=Father[u][j];
		}
	
	if(Next_A[u]&&Fa[u][0]<=Tmp)T1+=Fa[u][0];
	
	if(Flag||T2&&(!Ans||Ans1*T2>Ans2*T1)){
		Ans1=T1;Ans2=T2;Ans=i;
	}
}

int main(){
	
	freopen( "drive.in" , "r" , stdin ) ;
	freopen( "drive.out" , "w" , stdout ) ;
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&H[i]),Map[H[i]]=i;
	
	for(int i=n;i>=1;i--){
		Min1=Min2=INT_MAX;
		Set.insert(H[i]);
		it=Set.find(H[i]);
		if(it!=Set.begin()){
			if(H[i]-*--it<Min1) Do(i);
			else if(H[i]-*it<Min2){Min2=H[i]-*it;Next_A[i]=Map[*it];}
			if(it!=Set.begin()){
				if(H[i]-*--it<Min1) Do(i);
				else if(H[i]-*it<Min2){Min2=H[i]-*it;Next_A[i]=Map[*it];}
				++it;
			}
			++it;
		}
		if(++it!=Set.end()){
			if(*it-H[i]<Min1) Do(i);
			else if(*it-H[i]<Min2){Min2=*it-H[i];Next_A[i]=Map[*it];}
			if(++it!=Set.end())
				if(*it-H[i]<Min1) Do(i);
				else if(*it-H[i]<Min2){Min2=*it-H[i];Next_A[i]=Map[*it];}
		}
		A_Dis[i]=Min2;B_Dis[i]=Min1;
	}
	
	for(int i=1;i<=n;i++){
		Father[i][0]=Next_B[Next_A[i]];
		Fa[i][0]=A_Dis[i];Fb[i][0]=B_Dis[Next_A[i]];
	}
	
	for(int j=1;j<=MAX;j++)
		for(int i=1;i<=n;i++){
			Father[i][j]=Father[Father[i][j-1]][j-1];
			Fa[i][j]=Fa[i][j-1]+Fa[Father[i][j-1]][j-1];
			Fb[i][j]=Fb[i][j-1]+Fb[Father[i][j-1]][j-1];
		}
	
	scanf("%d",&x0);
	
	for(int i=1;i<=n;i++) Query(i,x0,i);
	
	printf("%d\n",Ans);
	
	scanf("%d",&m);Flag=1;
	while(m--){
		int u,v;
		scanf("%d%d",&u,&v);
		Query(u,v,u);
		printf("%lld %lld\n",Ans1,Ans2);
	}
	
	return 0;
}
