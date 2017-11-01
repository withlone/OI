#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 100 + 10;

int n;
int m;

bool dis[maxn][maxn];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , m ){
		int x , y ;
		scanf( x ) ; scanf( y ) ;
		dis[x][y] = true;
	}
	For( i , 1 , n )dis[i][i] = true;
}

void Floyd(){
	For( k , 1 , n )
		For( i , 1 , n )
			For( j , 1 , n )
				dis[i][j] |= dis[i][k] & dis[k][j];
}

bool chk( int x ){
	For( i , 1 , n )
		if( !dis[i][x] && !dis[x][i] )return false;
	return true;
}

int calc(){
	int res = 0;
	For( i , 1 , n )res += chk( i );
	return res;
}

int main(){
	
	read_in();
	
	Floyd();
	
	printf("%d\n" , calc() );
	
	return 0;
}
