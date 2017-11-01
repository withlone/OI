#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

typedef long long LL;
static const int Inf = 1e8;
static const int MAXN = 13;
static const int MAXM = 10;

int n;LL In;
LL Sum[MAXM][MAXM];
LL f[MAXN][MAXM][MAXM][MAXM][MAXM];

LL Get( int x1 , int y1 , int x2 , int y2 ){
	return Sum[x2][y2] - Sum[x2][y1-1] - Sum[x1-1][y2] + Sum[x1-1][y1-1];
}
LL Pow( LL x ){ return x*x; }

#define Judge

int main(){
	
	#ifdef Judge
		freopen("chessboard.in","r",stdin);
		freopen("chessboard.out","w",stdout);
	#endif
	
	Read( n );
	
	For( i , 1 , 8 )For( j , 1 , 8 ){
		Read( In );
		Sum[i][j] = In + Sum[i-1][j] + Sum[i][j-1] - Sum[i-1][j-1];
	}
	
	For( x2 , 1 , 8 )
		For( y2 , 1 , 8 )
			For( x1 , 1 , x2 )
				For( y1 , 1 , y2 )
					f[1][x1][y1][x2][y2] = Pow( Get( x1 , y1 , x2  ,y2 ) );
	
	For( k , 2 , n )
		For( x2 , 1 , 8 )
			For( y2 , 1 , 8 )
				For( x1 , 1 , x2 )
					For( y1 , 1 , y2 ){
						f[k][x1][y1][x2][y2] = Inf;
						For( x , x1 , x2-1 )
							f[k][x1][y1][x2][y2] = min(
								f[k][x1][y1][x2][y2],
								min(
									f[k-1][x1][y1][x][y2] + Pow( Get( x+1 , y1 , x2 , y2 ) ),
									f[k-1][x+1][y1][x2][y2] + Pow( Get( x1 , y1 , x , y2 ) )
								)
							);
						
						For( y , y1 , y2-1 )
							f[k][x1][y1][x2][y2] = min(
								f[k][x1][y1][x2][y2],
								min(
									f[k-1][x1][y1][x2][y] + Pow( Get( x1 , y+1 , x2 , y2 ) ),
									f[k-1][x1][y+1][x2][y2] + Pow( Get( x1 , y1 , x2 , y ) )
								)
							);
					}
	
	double Ans = f[n][1][1][8][8]*1.0/n - 1.0*Pow( Sum[8][8] )/Pow( n );
	
	printf("%.3lf\n",sqrt( Ans ));
	
	return 0;
}
/*
In
3
1 1 1 1 1 1 1 3
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 0
1 1 1 1 1 1 0 3

Out
1.633
*/
