#include<cstdio>

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

typedef long long LL;
static const int MAXM = 1e5 +1;

int T , Tot;LL Ans;
LL f[MAXM];
int c[5] , d[5];

void Dfs( int x , int k , int Sum ){
	if( Sum < 0 )return;
	if( x == 5 ){
		Ans += ( k&1?-1:1 )*f[Sum];
		return;
	}
	Dfs( x+1 , k+1 , Sum - ( d[x]+1 )*c[x] );
	Dfs( x+1, k , Sum );
}

int main(){
	
	For( i , 1 , 4 )scanf("%d",&c[i]);
	scanf("%d",&T);
	
	f[0] = 1;
	For( i , 1 , 4 )
		For( j , c[i] , MAXM-1 )
			f[j] += f[j-c[i]];
	
	
	while( T-- ){
		For( i , 1 , 4 )scanf("%d",&d[i]);
		scanf("%d",&Tot);
		Ans = 0;
		Dfs( 1 , 0 , Tot );
		printf("%lld\n",Ans);
	}
	return 0;
}
