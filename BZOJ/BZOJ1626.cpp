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
int m;
int A[maxn];
int B[maxn];

double sqr( DB x ){ return x * x ; }
DB dist( int x , int y ){ return sqrt( sqr( A[x] - A[y] ) + sqr( B[x] - B[y] ) ) ; }

int mct;

struct edge{
	int x , y ;DB z;
	bool operator < ( edge t ) const { return cmp( z , t.z ) == -1 ; }
}e[maxn * maxn];

int Fa[maxn];

int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

void read_in(){
	scanf( n ) ; scanf( m );
	For( i , 1 , n ){
		scanf( A[i] ) ; scanf( B[i] );Fa[i] = i;
		For( j , 1 , i - 1 )
			e[ ++mct ] = (edge){ i , j , dist( i , j ) };
	}
	For( i , 1 , m ){
		int x , y ;
		scanf( x ) ; scanf( y );
		Fa[ Find( x ) ] = Find( y );
	}
}

void kruskal(){
	sort( 1 + e , 1 + mct + e );
	DB MST = 0;
	For( i , 1 , mct )
		if( Find( e[i].x ) != Find( e[i].y ) ){
			Fa[ Find( e[i].x ) ] = Find( e[i].y );
			MST += e[i].z;
		}
	printf("%.2lf\n" , MST );
}

int main(){
	
	read_in();
	
	kruskal();
	
	return 0;
}
