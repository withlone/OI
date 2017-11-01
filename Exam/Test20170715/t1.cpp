#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int Inf = 0x7fffffff;
static const int maxn = 1e3 +1;
static const int maxm = 1e6 +1;

int n , m;
int f[maxm];
bool ans[maxm];

struct data{
	int a , b , c;
	bool operator < ( data tmp ) const { return a < tmp.a ; }
}T[maxn];

struct Query{
	int x , y , z , id;
	bool operator < ( Query tmp ) const { return x < tmp.x ; }
}Q[maxm];

int main(){
	
	freopen("t1.in","r",stdin);
	freopen("t1.out","w",stdout);
	
	Read( n );
	For( i , 1 , n )Read( T[i].c ) , Read( T[i].a ) , Read( T[i].b );
	Read( m );
	For( i , 1 , m )Read( Q[i].x ) , Read( Q[i].y ) , Read( Q[i].z ) , Q[i].id = i;
	f[0] = Inf;
	
	sort( 1 + T , 1 + n + T );
	sort( 1 + Q , 1 + m + Q );
	
	int pos = 1;
	For( i , 1 , m ){
		for( ; pos <= n && T[pos].a <= Q[i].x ; pos++ )
			Lop( j , maxm / 10 , T[pos].c )
				f[j] = max( f[j] , min( T[pos].b , f[j - T[pos].c] ) );
		if( f[ Q[i].y ] > Q[i].x + Q[i].z )ans[ Q[i].id ] = true;
	}
	
	For( i , 1 , m )puts( ans[i] ? "TAK" : "NIE" );
	
	return 0;
}
