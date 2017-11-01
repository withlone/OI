#include<cstdio>

template< typename Type >inline Type max( Type x,Type y ){ return x>y?x:y; }
template< typename Type >inline Type min( Type x,Type y ){ return x<y?x:y; }

const int MAXN = 51;

int n,m,Ans;
int A[MAXN][MAXN],Sum[MAXN][MAXN];
int f[MAXN][MAXN][MAXN*MAXN];

int main(){
	
	scanf("%d%d",&n,&m);
	for( int j=1;j<=n;j++ )
		for( int i=n;i>=j;i-- )
			scanf("%d",&A[i][j]);
	
	for( int i=1;i<=n;i++ )
		for( int j=1;j<=i;j++ )
			Sum[i][j] = Sum[i][j-1] + A[i][j];
	
	for( int i=1;i<=n;i++ )
		for( int j=0;j<=i;j++ ){
			for( int k=(1+j)*j>>1;k<=min(m,j+((i-1)*i>>1));k++ )
				for( int p=j-1;p<=min(k,i-1);p++ )
					f[i][j][k] = max( f[i][j][k],f[i-1][p][k-j] + Sum[i][j] );
			Ans = max( Ans,f[i][j][m] );
		}
	
	printf("%d\n",Ans);
	return 0;
}
