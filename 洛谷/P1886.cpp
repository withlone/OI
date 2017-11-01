#include<cstdio>
#include<algorithm>
using namespace std;

static const int MAXN = 1e6 +1;

int n,M,k;
int d[2][MAXN<<2];
int A[MAXN],Min[MAXN],Max[MAXN];

void UP( int x ){
	d[0][x] = min( d[0][x<<1],d[0][x<<1|1] );
	d[1][x] = max( d[1][x<<1],d[1][x<<1|1] );
}
int Q0( int s,int t ){
	int Res = 0x7fffffff;
	for( s+=M-1,t+=M+1;s^t^1;s>>=1,t>>=1 ){
		if(~s&1 )Res = min( Res,d[0][s^1] );
		if( t&1 )Res = min( Res,d[0][t^1] );
	}
	return Res;
}
int Q1( int s,int t ){
	int Res = -0x7fffffff;
	for( s+=M-1,t+=M+1;s^t^1;s>>=1,t>>=1 ){
		if(~s&1 )Res = max( Res,d[1][s^1] );
		if( t&1 )Res = max( Res,d[1][t^1] );
	}
	return Res;
}

int main(){
	
	scanf("%d%d",&n,&k);
	for( M=1;M<n+2;M<<=1 );
	for( int i=1;i<=n;i++ )scanf("%d",&A[i]),d[0][i+M]=d[1][i+M]=A[i];
	for( int i=M-1;i;i-- )UP( i );
	for( int i=1;i<=n-k+1;i++ )Min[i] = Q0( i,i+k-1 ),Max[i] = Q1( i,i+k-1 );
	for( int i=1;i<=n-k+1;i++ )printf("%d ",Min[i]);puts("");
	for( int i=1;i<=n-k+1;i++ )printf("%d ",Max[i]);puts("");
	return 0;
}
