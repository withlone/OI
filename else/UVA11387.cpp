#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 100 + 10;

void make( int n ){
	printf("%d\n",3 * n >> 1);
	For( i , 1 , n - 1 )printf("%d %d\n", i , i + 1 );
	printf("%d 1\n",n);
	printf("1 %d\n",( n >> 1 ) + 1);
	For( i , 2 , n >> 1 )printf("%d %d\n", i , n + 2 - i );
}

int main(){
	
	int n;
	
	while( Read( n ) , n )
		if( n & 1 || n <= 3 )puts("Impossible");
		else make( n );
	return 0;
}
