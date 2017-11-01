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

static const int maxn = 100 + 10;
static const int maxm = 1e3 + 10;
static const int mod = 31011;

int n;
int m;

struct edge{
	int x , y , z ;
	bool operator < ( edge t ) const { return z < t.z ; }
}e[maxm];

void read_in(){
	scanf( n ) ; scanf( m );
	For( i , 1 , m )
		scanf( e[i].x ) , scanf( e[i].y ) , scanf( e[i].z );
}

int Fa[maxn];

int Find( int t ){ return t == Fa[t] ? t : Find( Fa[t] ) ; }

int cnt;
int num;
int L[maxm];
int R[maxm];
int v[maxm];

void kruskal(){
	sort( 1 + e , 1 + m + e );
	For( i , 1 , n )Fa[i] = i;
	For( i , 1 , m ){
		if( e[i].z != e[i - 1].z )
			R[cnt] = i - 1 , ++cnt , L[cnt] = i;
		int fx = Find( e[i].x ) , fy = Find( e[i].y );
		if( fx != fy )Fa[fx] = fy , v[cnt]++ , num++;
	}
	R[cnt] = m;
}

int ans = 1 ,  sum;

void Dfs( int i , int pos , int chosen ){
	if( pos == R[i] + 1 )
		return sum += ( chosen == v[i] ) , void();
	int fx = Find( e[pos].x ) , fy = Find( e[pos].y );
	if( fx != fy ){
		Fa[fx] = fy;
		Dfs( i , pos + 1 , chosen + 1 );
		Fa[fx] = fx;
	}
	Dfs( i , pos + 1 , chosen );
}

void calc(){
	For( i , 1 , n )Fa[i] = i;
	For( i , 1 , cnt ){
		sum = 0;
		Dfs( i , L[i] , 0 );
		ans = ( ans * sum ) % mod;
		For( j , L[i] , R[i] )
			if( Find( e[j].x ) != Find( e[j].y ) )
				Fa[ Find( e[j].x ) ] = Find( e[j].y );
	}
	printf( ans ) , putchar( '\n' );
}

int main(){
	
	read_in();
	
	kruskal();
	
	if( num != n - 1 )return puts("0") , 0;
	
	calc();
	
	return 0;
}
