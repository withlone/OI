#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

static const int MAXN = 11;

int n;
int w[MAXN][MAXN],f[MAXN][1<<MAXN+1];

int main(){
	
	while( scanf("%d",&n)){
		if( !n )return 0;
		memset( f,30,sizeof f );
		for( int i=0;i<=n;i++ )for( int j=0;j<=n;j++ )scanf("%d",&w[i][j]);
		for( int k=0;k<=n;k++ )	
			for( int i=0;i<=n;i++ )
				for( int j=0;j<=n;j++ )
					w[i][j] = min( w[i][j] , w[i][k] + w[k][j] );
		f[0][1] = 0;
		for( int St=0;St<(1<<n+1);St++ )
			for( int i=0;i<=n;i++ )
				if( !( (1<<i)&St ) )
					for( int j=0;j<=n;j++ )
						if( (1<<j)&St )
							f[i][St|(1<<i)] = min( f[i][St|(1<<i)],f[j][St]+w[j][i] );
		int Ans = 0x7fffffff;
		for( int i=1;i<=n;i++ )
			Ans = min( Ans,f[i][(1<<n+1)-1]+w[i][0] );
		printf("%d\n",Ans);
	}
}
