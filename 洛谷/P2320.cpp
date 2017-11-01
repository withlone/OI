#include<cstdio>
#include<algorithm>
using namespace std;

int n;
int A[100000];

int main(){

	scanf("%d",&n);
	for( ;n;n>>=1 )A[++A[0]] = (n>>1)+(n&1);
	sort( 1+A,1+A[0]+A );
	printf("%d\n",A[0]);
	for( int i=1;i<=A[0];i++ )printf("%d ",A[i]);
	return 0;
}
