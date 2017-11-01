#include<cstdio>

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

static const int MAXN = 30;
typedef long long LL;

int n;
int A[MAXN];
int f[MAXN][MAXN],g[MAXN][MAXN];

LL Dfs( int x , int y ){
	if( f[x][y] ) return f[x][y];
	if( x > y )return 1;
	For( i , x , y ){
		int tmp = Dfs( x , i-1 )*Dfs( i+1 , y ) + A[i];
		if( tmp > f[x][y] ){
			f[x][y] = tmp;
			g[x][y] = i;
		}
	}
	return f[x][y];
}

void print( int x , int y ){
	if( x > y )return;
	printf("%d ",g[x][y]);
	print( x , g[x][y]-1 );
	print( g[x][y]+1 , y );
}

int main(){
	
	scanf( "%d" , &n );
	
	For( i , 1 , n )scanf( "%d" , &A[i] ) , f[i][i] = A[i] , g[i][i] = i;
	
	printf("%lld\n",Dfs( 1 , n ));
	
	print( 1 , n );
	
	return 0;
}
