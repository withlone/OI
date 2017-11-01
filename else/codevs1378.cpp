#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 302;

int n,m,Fir,Num;
int Scr[MAXN],f[MAXN][MAXN];
int Nt[MAXN],To[MAXN],H[MAXN];

void Ins( int From,int _To ){
	Nt[++Num] = H[From];
	H[From] = Num;
	To[Num] = _To;
}

void Dfs( int T ){
	for( int i=H[T];i;i=Nt[i] ){
		for( int j=1;j<=m;j++ )f[To[i]][j] = f[T][j] + Scr[To[i]];
		Dfs( To[i] );
		for( int j=1;j<=m;j++ )f[T][j] = max( f[T][j],f[To[i]][j-1] );
	}
}

int main(){
	
	scanf("%d%d",&n,&m);m++;
	for( int i=1;i<=n;i++ )scanf("%d%d",&Fir,&Scr[i]),Ins( Fir,i );
	Dfs( 0 );
	int Ans = 0;
	for( int i=0;i<=m;i++ )if( Ans<f[0][i] )Ans = f[0][i];
	
	printf("%d\n",Ans);
	return 0;
}
