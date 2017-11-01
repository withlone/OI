#include<cstdio>

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )
 
template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

typedef long long LL;
static const int MAXN = 1e5 +1;

int n , k , In;
int pre[MAXN][201];
int Que[MAXN] , H , T;
LL Sum[MAXN] , f[MAXN] , g[MAXN];

void Dp();
void Init();
LL Sqr( LL );
LL Up( int , int );
LL Down( int , int );
void print( int , int );

int main(){
	
	Init();
	
	Dp();
	
	printf("%lld\n",f[n]);
	
	//print( n , k );
	
	return 0;
}

void Init(){
	Read( n );Read( k );
	For( i , 1 , n )Read( In ) , Sum[i] = Sum[i-1] + In;
}
LL Sqr( LL x ){ return x * x; }
LL Up( int x , int y ){ return ( g[y] - Sqr( Sum[y] ) ) - ( g[x] - Sqr( Sum[x] ) ); }
LL Down( int x , int y ){ return Sum[x] - Sum[y]; }
void Dp(){
	For( I , 1 , k ){
		H = 1;T = 0;
		Que[T] = I-1;
		For( i , I , n ){
			while( H < T && Up( Que[H+1] , Que[H] ) <= Sum[i] * Down( Que[H+1] , Que[H] ) )H++;
			f[i] = g[Que[H]] + Sum[Que[H]] * ( Sum[i] - Sum[Que[H]] );
			pre[i][I] = Que[H];
			while( H < T && Up( i , Que[T] ) * Down( Que[T] , Que[T-1] ) <= Up( Que[T] , Que[T-1] ) * Down( i , Que[T] ) )T--;
			Que[++T] = i;
		}
		For( i , 1 , n )g[i] = f[i];
	}
}
void print( int x , int Num ){
	if( !Num )return;
	print( pre[x][Num] , Num-1 );
	printf("%d ",pre[x][Num]);
}
