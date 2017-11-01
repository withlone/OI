#include<cstdio>

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

typedef long long LL;
static const int MAXS = 20;
static const int Mod  = 1000000001;
static const int MAXN = 1e5 +1;

int n;LL Ans = 1;
int A[MAXS][MAXS] , f[MAXS][MAXN] , B[MAXS] , Bin[MAXS];
bool Vis[MAXN];

int Dp( int );

int main(){
	
	Bin[0] = 1;
	For( i , 1 , MAXS - 1 )Bin[i] = Bin[i-1] << 1;
	
	Read( n );
	
	For( i , 1 , n )if( !Vis[i] )
		Ans = Ans * Dp( i ) % Mod;
	
	printf("%lld\n",Ans);
	
	return 0;
}

int Dp( int x ){
	A[1][1] = x;
	For( i , 2 , 18 )
		if( A[i-1][1] << 1 <= n )A[i][1] = A[i-1][1] << 1;
		else A[i][1] = n + 1;
	For( i , 1 , 18 )
		For( j , 2 , 11 )
			if( A[i][j-1] * 3 <= n )A[i][j] = A[i][j-1] * 3;
			else A[i][j] = n + 1;
	For( i , 1 , 18 ){
		B[i] = 0;
		For( j , 1 , 11 )
			if( A[i][j] <= n )B[i] += Bin[j-1] , Vis[A[i][j]] = true;
			else break;
	}
	For( i , 0 , 18 )
		For( j , 0 , B[i] )
			f[i][j] = 0;
	f[0][0] = 1;
	For( i , 0 , 17 )
		For( j , 0 , B[i] )
			if( !( j & ( j >> 1 ) ) && f[i][j] )
				For( k , 0 , B[i+1] )
					if( !( j & k ) )
						f[i+1][k] = ( f[i+1][k] + f[i][j] ) % Mod;
	return f[18][0];
}
