#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 1e3 +1;

int n,Ans,In;
int f[MAXN][MAXN];

int main(){
	
	freopen("training.in","r",stdin);
	freopen("training.out","w",stdout);
	scanf("%d",&n);
	for( int i=1;i<=n;i++ )for( int j=1;j<=n;j++ ){
		scanf("%1d",&In);
		if( In )f[i][j] = f[i][j-1] + 1;
	}
	for( int i=1;i<=n;i++ )
		for( int j=n;j>=1;j-- ){
			int Min = f[i][j],Ct=1;
			if( Min*(n-i+1)<=Ans )continue;
			Ans = max( Ans,f[i][j] );
			for( int k=i;k<=n;k++ ){
				Min = min( Min,f[k][j] );
				if( Min*(n-i+1)<=Ans )break;
				Ans = max( Ans,Min*Ct );
				Ct++;
			}
		}
	
	printf("%d\n",Ans);
	return 0;
}
