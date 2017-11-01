#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define Mem(i) memset(i,0,sizeof i)
const int MAXN = 1e4 +1;

int n,u,w,Num;
int Nt[MAXN<<1],H[MAXN],To[MAXN<<1],Dis[MAXN<<1],Fa[MAXN],f[MAXN][3];

void Ins( int From,int to,int dis ){
	Nt[++Num] = H[From];
	H[From] = Num;
	To[Num] = to;
	Dis[Num]= dis;
}

void Dfs1( int T ){
	for( int i=H[T];i;i=Nt[i] ){
		if( Fa[T]==To[i] )continue;
		Fa[To[i]] = T;Dfs1( To[i] );
		if( f[To[i]][0]+Dis[i]>f[T][0] ){
			f[T][1] = f[T][0];
			f[T][0] = f[To[i]][0]+Dis[i];
		}
		else if( f[To[i]][0]+Dis[i]>f[T][1] )f[T][1] = f[To[i]][0]+Dis[i];
	}
}
void Dfs2( int T ){
	for( int i=H[T];i;i=Nt[i] ){
		if( Fa[T]==To[i] )continue;
		f[To[i]][2] = max( f[T][f[T][0]==( f[To[i]][0]+Dis[i] )],f[T][2] )+Dis[i];
		Dfs2( To[i] );
	}
}

int main(){
	
	while( ~scanf("%d",&n) ){
		Num = 0;
		Mem( Nt );Mem( H );Mem( To );Mem( Dis );Mem( Fa );Mem( f );
		for( int i=2;i<=n;i++ )scanf("%d%d",&u,&w),Ins( u,i,w ),Ins( i,u,w );
		Dfs1( 1 );
		Dfs2( 1 );
		for( int i=1;i<=n;i++ )printf("%d\n",max( f[i][0],f[i][2] ));
	}
	return 0;
}
