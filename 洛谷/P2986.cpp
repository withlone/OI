#include<cstdio>

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define Rep( i , _Begin , _Add ) for( int i=_Begin;i;i = _Add  )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}
template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y; }

static const int MAXN = 1e5 +1;
typedef long long LL;

int n , u , v , w , Sum;
LL C[MAXN] , Sz[MAXN] , Fa[MAXN] , Dt[MAXN];
int Nt[MAXN<<1] , H[MAXN] , To[MAXN<<1] , Dis[MAXN<<1] , Ct;
LL f[MAXN][2];

void Ins( int,int,int );
void Dfs1( int );
void Dfs2( int );

int main(){
	
	Read( n );
	For( i , 1 , n )Read( C[i] ) , Sum += C[i];
	For( i , 1 , n-1 )Read( u ) , Read( v ) , Read( w ) , Ins( u , v , w ) , Ins( v , u , w );
	
	Dfs1( 1 );
	Dfs2( 1 );
	
	LL Ans = 1e17;
	For( i , 1 , n )
		Ans = min( Ans , f[i][1] );
	
	printf("%lld\n",Ans);
	
	return 0;
}

void Ins( int F , int T , int D ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
	Dis[Ct] = D;
}

void Dfs1( int x ){
	Sz[x] = C[x];
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( y == Fa[x] )continue;
		Fa[y] = x;
		Dt[y] = Dis[i];
		Dfs1( y );
		Sz[x] += Sz[y];
		f[x][0] += Dis[i]*Sz[y] + f[y][0];
	}
}

void Dfs2( int x ){
	if( x != 1 )f[x][1] = f[Fa[x]][1] + Dt[x]*( Sum - Sz[x] ) - Sz[x] * Dt[x];
	else f[x][1] = f[x][0];
	Rep( i , H[x] , Nt[i] )
		if( To[i] != Fa[x] )Dfs2( To[i] );
}
