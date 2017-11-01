#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 100 + 10;
static const int maxm = 10000 + 10;

int T , n , m , MST;

int Fa[maxn];
int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int mp[maxn][maxn];

struct edge{
	int x , y , z;
	bool operator < ( edge t ) const { return z < t.z ; }
}E[maxm];

int H[maxn] , Nt[maxm] , To[maxm] , Dt[maxm] , Ct;
void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = z;
}

bool V[maxn];
int F[maxn];
void Dfs( int x ){
	V[x] = true;
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( V[y] )continue;
		F[y] = max( F[x] , Dt[i] );
		Dfs( y );
	}
}

bool work(){
	int res = 0x7fffffff;
	For( i , 1 , n ){
		
		memset( F , 0 , F );
		memset( V , 0 , V );
		Dfs( i );
		
		For( j , 1 , n )if( mp[i][j] != -1 ){
			if( F[j] == mp[i][j] )return true;
			res = min( res , MST - F[j] + mp[i][j] );
		}
		
	}
	return false;
}

int main(){

	Read( T );
	
	while( T-- ){
		
		MST = Ct = 0;
		
		Read( n );Read( m );
		
		For( i , 1 , n )Fa[i] = i , H[i] = 0;
		
		For( i , 1 , m )Read( E[i].x ) , Read( E[i].y ) , Read( E[i].z );
		
		sort( 1 + E , 1 + m + E );
		
		memset( mp , -1 , sizeof mp );
		
		For( i , 1 , m )
			if( Find( E[i].x ) != Find( E[i].y ) ){
				MST += E[i].z;
				Fa[ Find( E[i].x ) ] = Find( E[i].y );
				Ins( E[i].x , E[i].y , E[i].z );
				Ins( E[i].y , E[i].x , E[i].z );
			}
			else mp[ E[i].x ][ E[i].y ] = mp[ E[i].y ][ E[i].x ] = E[i].z;
		
		if( work() )puts("Not Unique!");
		else printf("%d\n",MST);
	}
	
	return 0;
}
