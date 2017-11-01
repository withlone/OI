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
static const int maxm = 1e6 + 10;
static const DB eps = 1e-10;

int cmp( DB x , DB y ){ return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ; }

int n;
int m;
int q;
int A[maxn];
int B[maxn];

int sqr( int x ){ return x * x ; }
DB dist( int x , int y ){ return sqrt( sqr( A[x] - A[y] ) + sqr( B[x] - B[y] ) ) ; }

struct edge{
	int x , y;DB z;
	bool operator < ( edge t ) const { return cmp( z , t.z ) == -1 ; }
}e[maxm];

int Fa[maxn];

int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int main(){
	
	scanf( n );scanf( q );
	
	For( i , 1 , n ){
		scanf( A[i] ) , scanf( B[i] );
		For( j , 1 , i - 1 )
			e[ ++m ] = (edge){ i , j , dist( i , j ) };
	}
	
	sort( 1 + e , 1 + m + e );
	
	For( i , 1 , n )Fa[i] = i;
	
	int num = n + 1;
	
	For( i , 1 , m )
		if( Find( e[i].x ) != Find( e[i].y ) ){
			if( --num == q )return printf("%.2lf\n", e[i].z ) , 0;
			Fa[ Find( e[i].x ) ] = Find( e[i].y );
		}
	
	return 0;
}
