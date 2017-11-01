#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 101;

int n,m,Tp;
int Cur[MAXN],St[MAXN],Num[MAXN],f[MAXN][MAXN][MAXN];

bool Ok( int x ){
	return !(x&(x<<1))&&!(x&(x<<2));
}

void Init(){
	for( int i=0;i<( 1<<m );i++ )
		if( Ok( i ) )St[++Tp] = i;
}

int Get( int x ){
	int Ans = 0;for( ;x;x>>=1 )Ans += x&1;return Ans;
}

int main(){
	
	scanf("%d%d",&n,&m);Init();
	for( int i=1;i<=n;i++ )for( int j=1;j<=m;j++ ){
		char ch = getchar();
		while( ch!='H'&&ch!='P' )ch=getchar();
		if( ch=='H' ) Cur[i] |= 1<<j-1;
	}
	for( int i=1;i<=Tp;i++ ){
		Num[i] = Get( St[i] );
		if( !(St[i]&Cur[1]) )f[1][i][1] = Num[i];
	}
	for( int i=2;i<=n;i++ )
		for( int Ts=1;Ts<=Tp;Ts++ ){
			if( St[Ts]&Cur[i] )continue;
			for( int Ls=1;Ls<=Tp;Ls++ ){
				if( St[Ls]&Cur[i-1]||St[Ls]&St[Ts] )continue;
				for( int LLs=1;LLs<=Tp;LLs++ ){
					if( St[LLs]&Cur[i-2]||St[LLs]&St[Ls]||St[LLs]&St[Ts] )continue;
					f[i][Ts][Ls] = max( f[i][Ts][Ls] , f[i-1][Ls][LLs] + Num[Ts] );
				}
			}
		}
	int Ans = 0;
	for( int i=1;i<=Tp;i++ )for( int j=1;j<=Tp;j++ )Ans = max( Ans,f[n][i][j] );
	printf("%d\n",Ans);
	return 0;
}
