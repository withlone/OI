#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e5 +1;
static const int maxm = maxn << 1;
static const int maxx = 2e6;

int n , m , Cnt;
int v[maxn] , w[maxn];
int H[maxn] , Nt[maxm] , To[maxm] , Ct;
int Dep[maxn] , Fa[maxn][18];

int root[maxn];
int Ch[maxx][2] , Sz[maxx];
void modify( int pt , int &rt , int l , int r , int x ){
	Sz[rt = ++Ct] = Sz[pt] + 1;
	if( l == r )return;
	int mid = l + r >> 1;
	if( x <= mid )Ch[rt][1] = Ch[pt][1] , modify( Ch[pt][0] , Ch[rt][0] , l , mid , x );
	else Ch[rt][0] = Ch[pt][0] , modify( Ch[pt][1] , Ch[rt][1] , mid + 1 , r , x );
}

void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

int QLca( int x , int y ){
	if( Dep[x] < Dep[y] )swap( x , y );
	int delta = Dep[x] - Dep[y];
	For( i , 0 , 17 )
		if( delta & ( 1 << i ) )x = Fa[x][i];
	if( x == y )return x;
	Lop( i , 17 , 0 )
		if( Fa[x][i] != Fa[y][i] )x = Fa[x][i] , y = Fa[y][i];
	return Fa[x][0];
}

void Dfs( int x ){
	modify( root[ Fa[x][0] ] , root[x] , 1 , Cnt , v[x] );
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( y == Fa[x][0] )continue;
		Fa[y][0] = x;
		Dep[y] = Dep[x] + 1;
		Dfs( y );
	}
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Read( v[i] ) , w[i] = v[i];
	
	sort( 1 + w , 1 + n + w );
	Cnt = unique( 1 + w , 1 + n + w ) - w - 1;
	For( i , 1 , n )v[i] = lower_bound( 1 + w , 1 + Cnt + w , v[i] ) - w;
	
	For( i , 1 , n - 1 ){
		int x , y;
		Read( x );Read( y );
		Ins( x , y );Ins( y , x );
	}
	
	Ct = 0;
	Dep[1] = 1;
	Dfs( 1 );
	
	For( j , 1 , 17 )For( i , 1 , n )
		Fa[i][j] = Fa[ Fa[i][j - 1] ][j - 1];
	
	while( m-- ){
		int x , y , k;
		Read( x );Read( y );Read( k );
		int Lca = QLca( x , y );
		int rt1 = root[x] , rt2 = root[y] , rt3 = root[Lca] , rt4 = root[ Fa[Lca][0] ];
		int l = 1 , r = Cnt;
		while( l < r ){
			int mid = l + r >> 1;
			int tmp = Sz[ Ch[rt1][0] ] + Sz[ Ch[rt2][0] ] - Sz[ Ch[rt3][0] ] - Sz[ Ch[rt4][0] ];
			bool t = ( tmp < k );
			rt1 = Ch[rt1][t];rt2 = Ch[rt2][t];rt3 = Ch[rt3][t];rt4 = Ch[rt4][t];
			if( !t )r = mid;
			else l = mid + 1 , k -= tmp;
		}
		printf("%d\n",w[l]);
	}
	
	return 0;
}
