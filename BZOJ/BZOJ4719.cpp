#include<cstdio>
#include<vector>
#include<cstring>
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

static const int maxn = 3e5 +1;
static const int maxm = maxn << 1;
static const int maxx = maxn << 3;

int n , m , u , v , Cnt , lim;

int W[maxn];
int S[maxn] , T[maxn];
int Dep[maxn] , Fa[maxn][21] , Lca[maxn];

int H[maxn] , Nt[maxm] , To[maxm] , Ct;

int num[maxn];
vector< int >_T[maxn] , _L[maxn];

int Stk[maxx] , tp;

int ans[maxn];

namespace preparation{
	
	void Ins( int x , int y ){
		Nt[ ++Ct ] = H[x];
		H[x] = Ct;
		To[Ct] = y;
	}
	
	void Dfs( int x ){
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
		For( i , 0 , 20 )
			if( delta & ( 1 << i ) )x = Fa[x][i];
		if( x == y )return x;
		Lop( i , 20 , 0 )
			if( Fa[x][i] != Fa[y][i] )x = Fa[x][i] , y = Fa[y][i];
		return Fa[x][0];
	}
	
	void Init(){
		Read( n );Read( m );lim = n << 1 | 1;
		For( i , 1 , n - 1 )Read( u ) , Read( v ) , Ins( u , v ) , Ins( v , u );
		For( i , 1 , n )Read( W[i] );
		For( i , 1 , m )Read( S[i] ) , Read( T[i] ) , num[ S[i] ]++ , _T[ T[i] ].push_back( i );
		Dep[1] = 1;
		Dfs( 1 );
		For( j , 1 , 20 )For( i , 1 , n )
			Fa[i][j] = Fa[ Fa[i][j-1] ][j-1];
		For( i , 1 , m )_L[ Lca[i] = QLca( S[i] , T[i] ) ].push_back( i );
	}
	
};

struct Segment_tree{
	
	int Sz[maxx];
	int root[maxn] , Ch[maxx][2];
	
	#define Lson Ch[rt][0] , l , mid
	#define Rson Ch[rt][1] , mid + 1 , r
	
	Segment_tree(){
		memset( Sz , 0 , sizeof Sz );
		memset( Ch , 0 , sizeof Ch );
		memset( root , 0 , sizeof root );
	}
	
	void del( int &rt ){ Stk[ ++tp ] = rt;Sz[rt] = Ch[rt][0] = Ch[rt][1] = 0;rt = 0; }
	
	int merge( int x , int y ){
		if( !( x * y ) )return x + y;
		Sz[x] += Sz[y];
		Ch[x][0] = merge( Ch[x][0] , Ch[y][0] );
		Ch[x][1] = merge( Ch[x][1] , Ch[y][1] );
		del( y );
		return x;
	}
	
	void Insert( int &rt , int l , int r , int x , int y ){
		if( !rt )rt = ( tp ? Stk[ tp-- ] : ++Cnt );
		Sz[rt] += y;int mid = l + r >> 1;
		return l == r ? void() : x <= mid ?
			Insert( Lson , x , y ) : Insert( Rson , x , y );
	}
	
	void Del( int &rt , int l , int r , int x ){
		Sz[rt]--;
		if( l == r ){
			if( !Sz[rt] )del( rt );
			return;
		}
		int mid = l + r >> 1;
		if( x <= mid )Del( Lson , x );else Del( Rson , x );
		if( !Sz[rt] )del( rt );
	}
	
	int Query( int rt , int l , int r , int x ){
		if( l == r || !rt )return !rt ? 0 : Sz[rt];
		int mid = l + r >> 1;
		return x <= mid ? Query( Lson , x ) : Query( Rson , x );
	}
	
}Tr[2];

namespace work_out{
	
	void Dfs( int x ){
		Rep( i , H[x] , Nt[i] ){
			int y = To[i];
			if( y == Fa[x][0] )continue;
			Dfs( y );
			Tr[0].root[x] = Tr[0].merge( Tr[0].root[x] , Tr[0].root[y] );
			Tr[1].root[x] = Tr[1].merge( Tr[1].root[x] , Tr[1].root[y] );
		}
		if( num[x] )Tr[0].Insert( Tr[0].root[x] , 1 , lim , Dep[x] , num[x] );
		For( i , 0 , _T[x].size() - 1 )Tr[1].Insert( Tr[1].root[x] , 1 , lim , Dep[ S[ _T[x][i] ] ] - ( Dep[ Lca[ _T[x][i] ] ] << 1 ) + n + 1 , 1 );
		ans[x] += Tr[0].Query( Tr[0].root[x] , 1 , lim , W[x] + Dep[x] );
		For( i , 0 , _L[x].size() - 1 )
			Tr[0].Del( Tr[0].root[x] , 1 , lim , Dep[ S[ _L[x][i] ] ] ) , 
			Tr[1].Del( Tr[1].root[x] , 1 , lim , Dep[ S[ _L[x][i] ] ] - ( Dep[ Lca[ _L[x][i] ] ] << 1 ) + n + 1 ) ;
		ans[x] += Tr[1].Query( Tr[1].root[x] , 1 , lim , W[x] - Dep[x] + n + 1 );
	}
	
};

int main(){
	
	preparation :: Init();
	
	work_out :: Dfs( 1 );
	
	printf("%d",ans[1]);
	For( i , 2 , n )printf(" %d",ans[i]);
	
	return 0;
}
