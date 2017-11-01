#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}
template< typename Type >inline void printf( Type x ){
	if( x > 9 )printf( x / 10 );
	putchar( x % 10 + '0' );
}

typedef double DB;
#define mem( x ) memset( x , 0 , sizeof x )
static const int maxn = 1e3 + 10;
static const int maxm = maxn * maxn << 1;
static const DB eps = 1e-10;

int cases;
int n;

int A[maxn];
int B[maxn];
int C[maxn];

int sqr( int x ){ return x * x ; }
DB dist( int x , int y ){ return sqrt( sqr( A[x] - A[y] ) + sqr( B[x] - B[y] ) ) ; }

int cmp( DB x , DB y ){ return ( abs( x - y ) < eps ) ? 0 : ( x - y > 0 ? 1 : -1 ) ; }

int m;
struct edge{
	int x , y;DB z;
	bool operator < ( edge t ) const { return cmp( z , t.z ) == -1 ; }
}e[maxm];

int Fa[maxm];
int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
DB Dt[maxm];

void Ins( int x , int y , DB z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = z;
}

DB F[maxn];

void Dfs( int x , int f ){
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( y == f )continue;
		F[y] = max( F[x] , Dt[i] );
		Dfs( y , x );
	}
}

void Kruskal(){
	Ct = 0;mem( Ht );
	For( i , 1 , n )Fa[i] = i;
	sort( 1 + e , 1 + m + e );
	DB MST = 0 , ans = 0;
	For( i , 1 , m )
		if( Find( e[i].x ) != Find( e[i].y ) ){
			Fa[ Find( e[i].x ) ] = Find( e[i].y );
			Ins( e[i].x , e[i].y , e[i].z );Ins( e[i].y , e[i].x , e[i].z );
			MST += e[i].z;
		}
	
	For( i , 1 , n ){
		For( j , 1 , n )F[j] = 0;
		Dfs( i , 0 );
		For( j , 1 , n )if( j != i )
			ans = max( ans , ( C[i] + C[j] ) * 1.0 / ( MST - F[j] ) );
	}
	
	printf("%.2lf\n" , ans );
}

int main(){
	
	Read( cases );
	
	while( cases-- ){
		
		m = 0;
		
		Read( n );
		
		For( i , 1 , n ){
			Read( A[i] );Read( B[i] );Read( C[i] );
			For( j , 1 , i - 1 )
				e[ ++m ] = (edge){ i , j , dist( i , j ) };
		}
		
		Kruskal();
		
	}
	
	return 0;
}
