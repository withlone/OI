#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

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

typedef double DB;
static const int maxn = 1e3 + 10;
static const DB eps = 1e-10;

int cmp( DB x , DB y ){ return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ; }

int n;
DB dis[maxn][maxn];

void read_in(){
	For( i , 1 , n )
		For( j , 1 , n )
			scanf( "%lf" , &dis[i][j] );
}

void Floyd(){
	For( k , 1 , n )
		For( i , 1 , n )
			For( j , 1 , n )
				dis[i][j] = max( dis[i][j] , dis[i][k] * dis[k][j] );
}

void display(){
	int q;
	scanf( q );
	while( q-- ){
		int x , y;
		scanf( x ) ; scanf( y ) ;
		if( !cmp( dis[x][y] , 0 ) )puts("What a pity!");
		else printf("%.3lf\n" , dis[x][y] );
	}
}

int main(){
	
	while( scanf( "%d" , &n ) != EOF ){
		
		read_in();
		
		Floyd();
		
		display();
		
	}
	
	return 0;
}
