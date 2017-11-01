#include<cstdio>

static const int MAXN = 1e4 +1;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

int n,Ans;
int A[MAXN];

void Dfs( int i ){
	if( i==n+1 ){ Ans += !A[i-1];return; }
	if( A[i-1]==1&&A[i]&&(A[i+1]||i==n) ){
		A[i-1]--;A[i]--;A[i+1]--;
		Dfs( i+1 );
		A[i-1]++;A[i]++;A[i+1]++;
	}
	if( !A[i-1] ) Dfs( i+1 );
}

int main(){
	
	scanf("%d",&n);
	For( i , 1 , n )scanf("%d",&A[i]);
	Dfs( 2 );
	A[1]--;A[2]--;
	Dfs( 2 );
	printf("%d\n",Ans);
	return 0;
}
