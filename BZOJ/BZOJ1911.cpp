#include<cstdio>

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

typedef long long LL;
static const int MAXN = 1e6 +1;

int n;LL A , B , C;
LL Sum[MAXN] , f[MAXN];
int Que[MAXN] , H , T;

LL Up( int x , int y ){
	return ( f[x] - B * Sum[x] + A * Sum[x] * Sum[x] ) - ( f[y] - B * Sum[y] + A * Sum[y] * Sum[y] );
}
LL Down( int x , int y ){
	return 2LL * A * ( Sum[x] - Sum[y] );
}

int main(){
	
	Read( n );Read( A );Read( B );Read( C );
	
	For( i , 1 , n ){
		Read( Sum[i] );Sum[i] += Sum[i-1];
		while( H < T && Sum[i] * Down( Que[H+1] , Que[H] ) <= Up( Que[H+1] , Que[H] ) )H++;
		f[i] = f[Que[H]] + A * ( Sum[i] - Sum[Que[H]] ) * ( Sum[i] - Sum[Que[H]] ) + B * ( Sum[i] - Sum[Que[H]] ) + C;
		while( H < T && Up( i , Que[T] ) * Down( Que[T] , Que[T-1] ) <= Up( Que[T] , Que[T-1] ) * Down( i , Que[T] ) )T--;
		Que[++T] = i;
	}
	
	printf("%lld\n",f[n]);
	
	return 0;
}
