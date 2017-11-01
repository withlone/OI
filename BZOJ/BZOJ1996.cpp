#include<cstdio>

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

typedef long long LL;
static const int MAXN = 1001;
static const int Mod  = 19650827;

int n , A[MAXN];
bool Vis[MAXN][MAXN][2];
LL f[MAXN][MAXN][2];

void Init();
LL Dfs( int , int , int );

int main(){
	
	Init();
	
	printf("%lld\n",( Dfs( 1 , n , 0 ) + Dfs( 1 , n , 1 ) ) % Mod);
	
	return 0;
}

void Init(){
	Read( n );
	For( i , 1 , n )Read( A[i] );
}
LL Dfs( int l , int r , int Lt ){
	if( l == r )return Lt;
	if( Vis[l][r][Lt] )return f[l][r][Lt];
	Vis[l][r][Lt] = true;
	if( !Lt )f[l][r][0] = Dfs( l+1 , r , 0 ) * ( A[l] < A[l+1] ) % Mod + Dfs( l+1 , r , 1 ) * ( A[l] < A[r] ) % Mod;
	else f[l][r][1] = Dfs( l , r-1 , 0 ) * ( A[r] > A[l] ) % Mod + Dfs( l , r-1 , 1 ) * ( A[r] > A[r-1] ) % Mod;
	return f[l][r][Lt];
}
