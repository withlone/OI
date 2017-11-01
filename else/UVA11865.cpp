#include<cstdio>
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

static const int maxn = 70;
static const int maxm = 1e4 + 10;

int cases;
int n;
int m;
int cost;

struct edge{ int x , y , c1 , c2; }e[maxm] , d[maxm];

bool cmp1( edge x , edge y ){ return x.c1 < y.c1 ; }
bool cmp2( edge x , edge y ){ return x.c2 < y.c2 ; }

int in[maxn];
int Fa[maxn];
int pre[maxn];
int bel[maxn];
int Idg[maxn];
bool V[maxn];

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
}

void Dfs( int x ){
	V[x] = true;
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( !V[y] )Dfs( y );
	}
}

int LZ( int N , int M ){
	int res = 0;Ct = 0;
	For( i , 1 , N )Ht[i] = 0;
	For( i , 1 , M )Ins( d[i].x , d[i].y );
	For( i , 1 , N ){
		For( j , 1 , N )V[j] = false;
		Dfs( i );
		bool flag = 1;
		For( j , 1 , N )if( !V[j] )flag = 0;
		res |= flag;
	}
	if( !res )return cost + 1;
	res = 0;
	while( true ){
		
		For( i , 1 , N )in[i] = 1e6 , pre[i] = bel[i] = Fa[i] = 0;
		
		For( i , 1 , M )
			if( d[i].x != d[i].y && in[ d[i].y ] > d[i].c2 )
				pre[ d[i].y ] = d[i].x , in[ d[i].y ] = d[i].c2;
		
		int temp = 0;
		For( i , 1 , N )if( !pre[i] )++temp;
		if( temp > 1 )return cost + 1;
		
		int p = 1;
		if( temp == 1 )For( i , 1 , N )if( !pre[i] )p = i;
		else For( i , 2 , N )if( in[i] > in[p] )p = i;
		bel[p] = 1;
		
		int cnt = 1;
		
		For( i , 1 , N )if( i != p ){
			res += in[i];
			int x = i , y = i;
			while( !bel[x] && x != p && Fa[x] != y )Fa[x] = y , x = pre[x];
			if( !bel[x] && x != p ){
				++cnt;y = x;
				do{
					bel[y] = cnt;
					y = pre[y];
				}while( x != y );
			}
		}
		
		if( cnt == 1 )return res;
		
		For( i , 1 , N )if( !bel[i] )bel[i] = ++cnt;
		N = cnt;
		
		For( i , 1 , M ){
			if( d[i].y != p )d[i].c2 -= in[ d[i].y ];
			d[i].x = bel[ d[i].x ];d[i].y = bel[ d[i].y ];
		}
		
	}
}

int main(){
	
	scanf( cases );
	
	while( cases-- ){
		
		scanf( n );scanf( m );scanf( cost );
		
		For( i , 1 , n )Idg[i] = 0;
		
		For( i , 1 , m )
			scanf( e[i].x ) , scanf( e[i].y ) , scanf( e[i].c1 ) , scanf( e[i].c2 ) ,
			++e[i].x , ++e[i].y , Idg[ e[i].y ]++;
		
		sort( 1 + e , 1 + m + e , cmp1 );
		
		int l = 1 , r = m , ans = -1;
		
		while( l <= r ){
			int mid = l + r >> 1;
			For( i , mid , m )d[ i - mid + 1 ] = e[i];
			if( LZ( n , m - mid + 1 ) <= cost )l = mid + 1 , ans = mid;
			else r = mid - 1;
		}
		
		if( ans == -1 )puts("streaming not possible.");
		else printf( e[ans].c1 ) , puts(" kbps");
		
	}
	
	return 0;
}
