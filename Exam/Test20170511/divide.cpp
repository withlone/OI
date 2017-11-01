#include<cstdio>

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}
template< typename Type >inline Type max( Type x , Type y ){ return x>y?x:y; }

static const int MAXN = 1500 +1;
#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

int n,m,Ans;
int A[MAXN][MAXN],B[MAXN][MAXN];
int f[MAXN][MAXN];

void Init();
int Dp(){
	For( i , 1 , n )
		For( j , 1 , m ){
			if( i-1>=1&&j-1>=1 )f[i][j] = max( f[i][j] , f[i-1][j-1] + A[i-1][j] + B[i][j-1] );
			if( i-1>=1 )f[i][j] = max( f[i][j] , f[i-1][j] + B[i][j-1] );
			if( j-1>=1 )f[i][j] = max( f[i][j] , f[i][j-1] + A[i-1][j] );
		}
	return f[n][m];
}

#define Judge
int main(){
	
	#ifdef Judge
		freopen("divide.in","r",stdin);
		freopen("divide.out","w",stdout);
	#endif
	
	Init();
	
	printf("%d\n",Dp());
	return 0;
}

void Init(){
	Read( n );Read( m );
	For( i , 1 , n )For( j , 1 , m ){
		char ch=getchar();
		for( ;ch> 'Z'||ch< 'A';ch=getchar() );
		if( ch=='K' )Read( A[i][j] );
		else Read( B[i][j] );
	}
	For( i , 1 , n )For( j , 1 , m )B[i][j] += B[i][j-1],A[i][j] += A[i-1][j];
}
