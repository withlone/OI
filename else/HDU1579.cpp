#include<cstdio>

template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}
template< typename Type >inline void printf( Type x ){
	if( x < 0 )putchar( '-' ) , x = -x;
	if( x > 9 )printf( x / 10 );
	putchar( x % 10 + '0' );
}

static const int maxn = 21;

int f[maxn][maxn][maxn];

int w( int a , int b , int c ){
	if( a <= 0 || b <= 0 || c <= 0 )return 1;
	if( a > 20 || b > 20 || c > 20 )return w( 20 , 20 , 20 );
	if( f[a][b][c] )return f[a][b][c];
	if( a < b && b < c )
		return f[a][b][c] = ( w( a , b , c - 1 ) +  w( a , b - 1 , c - 1 ) - w( a , b - 1 , c ) );
	return f[a][b][c] = ( w( a - 1 , b , c ) + w( a - 1 , b - 1 , c )
	 + w( a - 1 , b , c - 1 ) - w( a - 1 , b - 1 , c - 1) );
}

int main(){
	
	int x , y , z;
	while( scanf( "%d%d%d" , &x , &y , &z ) != EOF && x + y + z != -3 )
		printf("w(%d, %d, %d) = %d\n", x , y , z , w( x , y , z ) );
	
	return 0;
}
