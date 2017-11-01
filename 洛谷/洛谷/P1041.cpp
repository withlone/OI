#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 301;

int n,m,u,v,Num,Ans,Tmp;
int Nt[MAXN<<1],H[MAXN],To[MAXN<<1];
int At[MAXN][MAXN],Ct[MAXN],Dep[MAXN];
bool Vis[MAXN];

void Ins( int From,int _To ){
	Nt[++Num] = H[From];
	H[From] = Num;
	To[Num] = _To;
}


void Dfs1( int T ){
	for( int i=H[T];i;i=Nt[i] ){
		if( Dep[To[i]] )continue;
		Dep[To[i]] = Dep[T] +1;
		Dfs1( To[i] );
	}
}

void UP( int T,int Ch ){
	Vis[T] = Ch>0;Tmp += Ch;
	for( int i=H[T];i;i=Nt[i] )
		if( Dep[To[i]]>Dep[T] )UP( To[i],Ch );
}
void Dfs2( int Deep ){
	if(!Ct[Deep]){Ans = max( Ans,Tmp );return;}
	bool B = 0;
	for( int i=1;i<=Ct[Deep];i++ )
		if( !Vis[At[Deep][i]] ){
			UP( At[Deep][i],1 );
			Dfs2( Deep+1 );
			UP( At[Deep][i],-1 );
			B = 1;
		}
	if( !B ) Ans = max( Ans,Tmp );
}

int main(){
	
	scanf("%d%d",&n,&m);
	for( int i=1;i<=m;i++ )scanf("%d%d",&u,&v),Ins( u,v ),Ins( v,u );
	Dep[1] = 1;Dfs1( 1 );
	for( int i=1;i<=n;i++ )At[Dep[i]][++Ct[Dep[i]]] = i;
	Dfs2( 2 );
	printf("%d\n",n-Ans);
	return 0;
}
