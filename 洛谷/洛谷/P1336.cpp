#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

static const int MAXN = 201;
typedef long long LL;

int n,m;
int A[MAXN],B[MAXN];
LL f[MAXN];

LL Calc( int x,int a,int b ){
	LL Res = a;
	while( b-- )Res *= x;
	return Res;
}

int main(){
	
	memset( f,30,sizeof f );
	scanf("%d%d",&m,&n);
	for( int i=1;i<=n;i++ )scanf("%d%d",&A[i],&B[i]);
	f[0] = 0;
	for( int i=1;i<=n;i++ )
		for( int j=m;j>=0;j-- )
			for( int k=1;k<=j;k++ )
				f[j] = min( f[j],f[j-k]+Calc( k,A[i],B[i] ) );
	printf("%lld\n",f[m]);
	return 0;
}
