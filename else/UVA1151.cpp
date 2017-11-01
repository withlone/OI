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

typedef long long LL;
static const int maxn = 1e3 + 10;
static const int maxm = 1e6 + 10;
static const int maxq = 10;

int cases;
int n;
int m;
int q;

int size[maxq];
int take[maxq];
int set[maxq][maxn];

int A[maxn];
int B[maxn];

int sqr( int x ){ return x * x ; }
int dist( int x , int y ){ return sqr( A[x] - A[y] ) + sqr( B[x] - B[y] ) ; }

struct edge{
	int x , y , z;
	bool operator < ( edge t ) const { return z < t.z ; }
}e[maxm];

int Fa[maxn];

int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int main(){
	
	bool first = 0;
	
	scanf( cases );
	
	while( cases-- ){
		
		m = 0;
		scanf( n );scanf( q );
		
		For( i , 1 , q ){
			scanf( size[i] );scanf( take[i] );
			For( j , 1 , size[i] )scanf( set[i][j] );
		}
		
		For( i , 1 , n ){
			scanf( A[i] );scanf( B[i] );
			For( j , 1 , i - 1 )
				e[ ++m ] = (edge){ i , j , dist( i , j ) };
		}
		
		LL ans = 1e15;
		
		sort( 1 + e , 1 + m + e );
		
		For( t , 0 , ( 1 << q ) - 1 ){
			
			LL MST = 0 , num = 0;
			
			For( i , 1 , n )Fa[i] = i;
			
			For( i , 1 , q )if( ( 1 << i - 1 ) & t ){
				MST += take[i];
				For( j , 2 , size[i] )
					if( Find( set[i][j] ) != Find( set[i][1] ) )
						Fa[ Find( set[i][j] ) ] = Find( set[i][1] ) , ++num;
			}
			
			For( i , 1 , m )
				if( num == n - 1 )break;
				else if( Find( e[i].x ) != Find( e[i].y ) ){
					Fa[ Find( e[i].x ) ] = Find( e[i].y );
					MST += e[i].z;
					++num;
				}
			
			if( num == n - 1 )ans = min( ans , MST );
		}
		
		printf( ans ) , putchar( '\n' );
		
		if( cases )putchar( '\n' );
		
	}
	
	return 0;
}
