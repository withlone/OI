#include<cstdio>
#include<algorithm>
using namespace std;

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define Rep( i , _Begin , _Add ) for( int i=_Begin;i ;i = _Add )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e5 +1;

int n , u , v;
int Nt[MAXN<<1] , H[MAXN] , To[MAXN<<1] , Ct;
int Fa[MAXN] , f[MAXN][3];

void Ins( int , int );
void Dfs( int );

#define Judge

int main(){
	
	#ifdef Judge
		freopen("guard.in","r",stdin);
		freopen("guard.out","w",stdout);
	#endif
	
	Read( n );
	For( i , 1 , n-1 )Read( u ) , Read( v ) , Ins( u , v ) , Ins( v , u );
	
	Dfs( 1 );
	
	printf("%d\n",min( f[1][0] , f[1][1] ));
	
	return 0;
}

void Ins( int F , int T ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
}

void Dfs( int x ){
	f[x][0] = 1;
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( Fa[x] == y )continue;
		Fa[y] = x;
		Dfs( y );
		f[x][0] += min( f[y][0] , min( f[y][1] , f[y][2] ) );
		f[x][2] += min( f[y][0] , f[y][1] );
	}
	f[x][1] = 0x7fffffff;
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( Fa[x] == y )continue;
		f[x][1] = min( f[x][1] , f[x][2] - min( f[y][0] , f[y][1] ) + f[y][0] );
	}
}
