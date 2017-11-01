#include<cstdio>

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

typedef long long LL;
static const int MAXN = 5e4 +1;

int n , L;
LL f[MAXN] , Sum[MAXN];
int Que[MAXN] , H , T;

LL Pow( LL x ){ return x*x; }

LL Up( LL x , LL y ){
	return ( f[x] + Pow( x + Sum[x] ) ) - ( f[y] + Pow( y + Sum[y] ) );
}
LL Down( LL x , LL y ){
	return 2 * ( x + Sum[x] - y - Sum[y] );
}

int main(){
	
	Read( n );Read( L );
	
	For( i , 1 , n ){
		Read( Sum[i] );Sum[i] += Sum[i-1];
		LL y = i - 1 + Sum[i] - L;
		while( H < T && Up( Que[H+1] , Que[H] ) <= y * Down( Que[H+1] , Que[H] ) )H++;
		int j = Que[H];
		f[i] = f[j] + Pow( i - j - 1 + Sum[i] - Sum[j] - L );
		while( H < T && Up( i , Que[T] )*Down( Que[T] , Que[T-1] ) <= Up( Que[T] , Que[T-1] )*Down( i , Que[T] ) )T--;
		Que[++T] = i;
	}
	
	printf("%lld\n",f[n]);
	
	return 0;
}
