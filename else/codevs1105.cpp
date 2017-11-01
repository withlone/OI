#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 101;
const int MAXM = MAXN*MAXN*MAXN;

int L,S,T,M;
int A[MAXN+1],f[MAXM];
bool Sto[MAXM];

int main(){
	
	scanf("%d%d%d%d",&L,&S,&T,&M);
	for( int i=1;i<=M;i++ )scanf("%d",&A[i]);
	sort( 1+A,1+M+A );
	A[M+1] = L;
	for( int i=1;i<=M+1;i++ )
		A[i] = A[i-1] + (A[i]-A[i-1])%2520;
	for( int i=1;i<=M;i++ )Sto[A[i]] = true;
	memset( f,126,sizeof f );
	f[0] = 0;
	for( int i=1;i<=A[M+1]+T;f[i] += Sto[i],i++ )
		for( int j=S;j<=T&&i>=j;j++ )
			f[i] = min( f[i],f[i-j] );
	int Ans = 0x7fffffff;
	for( int i=A[M+1];i<=A[M+1]+T;i++ )Ans = min( Ans,f[i] );
	printf("%d\n",Ans);
	return 0;
}
