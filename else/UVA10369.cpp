#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

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
static const int maxn = 500 + 10;
static const int maxm = maxn * maxn + 10;
static const DB eps = 1e-10;

int cmp( DB x , DB y ){ return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ; }

int cases;
int n;
int m;
int q;

int A[maxn];
int B[maxn];

struct edge{
	int x , y;DB z;bool chosen;
	bool operator < ( edge t ) const { return cmp( z , t.z ) == -1 ; }
}e[maxm];

int sqr( int x ){ return x * x ; }
DB dist( int x , int y ){ return sqrt( sqr( A[x] - A[y] ) + sqr( B[x] - B[y] ) ) ; }

int Fa[maxn];
bool V[maxn];

int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

void kruskal(){
	
	sort( 1 + e , 1 + m + e );
	
	For( i , 1 , n )Fa[i] = i;
	
	For( i , 1 , m )
		if( Find( e[i].x ) != Find( e[i].y ) ){
			Fa[ Find( e[i].x ) ] = Find( e[i].y );
			e[i].chosen = true;
		}
	
}

int main(){
	
	scanf( cases );
	
	while( cases-- ){
		
		m = 0;
		
		scanf( q );scanf( n );
		
		For( i , 1 , n ){
			scanf( A[i] ) , scanf( B[i] );
			For( j , 1 , i - 1 )
				e[ ++m ] = (edge){ i , j , dist( i , j ) , false };
		}
		
		kruskal();
		
		int num = 0;
		DB MST = 0;
		
		Lop( i , m , 1 )if( e[i].chosen ){
			if( num == q - 1 || !q ){
				MST = e[i].z;
				break;
			}
			else ++num;
		}
		
		printf("%.2lf\n" , MST );
		
	}
	
	return 0;
}
