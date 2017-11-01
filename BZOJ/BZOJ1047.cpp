#include<cstdio>

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}
template< typename Type >inline Type min ( Type x,Type y ){ return x<y?x:y; }

static const int MAXN = 1e3 +1;
#define For( i,_Begin,_End ) for( int i=_Begin;i<=_End;i++ )

int n,m,k;
int A[MAXN][MAXN],Mx[MAXN][MAXN],Mn[MAXN][MAXN];
int Max[MAXN][MAXN],Min[MAXN][MAXN];
int Que[MAXN],H,T;

int main(){
	
	Read( n );Read( m );Read( k );
	For( i , 1 , n )For( j , 1 , m )Read( A[i][j] );
	For( i , 1 , n ){
		H = T = 0;
		For( j , 1 , m ){
			while( H<=T&&A[i][Que[T]]<=A[i][j] )T--;
			Que[++T] = j;
			while( H<=T&&Que[H]<=j-k )H++;
			Mx[i][j] = A[i][Que[H]];
		}
		H = T = 0;
		For( j , 1 , m ){
			while( H<=T&&A[i][Que[T]]>=A[i][j] )T--;
			Que[++T] = j;
			while( H<=T&&Que[H]<=j-k )H++;
			Mn[i][j] = A[i][Que[H]];
		}
	}
	
	For( j , 1 , m ){
		H = T = 0;
		For( i , 1 , n ){
			while( H<=T&&Mx[Que[T]][j]<=Mx[i][j] )T--;
			Que[++T] = i;
			while( H<=T&&Que[H]<=i-k )H++;
			Max[i][j] = Mx[Que[H]][j];
		}
		H = T = 0;
		For( i , 1 , n ){
			while( H<=T&&Mn[Que[T]][j]>=Mn[i][j] )T--;
			Que[++T] = i;
			while( H<=T&&Que[H]<=i-k )H++;
			Min[i][j] = Mn[Que[H]][j];
		}
	}
	
	int Ans = 0x7fffffff;
	For( i , k , n )For( j , k , m )Ans = min( Ans , Max[i][j]-Min[i][j] );
	printf("%d\n",Ans);
	return 0;
}
