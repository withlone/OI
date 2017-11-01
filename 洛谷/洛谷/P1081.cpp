#include<cstdio>
#include<map>
#include<set>
#include<algorithm>
using namespace std;

const int MAXN = 100001;
const int MAXM = 10001;
const int MAX  = 20;
typedef long long LL;

int n,m,Size;int x0,Ans;LL Ans1,Ans2,T1,T2;
LL H[MAXN];
int A_Next[MAXN],B_Next[MAXN],A_Dis[MAXN],B_Dis[MAXN];
int Father[MAXN][MAX+1],Fa[MAXN][MAX+1],Fb[MAXN][MAX+1];
bool Flag;

map <LL,int> MAP;
set <int> Set;
set <int> ::iterator it;

struct DATA{
	int Dis,Next;
	bool operator < (DATA Tmp) const{return Dis<Tmp.Dis;}
}Data[5];

void Open(int Dis,int Next){
	Data[++Size].Dis=Dis;
	Data[Size].Next=Next;
}

void Init(){
	for(int i=n;i>=1;i--){
		Size=0;
		Set.insert(H[i]);
		it=Set.find(H[i]);
		if(it!=Set.begin()){
			it--;
			Open(H[i]-*it,MAP[*it]);
			if(it!=Set.begin()){
				it--;Open(H[i]-*it,MAP[*it]);it++;
			}
			it++;
		}
		if(++it!=Set.end()){
			Open(*it-H[i],MAP[*it]);
			if(++it!=Set.end()) Open(*it-H[i],MAP[*it]);
		}
		sort(1+Data,1+Size+Data);
		if(Size>=2) A_Next[i]=Data[2].Next,A_Dis[i]=Data[2].Dis;
		if(Size>=1) B_Next[i]=Data[1].Next,B_Dis[i]=Data[1].Dis;
	}
	
	for(int i=1;i<=n;i++){
		Father[i][0]=B_Next[A_Next[i]];
		Fa[i][0]=A_Dis[i];Fb[i][0]=B_Dis[A_Next[i]];
	}
	
	for(int j=1;j<=MAX;j++)
		for(int i=1;i<=n;i++){
			Father[i][j]=Father[Father[i][j-1]][j-1];
			Fa[i][j]=Fa[i][j-1]+Fa[Father[i][j-1]][j-1];
			Fb[i][j]=Fb[i][j-1]+Fb[Father[i][j-1]][j-1];
		}
}

void Query(int Start,int Time){
	T1=T2=0;int u=Start;
	for(int i=MAX;i>=0;i--)
		if(Father[u][i]&&T1+T2+Fa[u][i]+Fb[u][i]<=Time){
			T1+=Fa[u][i];T2+=Fb[u][i];
			u=Father[u][i];
		}
	
	if(A_Next[u]&&T1+T2+A_Dis[u]<=Time) T1+=A_Dis[u];
	
	if(Flag) printf("%lld %lld\n",T1,T2);
	else if(T2&&(!Ans||Ans1*T2>Ans2*T1)){
		Ans=Start;
		Ans1=T1;Ans2=T2;
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&H[i]),MAP[H[i]]=i;
	
	Init();
	
	scanf("%d",&x0);
	
	for(int i=1;i<=n;i++) Query(i,x0);
	
	printf("%d\n",Ans);
	Flag=1;
	scanf("%d",&m);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		Query(u,v);
	}
	
	return 0;
}
