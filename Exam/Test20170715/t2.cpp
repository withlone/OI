#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 8e4 +1;
static const int maxm = maxn << 1;
static const int maxx = 3e7;

int n , m , u , v;
int val[maxn];

int H[maxn] , Nt[maxm] , To[maxm] , Ct;
int Dep[maxn] , Bn[maxn] , En[maxn] , Fa[maxn][18];

namespace president_tree{
	
	int Cnt;int Ch[maxx][2] , Sz[maxx];
	int Stk[maxx] , tp;
	
	void modify( int pt , int &rt , int l , int r , int x , int f ){
		if( !rt )rt = ( tp ? Stk[ tp-- ] : ++Cnt );
		Sz[rt] = Sz[pt] + f;
		if( l == r ){ if( !Sz[rt] )Stk[ ++tp ] = rt , rt = 0;return; }
		int mid = l + r >> 1;
		if( x <= mid )Ch[rt][1] = Ch[pt][1] , modify( Ch[pt][0] , Ch[rt][0] , l , mid , x , f );
		else Ch[rt][0] = Ch[pt][0] , modify( Ch[pt][1] , Ch[rt][1] , mid + 1 , r , x , f );
		if( !Sz[rt] && !Ch[rt][0] && !Ch[rt][1] )Stk[ ++tp ] = rt , rt = 0;
	}
	
}using namespace president_tree;

int root[maxn];

void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

void Dfs( int x ){
	Bn[x] = ++Ct;
	modify( root[ Fa[x][0] ] , root[x] , 1 , 1e9 , val[x] , 1 );
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( y == Fa[x][0] )continue;
		Fa[y][0] = x;
		Dep[y] = Dep[x] + 1;
		Dfs( y );
	}
	En[x] = Ct;
}

int QLca( int x , int y ){
	if( Dep[x] < Dep[y] )x ^= y ^= x ^= y;
	int delta = Dep[x] - Dep[y];
	For( i , 0 , 17 )
		if( delta & ( 1 << i ) )x = Fa[x][i];
	if( x == y )return x;
	Lop( i , 17 , 0 )
		if( Fa[x][i] != Fa[y][i] )x = Fa[x][i] , y = Fa[y][i];
	return Fa[x][0];
}

namespace BIT{
	
	int Rt[maxn];
	int work[2][maxn] , size[2];
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int x , int y , int f ){
		for( int i = x ; i <= n ; i += Lowbit( i ) )
			modify( Rt[i] , Rt[i] , 1 , 1e9 , y , f );
	}
	
	void Get( int x , int num ){
		for( int i = x ; i ; i -= Lowbit( i ) )
			work[num][ ++size[num] ] = Rt[i];
	}
	
	int Query( int k ){
		int l = 1 , r = 1e9;
		while( l < r ){
			int mid = l + r >> 1;
			LL sum[2];sum[0] = sum[1] = 0;
			For( i , 0 , 1 )For( j , 1 , size[i] )sum[i] += Sz[ Ch[ work[i][j] ][0] ];
			bool t = ( sum[0] - sum[1] < k );
			For( i , 0 , 1 )For( j , 1 , size[i] )work[i][j] = Ch[ work[i][j] ][t];
			if( !t )r = mid;
			else l = mid + 1 , k -= sum[0] - sum[1];
		}
		return l;
	}
	
}using namespace BIT;

int main(){
	
	freopen("t2.in","r",stdin);
	freopen("t2.out","w",stdout);
	
	Read( n );Read( m );
	For( i , 1 , n )Read( val[i] );
	For( i , 1 , n - 1 )Read( u ) , Read( v ) , Ins( u , v ) , Ins( v , u );
	
	Ct = 0;
	Dep[1] = 1;
	Dfs( 1 );
	
	For( j , 1 , 17 )For( i , 1 , n )
		Fa[i][j] = Fa[ Fa[i][j-1] ][j-1];
	
	while( m-- ){
		int opt , x , y;
		Read( opt );Read( x );Read( y );
		if( !opt ){
			Add( Bn[x] , val[x] , -1 );Add( En[x] + 1 , val[x] , 1 );
			val[x] = y;
			Add( Bn[x] , val[x] , 1 );Add( En[x] + 1 , val[x] , -1 );
		}
		else{
			int Lca = QLca( x , y ) , tot = Dep[x] + Dep[y] - Dep[Lca] - Dep[ Fa[Lca][0] ];
			if( tot < opt ){ puts("invalid request!") ; continue; }
			size[0] = size[1] = 0;
			Get( Bn[x] , 0 );Get( Bn[y] , 0 );
			Get( Bn[Lca] , 1 );Get( Bn[ Fa[Lca][0] ] , 1 );
			work[0][ ++size[0] ] = root[x];work[0][ ++size[0] ] = root[y];
			work[1][ ++size[1] ] = root[Lca];work[1][ ++size[1] ] = root[ Fa[Lca][0] ];
			printf("%d\n",Query( tot - opt + 1 ));
		}
	}
	
	return 0;
}
