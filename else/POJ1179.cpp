#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

typedef long long LL;
static const int Inf  = 1e9;
static const int MAXN = 50;

int n;LL Ans;
int A[MAXN] , B[MAXN];
char Opt[MAXN] , C[MAXN];
bool Vmin[MAXN][MAXN] , Vmax[MAXN][MAXN];
LL fmax[MAXN][MAXN] , fmin[MAXN][MAXN] , Rec[MAXN];

LL Dp( int , int , int );

int main(){
	
	Ans = -1LL*Inf*Inf;
	scanf("%d",&n);
	For( i , 0 , n-1 )scanf("%s%d",&C[i],&B[i]);
	For( i , 0 , n-1 ){
		For( j , 0 , n-1 )A[j] = B[(i+j)%n] , Opt[j] = C[(i+j)%n];
		For( x , 0 , n-1 )For( y , 0 , n-1 )fmin[x][y] = Inf , fmax[x][y] = -Inf;
		memset( Vmin , 0 , sizeof Vmin );
		memset( Vmax , 0 , sizeof Vmax );
		For( j , 0 , n-1 )fmin[j][j] = fmax[j][j] = A[j] , Vmin[j][j] = Vmax[j][j] = 1;
		Ans = max( Ans , Rec[i] = Dp( 1 , 0 , n-1 ) );
	}
	
	printf("%lld\n",Ans);
	For( i , 0 , n-1 )
		if( Rec[i]==Ans )
			printf("%d ",i+1);
	puts("");
	return 0;
}

LL Dp( int p , int l , int r ){
	if( !p&& Vmin[l][r] )return fmin[l][r];
	if( p && Vmax[l][r] )return fmax[l][r];
	For( i , l , r-1 )
		if( Opt[i+1]=='t' ){
			fmin[l][r] = min( fmin[l][r] , Dp( 0,l,i ) + Dp( 0,i+1,r ) );
			fmax[l][r] = max( fmax[l][r] , Dp( 1,l,i ) + Dp( 1,i+1,r ) );
		}
		else{
			fmin[l][r] = min( fmin[l][r] ,
							min(
								min( Dp( 0,l,i )*Dp( 0,i+1,r ) , Dp( 1,l,i )*Dp( 1,i+1,r ) ),
								min( Dp( 0,l,i )*Dp( 1,i+1,r ) , Dp( 1,l,i )*Dp( 0,i+1,r ) )
								)
							);
			fmax[l][r] = max( fmax[l][r] ,
							max(
								max( Dp( 0,l,i )*Dp( 0,i+1,r ) , Dp( 1,l,i )*Dp( 1,i+1,r ) ),
								max( Dp( 0,l,i )*Dp( 1,i+1,r ) , Dp( 1,l,i )*Dp( 0,i+1,r ) )
								)
							);
		}
	Vmin[l][r] = Vmax[l][r] = 1;
	return p ? fmax[l][r] : fmin[l][r];
}
