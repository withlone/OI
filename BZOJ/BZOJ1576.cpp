#include<algorithm>
#include<cstring>
#include<vector>
#include<cstdio>
#include<queue>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

typedef pair< int , int > par;
static const int Inf = 0x7fffffff;
static const int maxn = 1e5 +1;
static const int maxm = 2e5 +1;
static const int maxx = maxn * 20;

int n , m , u , v , w , lim;

int H[maxn] , Nt[maxm << 1] , To[maxm << 1] , Dt[maxm << 1] , Ct;

int Fa[maxn] , Dep[maxn];

int ans[maxn];

namespace preparation{
	
	void Ins( int x , int y , int z ){
		Nt[ ++Ct ] = H[x];
		H[x] = Ct;
		To[Ct] = y;
		Dt[Ct] = z;
	}
	
	bool Vis[maxn];
	void Dijkstra( int s ){
		priority_queue< par , vector< par > , greater< par > >Hp;
		For( i , 2 , n )Dep[i] = Inf;
		Hp.push( make_pair( 0 , 1 ) );
		while( !Hp.empty() ){
			par t = Hp.top();Hp.pop();
			if( Vis[t.second] )continue;
			Vis[t.second] = true;
			Rep( i , H[t.second] , Nt[i] )
				if( Dep[ To[i] ] > t.first + Dt[i] && !Vis[ To[i] ] ){
					Dep[ To[i] ] = t.first + Dt[i];
					Fa[ To[i] ] = t.second;
					Hp.push( make_pair( Dep[ To[i] ] , To[i] ) );
				}
		}
	}
	
	int size[maxn] , Son[maxn] , Top[maxn] , Dept[maxn] , cnt;
	void Dfs( int x ){
		size[x] = 1;
		Rep( i , H[x] , Nt[i] ){
			int y = To[i];
			if( y == Fa[x] || Fa[y] != x )continue;
			Dept[y] = Dept[x] + 1;
			Dfs( y );
			size[x] += size[y];
			if( size[y] > size[ Son[x] ] )Son[x] = y;
		}
	}
	
	void Dfs( int x , int chain ){
		Top[x] = chain;
		if( Son[x] )Dfs( Son[x] , chain );
		Rep( i , H[x] , Nt[i] )
			if( To[i] != Fa[x] && Fa[ To[i] ] == x && To[i] != Son[x] )
				Dfs( To[i] , To[i] );
	}
	
	int Lca( int x , int y ){
		for( ; Top[x] != Top[y] ; x = Fa[ Top[x] ] )
			if( Dept[ Top[x] ] < Dept[ Top[y] ] )swap( x , y );
		return Dept[x] < Dept[y] ? x : y;
	}
	
	void Init(){
		Read( n );Read( m );
		For( i , 1 , m )Read( u ) , Read( v ) , Read( w ) , Ins( u , v , w ) , Ins( v , u , w ) , lim = max( lim , w );
		lim *= n << 1;
		Dijkstra( 1 );
		Dept[1] = 1;
		Dfs( 1 );
		Dfs( 1 , 1 );
	}
	
}using namespace preparation;

namespace Segment_tree{
	
	int root[maxn];
	int Sz[maxx] , Ch[maxx][2];
	int Stk[maxx] , tp , Cnt;
	
	void del( int &rt ){ Stk[ ++tp ] = rt;Ch[rt][0] = Ch[rt][1] = Sz[rt] = 0;rt = 0; }
	
	int merge( int x , int y ){
		if( !( x * y ) )return x ^ y;
		Sz[x] += Sz[y];
		Ch[x][0] = merge( Ch[x][0] , Ch[y][0] );
		Ch[x][1] = merge( Ch[x][1] , Ch[y][1] );
		del( y );
		return x;
	}
	
	void Insert( int &rt , int l , int r , int k ){
		if( !rt )rt = ( tp ? Stk[ tp-- ] : ++Cnt );
		Sz[rt]++;int mid = l + r >> 1;
		return l == r ? void() : k <= mid ?
			Insert( Ch[rt][0] , l , mid , k ) : Insert( Ch[rt][1] , mid + 1 , r , k );
	}
	
	void Del( int &rt , int l , int r , int k ){
		Sz[rt]--;
		if( l == r ){
			if( !Sz[rt] )del( rt );
			return;
		}
		int mid = l + r >> 1;
		if( k <= mid )Del( Ch[rt][0] , l , mid , k );
		else Del( Ch[rt][1] , mid + 1 , r , k );
		if( !Sz[rt] )del( rt );
	}
	
	int Query( int rt ){
		if( !Sz[rt] )return -1;
		int l = 1 , r = lim;
		while( l < r ){
			int mid = l + r >> 1;
			if( Sz[ Ch[rt][0] ] )rt = Ch[rt][0] , r = mid;
			else rt = Ch[rt][1] , l = mid + 1;
		}
		return l;
	}
	
}using namespace Segment_tree;

namespace working{
	
	vector< int >_Del[maxn];
	
	void Dfs( int x ){
		Rep( i , H[x] , Nt[i] ){
			int y = To[i];
			if( Fa[y] != x || y == Fa[x] )continue;
			Dfs( y );
			root[x] = merge( root[x] , root[y] );
		}
		if( x == 1 )return;
		Rep( i , H[x] , Nt[i] ){
			int y = To[i];
			if( Fa[y] == x || y == Fa[x] )continue;
			Insert( root[x] , 1 , lim , Dep[x] + Dt[i] + Dep[y] );
			_Del[ Lca( x , y ) ].push_back( Dep[x] + Dt[i] + Dep[y] );
		}
		For( i , 0 , _Del[x].size() - 1 )Del( root[x] , 1 , lim , _Del[x][i] );
		ans[x] = Query( root[x] ) - Dep[x];
	}
	
	void Display(){	For( i , 2 , n )printf("%d\n",Dep[i] == Inf ? 0 : ans[i] < 0 ? -1 : ans[i]); }
	
};

int main(){
	
	preparation :: Init();
	
	working :: Dfs( 1 );
	
	working :: Display();
	
	return 0;
}
