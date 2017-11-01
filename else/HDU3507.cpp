#include<cstdio>

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

typedef long long LL;
static const int MAXN = 5e5 +1;

int n , m;
int f[MAXN] , Sum[MAXN];
int Que[MAXN] , H , T;

int Pow( int x ){ return x*x; }

int Up( int x , int y ){
	return f[x] - f[y] + Pow( Sum[x] ) - Pow( Sum[y] );
}
int Down( int x , int y ){
	return 2 * ( Sum[x] - Sum[y] );
}

int main(){
	
	while( ~scanf("%d%d",&n,&m) ){
		H = T = 0;
		For( i , 1 , n ){
			Read( Sum[i] );Sum[i] += Sum[i-1];
			while( H < T && Up( Que[H+1] , Que[H] ) <= Sum[i]*Down( Que[H+1] , Que[H] ) )H++;
			f[i] = f[Que[H]] + m + Pow( Sum[i] - Sum[Que[H]] );
			while( H < T && Up( i , Que[T] )*Down( Que[T] , Que[T-1] ) <= Up( Que[T] , Que[T-1] )*Down( i , Que[T] ) )T--;
			Que[++T] = i;
		}
		printf("%d\n",f[n]);
	}
	return 0;
}
