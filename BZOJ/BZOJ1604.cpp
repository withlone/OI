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

typedef pair< int , int > par;
static const int maxn = 1e5 + 10;
static const int Inf = 2e9;

int n;
int m;
int C;

struct point{
	int x , y , id;
	bool operator < ( point t ) const { return x == t.x ? y < t.y : x < t.x; }
}pnt[maxn];

void read_in(){
	scanf( n ) ; scanf( C );
	For( i , 1 , n )
		scanf( pnt[i].x ) , scanf( pnt[i].y ) , pnt[i].id = i;
}

bool operator < ( par x , par y ){ return x.first < y.first ; }
bool operator > ( par x , par y ){ return x.first > y.first ; }

namespace BIT{
	
	par T[maxn];
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int x , par y ){
		for( int i = x ; i ; i -= Lowbit( i ) )
			if( T[i] > y )T[i] = y;
	}
	
	int Query( int x ){
		par res = make_pair( Inf , -1 );
		for( int i = x ; i <= n ; i += Lowbit( i ) )
			if( res > T[i] )res = T[i];
		return res.second;
	}
	
}

int dce[maxn] , cnt ;

void discretization(){
	For( i , 1 , cnt = n )dce[i] = pnt[i].y - pnt[i].x;
	sort( 1 + dce , 1 + cnt + dce );
	cnt = unique( 1 + dce , 1 + cnt + dce ) - dce - 1;
}

int hash( int x ){ return lower_bound( 1 + dce , 1 + cnt + dce , x ) - dce ; }

int abs( int x ){ return x > 0 ? x : -x ; }

int dist( int x , int y ){ return abs( pnt[x].x - pnt[y].x ) + abs( pnt[x].y - pnt[y].y ) ; }

struct edge{
	int x , y , z;
	bool operator < ( edge t ) const { return z < t.z ; }
}e[maxn << 2];

void build_edge(){
	using namespace BIT;
	For( way , 1 , 4 ){
		if( !( way & 1 ) )
			For( i , 1 , n )pnt[i].y = -pnt[i].y;
		else if( way == 3 )
			For( i , 1 , n )swap( pnt[i].x , pnt[i].y );
		
		sort( 1 + pnt , 1 + n + pnt );
		
		discretization();
		
		For( i , 1 , n )T[i] = make_pair( Inf , -1 );
		
		Lop( i , n , 1 ){
			int x = hash( pnt[i].y - pnt[i].x );
			int y = Query( x );
			if( y != -1 )e[ ++m ] = (edge){ pnt[i].id , pnt[y].id , dist( i , y ) };
			Add( x , make_pair( pnt[i].x + pnt[i].y , i ) );
		}
		
	}
}

int size[maxn];

int Fa[maxn];

int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

void kruskal(){
	For( i , 1 , n )Fa[i] = i;
	sort( 1 + e , 1 + m + e );
	For( i , 1 , m )
		if( e[i].z > C )break;
		else Fa[ Find( e[i].x ) ] = Find( e[i].y ) ;
	int tot = 0 , ans = 0;
	For( i , 1 , n )size[ Find( i ) ]++;
	For( i , 1 , n )if( Find( i ) == i )++tot , ans = max( ans , size[i] );
	printf("%d %d\n" , tot , ans );
}

int main(){
	
	read_in();
	
	build_edge();
	
	kruskal();
	
	return 0;
}
