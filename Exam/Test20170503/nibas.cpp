#include<cstdio>

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}
template< typename Type >inline Type max( Type x , Type y ){ return x>y?x:y; }

static const int MAXM = 3e4 +1;
static const int MAXN = 51;

int n , m;
int A[MAXN] , B[MAXN] , C[MAXN];
int Nt[MAXM] , H[MAXM] , To[MAXM] , Ct;
int f[MAXN][MAXM];

void Ins( int F , int T ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
}

void Dfs( int x ){
	for( int i = H[x] ; i ; i = Nt[i] ){
		int y = To[i];
		For( j , 0 , m )f[y][j] = f[x][j] + B[y];
		Dfs( y );
		For( j , A[y] , m )f[x][j] = max( f[x][j] , f[y][j-A[y]] );
	}
}

#define Judge

int main(){
	
	#ifdef Judge
		freopen("nibas.in","r",stdin);
		freopen("nibas.out","w",stdout);
	#endif
	
	Read( m );Read( n );
	For( i , 1 , n )Read( A[i] ) , Read( B[i] ) , Read( C[i] ) , Ins( C[i] , i );
	Dfs( 0 );
	printf("%d\n",f[0][m]);
	return 0;
}
