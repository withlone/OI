#include<cstdio>

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )
#define Rep( i , _Begin , _End ) for( int i=(_Begin);i>=(_End);i-- )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

static const int Inf  = 1e4;
static const int MAXN = 101;

int n , T;int A[MAXN];
int Ch[MAXN] , Sz;
bool f[MAXN][Inf<<1|1];int g[MAXN][Inf<<1|1];

void Dfs( int , int );

int main(){
	
	#define Judge
	#ifdef Judge
		freopen("substract.in","r",stdin);
		freopen("substract.out","w",stdout);
	#endif
	
	Read( n );Read( T );
	For( i , 1 , n )Read( A[i] );
	f[2][A[1] - A[2] + Inf] = true;
	For( i , 3 , n )
		For( j , -Inf+A[i] , Inf ){
			if( f[i-1][j-A[i]+Inf] )f[i][j+Inf] = true , g[i][j+Inf] = 1;
			if( f[i-1][j+A[i]+Inf] )f[i][j+Inf] = true , g[i][j+Inf] = 2;
		}
	Dfs( n , T + Inf );
	int tmp = 0;
	For( i , 1 , n )if( Ch[i] )printf("%d ",i-(tmp++));n -= tmp;
	while( --n )printf("1 ");
	return 0;
}
void Dfs( int x , int tmp ){
	if( x == 1 )return;
	if( g[x][tmp] == 1 )Dfs( x - 1 , tmp - A[x] ) , Ch[++Sz] = 1;
	else Dfs( x - 1 , tmp + A[x] ) , Ch[++Sz] = 0;
}
