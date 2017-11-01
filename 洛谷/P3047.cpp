#include<cstdio>

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define Rep( i , _Begin , _Add ) for( int i=_Begin;i;i = _Add  )
#define Lop( i , _Begin , _End ) for( int i=_Begin;i>=_End;i-- )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

typedef long long LL;
static const int MAXN = 1e5 +1;
static const int MAXK = 21;

int n , k , u , v;
int Nt[MAXN<<1] , H[MAXN] , To[MAXN<<1] , Ct;
int C[MAXN] , Fa[MAXN];
LL f[MAXN][MAXK];

void Ins( int F , int T ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
}

void Dfs1( int x ){
	For( i , 0 , k )f[x][i] = C[x];
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( y == Fa[x] )continue;
		Fa[y] = x;
		Dfs1( y );
		For( j , 1 , k )f[x][j] += f[y][j-1];
	}
}

void Dfs2( int x ){
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( y == Fa[x] )continue;
		Lop( j , k , 1 )f[y][j] += f[x][j-1] - ( j==1?0:f[y][j-2] );
		Dfs2( y );
	}
}

int main(){
	
	Read( n );Read( k );
	For( i , 1 , n-1 )Read( u ) , Read( v ) , Ins( u , v ) , Ins( v , u );
	For( i , 1 , n )Read( C[i] );
	
	Dfs1( 1 );
	Dfs2( 1 );
	
	
	For( i , 1 , n )printf("%lld\n",f[i][k]);
	return 0;
}
