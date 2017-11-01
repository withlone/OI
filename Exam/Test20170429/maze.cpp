#include<cstdio>
#include<algorithm>
using namespace std;

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 51;
#define For( i,l,r ) for( int i=l;i<=r;i++ )

int n,m;
int Mp[MAXN][MAXN];
int f[MAXN][MAXN][MAXN][MAXN];

int main(){
	
	freopen("maze.in","r",stdin);
	freopen("maze.out","w",stdout);
	Read( n );Read( m );
	For( i,1,n )For( j,1,m )Read( Mp[i][j] );
	
	For( x1,1,n )
		For( y1,1,m )
			For( x2,1,n )
				For( y2,1,m ){
					f[x1][y1][x2][y2] = 
					Mp[x1][y1] +
					max(
						max(
							f[x1-1][y1][x2][y2-1],
							f[x1][y1-1][x2-1][y2]
						),
						max(
							f[x1-1][y1][x2-1][y2],
							f[x1][y1-1][x2][y2-1]
						)
					);
					if( x1!=x2||y1!=y2 )f[x1][y1][x2][y2] += Mp[x2][y2];
				}
	printf("%d\n",f[n][m][n][m]);
	return 0;
}
