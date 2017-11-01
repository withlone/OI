#include<cstdio>
#include<cstring>

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}
template< typename Type >inline Type max ( Type x,Type y ){ return x>y?x:y; }

static const int MAXN = 1e5 +1;

int n,Ans;
int Val[MAXN][4],f[MAXN][4][2];

void Work( int St1,int St2 ){
	memset( f,0,sizeof f );
	f[1][St1][St2] = Val[1][St1];
	for( int i=2;i<=n;i++ )
		for( int j=1;j<=3;j++ )
			for( int k=1;k<=3;k++ ){
				if( k==j )continue;
				if( k> j )f[i][j][0] = max( f[i][j][0],f[i-1][k][1] + Val[i][j] );
				else f[i][j][1] = max( f[i][j][1],f[i-1][k][0] + Val[i][j] );
			}
	for( int i=1;i<=3;i++ )
		if( (i<St1)==St2&&i!=St1 )
			Ans = max( Ans,f[n][i][St2^1] );
}

int main(){
	
	Read( n );
	for( int i=1;i<=n;i++ )for( int j=1;j<=3;j++ )Read( Val[i][j] );
	
	for( int i=1;i<=3;i++ )
		for( int j=0;j<=1;j++ )
			Work( i,j );
	printf("%d\n",Ans);
	return 0;
}
