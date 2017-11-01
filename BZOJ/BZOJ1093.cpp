#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e5 + 10;
static const int maxm = 1e6 + 10;

int n;
int m;
int mod;
int A[maxm];
int B[maxm];

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
}

bool V[maxn];

int tp;
int dct;
int cnt;
int bel[maxn];
int dfn[maxn];
int Low[maxn];
int size[maxn];
int stack[maxn];

void tarjan( int x ){
	int y;
	V[x] = true;
	stack[ ++tp ] = x;
	dfn[x] = Low[x] = ++dct;
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( !dfn[y] )tarjan( y ) , Low[x] = min( Low[x] , Low[y] );
		else if( V[y] )Low[x] = min( Low[x] , dfn[y] );
	}
	if( dfn[x] != Low[x] )return;
	++cnt;
	do{
		y = stack[ tp-- ];
		V[y] = false;
		bel[y] = cnt;
		size[cnt]++;
	}while( x != y );
}

int Sz[maxn];
int Idg[maxn];
int way[maxn];
int pre[maxn];
int dis[maxn];

void Dfs( int x ){
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( !dis[y] )Dfs( y );
		if( dis[y] + size[x] > dis[x] )
			way[x] = way[y] , dis[x] = dis[y] + size[x];
		else if( dis[y] + size[x] == dis[x] )
			way[x] = ( way[x] + way[y] ) % mod;
	}
	if( !Ht[x] )dis[x] = size[x] , way[x] = 1;
}

int main(){
	
	Read( n );Read( m );Read( mod );
	
	For( i , 1 , m ){
		int x , y;
		Read( x );Read( y );
		Ins( x , y );
		A[i] = x;B[i] = y;
	}
	
	For( i , 1 , n )if( !dfn[i] )
		tarjan( i );
	
	Ct = 0;
	For( i , 1 , n )V[i] = Ht[i] = 0;
	
	map< int , bool >mp[maxn];
	
	For( i , 1 , m )if( bel[ A[i] ] != bel[ B[i] ] && !mp[ bel[ A[i] ] ][ bel[ B[i] ] ] )
		Ins( bel[ A[i] ] , bel[ B[i] ] ) , Idg[ bel[ B[i] ] ]++ ,
		mp[ bel[ A[i] ] ][ bel[ B[i] ] ] = true;
	
	int ans = 0 , tot = 0;
	For( i , 1 , cnt )if( !dis[i] ){
		Dfs( i );
		if( dis[i] > ans )
			tot = way[i] , ans = dis[i];
		else if( dis[i] == ans )
			tot = ( tot + way[i] ) % mod;
	}
	
	printf("%d\n%d\n",ans , tot );
	
	return 0;
}
