#include<cstdio>
#include<algorithm>

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1001;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

int n;
int A[MAXN],Sum[MAXN];
int f[MAXN][MAXN];bool Vis[MAXN][MAXN];

int Dfs( int x,int y ){
	if( Vis[x][y] )return f[x][y];
	Vis[x][y] = 1;
	return f[x][y] = Sum[y] - Sum[x-1] - std::min( Dfs( x+1 , y ) , Dfs( x , y-1 ) );
}

void print( int x,int y,int Ct ){
	if( x==y ){
		if( Ct&1 )printf("%d",x);
		return;
	}
	if( Sum[y] - Sum[x-1] - f[x][y] ==f[x+1][y] ){
		if( Ct&1 )printf("%d ",x);
		print( x+1 , y , Ct+1 );
	}
	else{
		if( Ct&1 )printf("%d ",y);
		print( x , y-1 , Ct+1 );
	}
}

#define Judge
int main(){
	
	#ifdef Judge
		freopen("poker.in","r",stdin);
		freopen("poker.out","w",stdout);
	#endif
	
	
	Read( n );
	For( i , 1 , n )Read( A[i] ) , Vis[i][i] = 1 , f[i][i] = A[i] , Sum[i] = Sum[i-1] + A[i] ;
	int Ans = Dfs( 1 , n );
	puts( Ans>Sum[n]-Ans?"WIN":"LOSE" );
	printf("%d\n",Ans);
	print( 1 , n , 1 );
	puts("");
	return 0;
}
