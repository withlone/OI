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

typedef long long LL;
typedef pair< int , int > par;
static const int maxn = 4e4 +1;
static const int maxm = maxn << 1;
static const int maxx = 150 * maxn;

int n , m , q , u , v;

int P[maxn];
int Px[maxn] , Py[maxn] , Pw[maxn];

int Qx[maxn] , Qy[maxn] , Qk[maxn];

int H[maxn] , Nt[maxm] , To[maxm] , Ct;

int Fa[maxn][17];
int Bn[maxn] , En[maxn] , Dep[maxn] , Cnt;

par Lca[maxn];

int ans[maxn];

struct Line{
	int x1 , x2 , y , f , id;
	bool operator < ( Line tmp ) const { return y < tmp.y || y == tmp.y && f > tmp.f ; }
}d[maxn * 5];

namespace preparation{
	
	void Ins( int x , int y ){
		Nt[ ++Ct ] = H[x];
		H[x] = Ct;
		To[Ct] = y;
	}
	
	void Dfs( int x ){
		Bn[x] = ++Cnt;
		Rep( i , H[x] , Nt[i] ){
			int y = To[i];
			if( y == Fa[x][0] )continue;
			Fa[y][0] = x;
			Dep[y] = Dep[x] + 1;
			Dfs( y );
		}
		En[x] = Cnt;
	}
	
	int QLca( int x , int y ){
		if( Dep[x] < Dep[y] )swap( x , y );
		int delta = Dep[x] - Dep[y];
		For( i , 0 , 16 )
			if( delta & ( 1 << i ) )x = Fa[x][i];
		if( x == y )return x;
		Lop( i , 16 , 0 )
			if( Fa[x][i] != Fa[y][i] )x = Fa[x][i] , y = Fa[y][i];
		return Fa[x][0];
	}
	
	void Init(){
		Read( n );Read( m );Read( q );
		For( i , 1 , n - 1 )Read( u ) , Read( v ) , Ins( u , v ) , Ins( v , u );
		For( i , 1 , m )Read( Px[i] ) , Read( Py[i] ) , Read( Pw[i] ) , P[i] = Pw[i];
		For( i , 1 , q )Read( Qx[i] ) , Read( Qy[i] ) , Read( Qk[i] );
		
		sort( 1 + P , 1 + m + P );
		Ct = unique( 1 + P , 1 + m + P ) - P - 1;
		
		Dep[1] = 1;
		Dfs( 1 );
		
		For( j , 1 , 16 )For( i , 1 , n )
			Fa[i][j] = Fa[ Fa[i][j-1] ][j-1];
		For( i , 1 , m )if( Bn[ Px[i] ] < Bn[ Py[i] ] )swap( Px[i] , Py[i] );
		For( i , 1 , q )if( Bn[ Qx[i] ] > Bn[ Qy[i] ] )swap( Qx[i] , Qy[i] );
		For( i , 1 , m ){
			Lca[i].first = QLca( Px[i] , Py[i] );
			if( Lca[i].first == Py[i] ){
				int delta = Dep[ Px[i] ] - Dep[ Py[i] ] - 1 , x = Px[i];
				For( j , 0 , 16 )
					if( delta & ( 1 << j ) )x = Fa[x][j];
				Lca[i].second = x;
			}
		}
	}
	
};

namespace president_tree{
	
	int root[maxn] , cnt;
	int Ch[maxx][2] , Sz[maxx];
	int Stk[maxx] , tp;
	
	void Del( int &rt ){ Stk[ ++tp ] = rt;Sz[rt] = Ch[rt][0] = Ch[rt][1] = 0;rt = 0; }
	
	void modify( int &rt , int l , int r , int x , int f ){
		if( !rt )rt = ( tp ? Stk[ tp-- ] : ++cnt );
		Sz[rt] += f;
		if( l == r ){ if( !Sz[rt] )Del( rt );return; }
		int mid = l + r >> 1;
		if( x <= mid )modify( Ch[rt][0] , l , mid , x , f );
		else modify( Ch[rt][1] , mid + 1 , r , x , f ) ;
		if( !Sz[rt] && !Ch[rt][0] && !Ch[rt][1] )Del( rt );
	}
	
}using namespace president_tree;

namespace BIT{
	
	int work[maxn] , size;
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int x , int y , int f ){
		for( ; x <= n ; x += Lowbit( x ) )
			modify( root[x] , 1 , Ct , y , f );
	}
	
	void Add( int x , int y , int z , int f ){ Add( x , z , f );Add( y + 1 , z , -f ); }
	
	void Get( int x ){
		for( size = 0; x ; x -= Lowbit( x ) )
			work[ ++size ] = root[x];
	}
	
	int Query( int k ){
		int l = 1 , r = Ct;
		while( l < r ){
			int mid = l + r >> 1;
			LL sum = 0;
			For( i , 1 , size )sum += Sz[ Ch[ work[i] ][0] ];
			bool p = ( sum < k );
			For( i , 1 , size )work[i] = Ch[ work[i] ][p];
			if( !p )r = mid;
			else l = mid + 1 , k -= sum;
		}
		return P[l];
	}
	
}using namespace BIT;

namespace working{
	
	void solve(){
		Cnt = 0;
		For( i , 1 , m ){
			if( Dep[ Lca[i].first ] < min( Dep[ Px[i] ] , Dep[ Py[i] ] ) ){
				if( Bn[ Px[i] ] > Bn[ Py[i] ] )swap( Px[i] , Py[i] );
				d[ ++Cnt ] = ( Line ){ Bn[ Px[i] ] , En[ Px[i] ] , Bn[ Py[i] ] , 1 , i } ;
				d[ ++Cnt ] = ( Line ){ Bn[ Px[i] ] , En[ Px[i] ] , En[ Py[i] ] , -1 , i } ;
			}
			else{
				if( Bn[ Px[i] ] < Bn[ Py[i] ] )swap( Px[i] , Py[i] );
				if( 1 <= Bn[ Lca[i].second ] - 1 ){
					d[ ++Cnt ] = ( Line ){ 1 , Bn[ Lca[i].second ] - 1 , Bn[ Px[i] ] , 1 , i };
					d[ ++Cnt ] = ( Line ){ 1 , Bn[ Lca[i].second ] - 1 , En[ Px[i] ] , -1 , i };
				}
				if( En[ Lca[i].second ] + 1 <= n ){
					d[ ++Cnt ] = ( Line ){ Bn[ Px[i] ] , En[ Px[i] ] , En[ Lca[i].second ] + 1 , 1 , i } ;
					d[ ++Cnt ] = ( Line ){ Bn[ Px[i] ] , En[ Px[i] ] , n , -1 , i };
				}
			}
		}
		
		For( i , 1 , q )d[ ++Cnt ] = ( Line ){ Bn[ Qx[i] ] , Bn[ Qx[i] ] , Bn[ Qy[i] ] , 0 , i };
		
		sort( 1 + d , 1 + Cnt + d );
		
		For( i , 1 , Cnt )
			if( !d[i].f ){
				Get( d[i].x1 );
				ans[ d[i].id ] = Query( Qk[ d[i].id ] );
			}
			else Add( d[i].x1 , d[i].x2 , lower_bound( 1 + P , 1 + Ct + P , Pw[ d[i].id ] ) - P , d[i].f );
	}
	
};

int main(){
	
	preparation :: Init();
	
	working :: solve();
	
	For( i , 1 , q )printf("%d\n",ans[i]);
	
	return 0;
}
