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

static const int maxn = 300 + 10;
static const int maxm = maxn * ( maxn + 1 );

int n;
int m;
int val[maxn];

struct edge{
	int x , y , z;
	bool operator < ( edge t ) const { return z < t.z ; }
}e[maxm];

int Fa[maxn];
int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int main(){
	
	scanf( n );
	
	For( i , 1 , n )scanf( val[i] ) , e[ ++m ] = (edge){ 0 , i , val[i] };
	
	For( i , 1 , n )
		For( j , 1 , n ){
			int x;
			scanf( x );
			if( i > j )e[ ++m ] = (edge){ i , j , x };
		}
	
	sort( 1 + e , 1 + m + e );
	
	For( i , 1 , n )Fa[i] = i;
	
	int MST = 0;
	
	For( i , 1 , m )
		if( Find( e[i].x ) != Find( e[i].y ) ){
			Fa[ Find( e[i].x ) ] = Find( e[i].y );
			MST += e[i].z;
		}
	
	printf( MST ) , putchar( '\n' );
	
	return 0;
}
