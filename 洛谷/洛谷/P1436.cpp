#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

static const int MAXN = 10;
static const int MAXM = 15;
typedef long long LL;
#define For( i,n ) for( int i=1;i<=n;i++ )
#define Rep( i,A,B ) for( int i=A;i<=B;i++ )

int n,N;
int A[MAXN][MAXN];
LL Sum[MAXN][MAXN];
LL f[MAXN][MAXN][MAXN][MAXN][MAXM];

LL Pow( int p ){ return p*p; }
LL Get( int x1,int y1,int x2,int y2 ){ return Pow( Sum[x2][y2] - Sum[x1-1][y2] - Sum[x2][y1-1] + Sum[x1-1][y1-1]); }

int main(){
	
	memset( f,30,sizeof f );
	N = 8;
	scanf("%d",&n);
	For( i,N )For( j,N ){
		scanf("%d",&A[i][j]);
		Sum[i][j] = Sum[i-1][j] + Sum[i][j-1] - Sum[i-1][j-1] + A[i][j];
	}
	For( x1,N )For( y1,N )Rep( x2,x1,N )Rep( y2,y1,N )f[x1][y1][x2][y2][0] = Get( x1,y1,x2,y2 );
	Rep( k,1,n-1 )
		For( x1,N )For( y1,N )
		Rep( x2,x1,N )
			Rep( y2,y1,N ){
				Rep( x,x1,x2-1 )
					f[x1][y1][x2][y2][k] = min(
						min(
						f[x1][y1][x][y2][k-1] + Get( x+1,y1,x2,y2 ),
						f[x+1][y1][x2][y2][k-1] + Get( x1,y1,x,y2 )
						),
						f[x1][y1][x2][y2][k]
					);
				Rep( y,y1,y2-1 )
					f[x1][y1][x2][y2][k] = min(
						min(
						f[x1][y1][x2][y][k-1] + Get( x1,y+1,x2,y2 ),
						f[x1][y+1][x2][y2][k-1] + Get( x1,y1,x2,y )
						),
						f[x1][y1][x2][y2][k]
					);
			}
	
	printf("%lld\n",f[1][1][N][N][n-1]);
	return 0;
}
