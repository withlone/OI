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

static const int maxn = 2e3 + 10;
static const int maxm = maxn * maxn;

int n;
int m;
int C;
int A[maxn];
int B[maxn];

int sqr( int x ){ return x * x ; }
int dist( int x , int y ){ return sqr( A[x] - A[y] ) + sqr( B[x] - B[y] ) ; }

struct edge{
	int x , y , z ;
	bool operator < ( edge t ) const { return z < t.z ; }
}e[maxm];

void read_in(){
	scanf( n ) ; scanf( C );
	For( i , 1 , n ){
		scanf( A[i] ) ; scanf( B[i] ) ;
		For( j , 1 , i - 1 )
			if( dist( i , j ) >= C )
				e[ ++m ] = (edge){ i , j , dist( i , j ) };
	}
}

int Fa[maxn];

int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

void kruskal(){
	sort( 1 + e , 1 + m + e );
	For( i , 1 , n )Fa[i] = i;
	int MST = 0 , num = 0;
	For( i , 1 , m )
		if( Find( e[i].x ) != Find( e[i].y ) ){
			Fa[ Find( e[i].x ) ] = Find( e[i].y ) ;
			MST += e[i].z;++num;
		}
	if( num != n - 1 )puts("-1");
	else printf("%d\n" , MST );
}

int main(){
	
	read_in();
	
	kruskal();
	
	return 0;
}
