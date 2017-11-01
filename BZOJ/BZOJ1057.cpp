#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

static const int MAXN = 2e3 +1;

int n,m;
int A[MAXN][MAXN];
int f[MAXN][MAXN];
int Up[MAXN][MAXN],l[MAXN][MAXN],r[MAXN][MAXN];

int First(){
	int Ans = 0;
	for( int i=1;i<=n;i++ )for( int j=1;j<=m;j++ ){
		l[i][j] = 1;
		if( j!=1 )l[i][j] += (A[i][j]==A[i][j-1])*l[i][j-1];
	}
	for( int i=1;i<=n;i++ )f[1][i] = f[i][1] = 1;
	for( int i=2;i<=n;i++ )for( int j=2;j<=m;j++ ){
		if( A[i][j]!=A[i-1][j-1] )f[i][j] = 1;
		else f[i][j] = min( min( l[i][j],Up[i][j] ),f[i-1][j-1]+1 );
		Ans = max( Ans,f[i][j] );
	}
	return Ans*Ans;
}
int Second(){
	memset( l,0,sizeof l );
	for( int i=1;i<=n;i++ )l[i][1] = 1;
	for( int i=1;i<=n;i++ )for( int j=2;j<=m;j++ ){
		l[i][j] = 1;
		int k = j-1;
		while( A[i][j]==A[i][k]&&Up[i][j]<=Up[i][k] ){
			l[i][j] += l[i][k];
			k -= l[i][k];
		}
	}
	for( int i=1;i<=n;i++ )r[i][m] = 1;
	for( int i=1;i<=n;i++ )for( int j=m-1;j;j-- ){
		r[i][j] = 1;
		int k = j+1;
		while( A[i][j]==A[i][k]&&Up[i][j]<=Up[i][k] ){
			r[i][j] += r[i][k];
			k += r[i][k];
		}
	}
	int Ans = 0;
	for( int i=1;i<=n;i++ )for( int j=1;j<=m;j++ )
		Ans = max( Ans,Up[i][j]*( l[i][j]+r[i][j]-1 ) );
	return Ans;
}

void Init(){
	for( int i=1;i<=m;i++ )Up[1][i] = 1;
	for( int i=2;i<=n;i++ )for( int j=1;j<=m;j++ )
		Up[i][j] = (A[i-1][j]==A[i][j])*Up[i-1][j] +1;
}

int main(){
	
	scanf("%d%d",&n,&m);
	for( int i=1;i<=n;i++ )for( int j=1;j<=m;j++ ){
		scanf("%d",&A[i][j]);
		if( !((i&1)^(j&1)) )A[i][j] ^= 1;
	}
	Init();
	
	printf("%d\n",First());
	printf("%d\n",Second());
	return 0;
}
