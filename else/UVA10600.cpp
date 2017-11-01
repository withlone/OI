#include<cstdio>
#include<cstring>
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

static const int maxn = 100 + 10;
static const int maxm = 1e4 + 10;

int cases;
int n;
int m;

int mp[maxn][maxn];

struct edge{
	int x , y , z;
	bool operator < ( edge t ) const { return z < t.z ; }
}e[maxm];

int Fa[maxn];

int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int Ct;
int Ht[maxn];
int Nt[maxm << 1];
int To[maxm << 1];
int Dt[maxm << 1];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = z;
}

int F[maxn];

void Dfs( int x , int f ){
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( y == f )continue;
		F[y] = max( F[x] , Dt[i] );
		Dfs( y , x );
	}
}

int main(){
	
	scanf( cases );
	
	while( cases-- ){
		
		memset( mp , 0 , sizeof mp );
		
		scanf( n );scanf( m );
		
		For( i , 1 , m )
			scanf( e[i].x ) , scanf( e[i].y ) , scanf( e[i].z ) ,
			mp[ e[i].x ][ e[i].y ] = mp[ e[i].y ][ e[i].x ] = e[i].z;
		
		sort( 1 + e , 1 + m + e );
		
		Ct = 0;
		
		For( i , 1 , n )Fa[i] = i , Ht[i] = 0;
		
		int MST = 0 , SMST = 0x7fffffff;
		
		For( i , 1 , m )
			if( Find( e[i].x ) != Find( e[i].y ) ){
				Fa[ Find( e[i].x ) ] = Find( e[i].y );
				MST += e[i].z;
				Ins( e[i].x , e[i].y , e[i].z );
				Ins( e[i].y , e[i].x , e[i].z );
				mp[ e[i].x ][ e[i].y ] = mp[ e[i].y ][ e[i].x ] = 0;
			}
		
		For( i , 1 , n ){
			For( j , 1 , n )F[j] = 0;
			Dfs( i , 0 );
			For( j , 1 , n )if( i != j && mp[i][j] )
				SMST = min( SMST , MST - F[j] + mp[i][j] );
		}
		
		printf( MST ) , putchar( ' ' ) , printf( SMST ) , putchar( '\n' );
		
	}
	
	return 0;
}
