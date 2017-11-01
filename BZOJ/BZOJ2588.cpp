#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

static const int maxn = 1e5 +1;
static const int maxm = maxn << 1;
static const int maxx = 3e6;

int n , m , u , v , Cnt , ans;
int A[maxn] , val[maxn];

int H[maxn] , Nt[maxm] , To[maxm] , Ct;
int Fa[maxn][18] , Dep[maxn];

int root[maxn];
int Ch[maxx][2] , Sz[maxx];

void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

void modify( int pt , int &rt , int l , int r , int x ){
	Sz[ rt = ++Cnt ] = Sz[pt] + 1;
	if( l == r )return;
	int mid = l + r >> 1;
	if( x <= mid )Ch[rt][1] = Ch[pt][1] , modify( Ch[pt][0] , Ch[rt][0] , l , mid , x );
	else Ch[rt][0] = Ch[pt][0] , modify( Ch[pt][1] , Ch[rt][1] , mid + 1 , r , x );
}

void Dfs( int x ){
	modify( root[ Fa[x][0] ] , root[x] , 1 , Ct , lower_bound( 1 + A , 1 + Ct + A , val[x] ) - A );
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( y == Fa[x][0] )continue;
		Fa[y][0] = x;
		Dep[y] = Dep[x] + 1;
		Dfs( y );
	}
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

int Query( int x , int y , int k ){
	int Lca = QLca( x , y ) , fa = Fa[Lca][0];
	int l = 1 , r = Ct;
	x = root[x];y = root[y];Lca = root[Lca];fa = root[fa];
	while( l < r ){
		int mid = l + r >> 1;
		int sum = Sz[ Ch[x][0] ] + Sz[ Ch[y][0] ] - Sz[ Ch[Lca][0] ] - Sz[ Ch[fa][0] ];
		bool t = ( sum < k );
		x = Ch[x][t];y = Ch[y][t];Lca = Ch[Lca][t];fa = Ch[fa][t];
		if( !t )r = mid;
		else l = mid + 1 , k -= sum;
	}
	return A[l];
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Read( val[i] ) , A[i] = val[i];
	For( i , 1 , n - 1 )Read( u ) , Read( v ) , Ins( u , v ) , Ins( v , u );
	
	sort( 1 + A , 1 + n + A );
	Ct = unique( 1 + A , 1 + n + A ) - A - 1;
	
	Dep[1] = 1;
	Dfs( 1 );
	
	For( j , 1 , 17 )For( i , 1 , n )
		Fa[i][j] = Fa[ Fa[i][j-1] ][j-1];
	
	while( m-- ){
		int x , y , z;
		Read( x );Read( y );Read( z );x ^= ans;
		printf("%d",ans = Query( x , y , z ));
		if( m )puts("");
	}
	
	return 0;
}
