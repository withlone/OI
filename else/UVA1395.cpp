#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

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

#define mem( x ) memset( x , 0 , sizeof x )
static const int maxn = 100 + 10;
static const int maxm = 5e3 + 10;

int n , m;

int Fa[maxn];
int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

struct edge{
	int x , y , z;
	bool operator < ( edge t ) const { return z < t.z ; }
}e[maxm];

int Kruskal(){
	
	int ans = 0x7fffffff;
	
	sort( 1 + e , 1 + m + e );
	
	For( j , 1 , m ){
		For( i , 1 , n )Fa[i] = i;
	
		int bottom = 0x7fffffff , top = 0 , num = 0;
		For( i , j , m )
			if( num == n - 1 )break;
			else if( Find( e[i].x ) != Find( e[i].y ) ){
				++num;
				Fa[ Find( e[i].x ) ] = Find( e[i].y );
				bottom = min( bottom , e[i].z );
				top = max( top , e[i].z );
			}
		if( num != n - 1 )return ans == 0x7fffffff ? -1 : ans;
		ans = min( ans , top - bottom );
	}
	return ans == 0x7fffffff ? -1 : ans;
}

int main(){
	
	while( scanf( n ) , scanf( m ) , n + m ){
		
		For( i , 1 , m ){
			int x , y , z;
			scanf( x );scanf( y );scanf( z );
			e[i] = (edge){ x , y , z };
		}
		
		printf( Kruskal() );
		putchar( '\n' );
		
	}
	
	return 0;
}
