#include<cstdio>

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )
#define Rep( i , _Begin , _End ) for( int i=(_Begin);i>=(_End);i-- )

template< typename Type >inline Type max ( Type x , Type y ){ return x > y ? x : y; }
template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

static const int Inf  = 1e8;
static const int MAXN = 101;

int n , k , u , Ans , x , y , z;
bool Vis[3][MAXN];
int L[11][2] , R[11][2] , Ct;
int C[3][MAXN] , Sum[3][MAXN];
int f[5][MAXN][11] , g[5][MAXN][11] , G[5][MAXN][11];

void CG();
void Dp();
void Init();
void print();

int main(){
	
	#define Judge
	#ifdef Judge
		freopen("fire.in","r",stdin);
		freopen("fire.out","w",stdout);
	#endif
	
	Init();
	Dp();
	print();
	return 0;
}
void CG(){
	int tmp1 = g[x][y][z] , tmp2 = G[x][y][z];
	x = tmp1;y--;z = tmp2;
}
void Dp(){
	f[1][1][1] = C[1][1];f[2][1][1] = C[2][1];f[4][1][1] = C[1][1] + C[2][1];f[3][1][1] = -Inf;
	For( i , 2 , n )
		For( j , 1 , k ){
			if( f[1][i-1][j]   > f[0][i][j] )f[0][i][j] = f[1][i-1][j] , g[0][i][j] = 1 , G[0][i][j] = j;
			if( f[2][i-1][j]   > f[0][i][j] )f[0][i][j] = f[2][i-1][j] , g[0][i][j] = 2 , G[0][i][j] = j;
			if( f[3][i-1][j]   > f[0][i][j] )f[0][i][j] = f[3][i-1][j] , g[0][i][j] = 3 , G[0][i][j] = j;
			if( f[4][i-1][j]   > f[0][i][j] )f[0][i][j] = f[4][i-1][j] , g[0][i][j] = 4 , G[0][i][j] = j;
			if( f[0][i-1][j]   > f[0][i][j] )f[0][i][j] = f[0][i-1][j] , g[0][i][j] = 0 , G[0][i][j] = j;
			
			if( f[0][i-1][j-1] > f[1][i][j] && j )f[1][i][j] = f[0][i-1][j-1] , g[1][i][j] = 0 , G[1][i][j] = j-1;
			if( f[1][i-1][j]   > f[1][i][j] )f[1][i][j] = f[1][i-1][j] , g[1][i][j] = 1 , G[1][i][j] = j;
			if( f[2][i-1][j-1] > f[1][i][j] && j )f[1][i][j] = f[2][i-1][j-1] , g[1][i][j] = 2 , G[1][i][j] = j-1;
			if( f[3][i-1][j]   > f[1][i][j] && j > 1 )f[1][i][j] = f[3][i-1][j] , g[1][i][j] = 3 , G[1][i][j] = j;
			if( f[4][i-1][j-1] > f[1][i][j] && j )f[1][i][j] = f[4][i-1][j-1] , g[1][i][j] = 4 , G[1][i][j] = j-1;
			
			if( f[0][i-1][j-1] > f[2][i][j] && j )f[2][i][j] = f[0][i-1][j-1] , g[2][i][j] = 0 , G[2][i][j] = j-1;
			if( f[1][i-1][j-1] > f[2][i][j] && j )f[2][i][j] = f[1][i-1][j-1] , g[2][i][j] = 1 , G[2][i][j] = j-1;
			if( f[2][i-1][j]   > f[2][i][j] )f[2][i][j] = f[2][i-1][j] , g[2][i][j] = 2 , G[2][i][j] = j;
			if( f[3][i-1][j]   > f[2][i][j] && j > 1 )f[2][i][j] = f[3][i-1][j] , g[2][i][j] = 3 , G[2][i][j] = j;
			if( f[4][i-1][j-1] > f[2][i][j] && j )f[2][i][j] = f[4][i-1][j-1] , g[2][i][j] = 4 , G[2][i][j] = j-1;
			
			if( f[1][i-1][j-1] > f[3][i][j] && j )f[3][i][j] = f[1][i-1][j-1] , g[3][i][j] = 1 , G[3][i][j] = j-1;
			if( f[2][i-1][j-1] > f[3][i][j] && j )f[3][i][j] = f[2][i-1][j-1] , g[3][i][j] = 2 , G[3][i][j] = j-1;
			if( f[3][i-1][j]   > f[3][i][j] )f[3][i][j] = f[3][i-1][j] , g[3][i][j] = 3 , G[3][i][j] = j;
			
			if( f[0][i-1][j-1] > f[4][i][j] )f[4][i][j] = f[0][i-1][j-1] , g[4][i][j] = 0 , G[4][i][j] = j-1;
			if( f[4][i-1][j]   > f[4][i][j] )f[4][i][j] = f[4][i-1][j] , g[4][i][j] = 4 , G[4][i][j] = j;
			
			f[1][i][j] += C[1][i];f[2][i][j] += C[2][i];f[3][i][j] += C[1][i] + C[2][i];f[4][i][j] += C[1][i] + C[2][i];
		}
	Ans = 0;
	For( i , 0 , 4 )For( j , 1 , k )if( Ans < f[i][n][j] )Ans = f[i][n][j] , x = i , z = j;
}
void Init(){
	Read( n );Read( k );
	For( i , 1 , 2 )For( j , 1 , n )Read( C[i][j] );
	For( i , 1 , 2 )For( j , 1 , n )Read( u ) , Sum[i][j] = ( C[i][j] = u - C[i][j] ) + Sum[i][j-1];
}
void print(){
	y = n;
	while( y ){
		if( x == 1 || x == 2 )Vis[x][y] = 3 - x;
		if( x == 3 || x == 4 )Vis[1][y] = Vis[2][y] = 1;
		CG();
	}
	For( j , 1 , n ){
		if( Vis[1][j]*Vis[2][j]&&!(Vis[1][j-1] + Vis[2][j-1]) ){
			Ct++;int tmp = j;
			L[Ct][0] = 1;L[Ct][1] = j;
			while( Vis[1][j]*Vis[2][j] ){
				Vis[1][j] = Vis[2][j] = 0;
				j++;
			}
			R[Ct][0] = 2;R[Ct][1] = j-1;
			if( Vis[1][j] + Vis[2][j] ){
				Ct--;
				For( i , tmp , j-1 )Vis[1][i] = Vis[2][i] = 1;
			}
		}
	}
	For( i , 1 , n )if( Vis[1][i] ){
		Ct++;
		L[Ct][0] = 2;L[Ct][1] = i;
		while( Vis[1][i] && i <= n )Vis[1][i++] = 0;	
		R[Ct][0] = 2;R[Ct][1] = i-1;
	}
	For( i , 1 , n )if( Vis[2][i] ){
		Ct++;
		L[Ct][0] = R[Ct][0] = 1;L[Ct][1] = i;
		while( Vis[2][i] && i <= n )Vis[2][i++] = 0;
		R[Ct][1] = i-1;
	}
	For( i , 1 , Ct )printf("%d %d %d %d\n",L[i][0],L[i][1],R[i][0],R[i][1]);
	For( i , Ct + 1 , k )puts("0 0 0 0");
}
