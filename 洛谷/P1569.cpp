#include<cstdio>
#include<algorithm>
using namespace std;

static const int MAXN = 1001;

int n;
int A[MAXN],f[MAXN],Sum[MAXN];

int main(){
	
	scanf("%d",&n);
	for( int i=1;i<=n;i++ )scanf("%d",&A[i]),Sum[i] = Sum[i-1] + A[i],f[i] = Sum[i]>=0;
	for( int i=1;i<=n;i++ )
		for( int j=1;j<i;j++ )
			if( f[j]>0&&Sum[i]-Sum[j]>=0 )
				f[i] = max( f[i],f[j] +1 );
	if( !f[n] )puts("Impossible");
	else printf("%d\n",f[n]);
	return 0;
}
