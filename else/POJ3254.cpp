#include<cstdio>

const int MAXN = 13;
const int Mod  = 1e8;

int n,m,Top,Ans,In;
int State[1<<MAXN],Cur[MAXN],f[MAXN][1<<MAXN];

void Init(){
	for( int i=0;i<( 1<<m );i++ )
		if( !( i&(i<<1) ) )State[++Top] = i;
}

int main(){
	
	scanf("%d%d",&n,&m);
	Init();
	for( int i=1;i<=n;i++ )for( int j=1;j<=m;j++ ){
		scanf("%d",&In);
		Cur[i] |= (!In)<<m-j;
	}
	for( int i=1;i<=Top;i++ )if( !(Cur[1]&State[i]) )f[1][i] = 1;
	for( int i=2;i<=n;i++ )
		for( int Ts=1;Ts<=Top;Ts++ ){
			if( State[Ts]&Cur[i] )continue;
			for( int Ls=1;Ls<=Top;Ls++ ){
				if( State[Ts]&State[Ls]||Cur[i-1]&State[Ls] )continue;
				( f[i][Ts] +=f[i-1][Ls] ) %=Mod;
			}
		}
	for( int i=1;i<=Top;i++ )(Ans += f[n][i]) %=Mod;
	printf("%d\n",Ans);
	return 0;
}
