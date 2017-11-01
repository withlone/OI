#include<cstdio>
#include<algorithm>

using std :: sort;

#define For( i , _Begin , _End ) for( int i=(_Begin),i##END=(_End);i<=(i##END);i++ )

template< typename Type >inline Type max( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

static const int Inf = 0x7fffffff;
static const int MAXN = 1e4 +1;
static const int MAXM = 1e6 +1;
static const double OK = 0.75;

int n , m , Num;
int A[MAXN] , B[MAXN];

int E[MAXN] , tp;

int Fa[MAXM] , Ch[MAXM][2] , Key[MAXM] , Sz[MAXM];

struct Scapegoat{
	
	int Rt;
	
	bool Bad( int x ){ return max( Sz[Ch[x][0]] , Sz[Ch[x][1]] ) > Sz[x] * OK + 4; }
	
	void Up( int x ){ Sz[x] = Sz[Ch[x][0]] + Sz[Ch[x][1]] + 1; }
	
	int GS( int x ){ return x == Ch[Fa[x]][1]; }
	
	void Ergo( int x ){
		if( !x )return;
		Ergo( Ch[x][0] );
		E[ ++tp ] = x;
		Ergo( Ch[x][1] );
	}
	
	int Build( int l , int r ){
		int mid = l + r >> 1 , rt = E[ mid ];
		Ch[rt][0] = Ch[rt][1] = 0;Sz[rt] = 1;
		if( l < mid )Fa[ Ch[rt][0] = Build( l , mid - 1 ) ] = rt;
		if( mid < r )Fa[ Ch[rt][1] = Build( mid + 1 , r ) ] = rt;
		Up( rt );return rt;
	}
	
	void RBuild( int x ){
		tp = 0;Ergo( x );
		int fa = Fa[x] , p = GS( x );
		int rt = Build( 1 , tp );
		Fa[rt] = fa;
		if( fa )Ch[fa][p] = rt;
		if( Rt == x )Rt = rt;
	}
	
	int Qrank( int x ){
		int p = Rt , Res = 0;
		while( p )
			if( x <= Key[p] )p = Ch[p][0];
			else Res += Sz[Ch[p][0]] + 1 , p = Ch[p][1];
		return Res;
	}
	
	void Insert( int x ){
		if( !Rt ){ Rt = ++Num;Sz[Rt] = 1;Key[Rt] = x;return; }
		int p = Rt , fa = 0;
		Sz[++Num] = 1;Key[Num] = x;
		while( 1 ){
			Sz[ fa = p ]++;p = Ch[p][ x > Key[p] ];
			if( !p ){
				p = Num;
				Fa[ Ch[fa][ x > Key[fa] ] = p ] = fa;
				break;
			}
		}
		int rt = 0;
		for( ; p ; p = Fa[p] )if( Bad( p ) )rt = p;
		if( rt )RBuild( rt );
	}
	
	void Del( int x ){
		int p = Rt;
		while( 1 )
			if( Key[p] == x )break;
			else p = Ch[p][ x > Key[p] ];
		x = p;
		
		if( Ch[x][0] && Ch[x][1] ){
			p = Ch[x][0];
			while( Ch[p][1] )p = Ch[p][1];
			Key[x] = Key[p];x = p;
		}
		int Son = Ch[x][0] + Ch[x][1] , fa = Fa[x];p = GS( x );
		Fa[ Son ] = fa;
		if( fa )Ch[fa][p] = Son;
		for( ; fa ; fa = Fa[fa] )Sz[fa]--;
		if( Rt == x )Rt = Son;
	}
	
	int build( int l , int r ){
		int mid = l + r >> 1 , rt = ++Num;
		Key[rt] = A[mid];
		if( l < mid )Fa[ Ch[rt][0] = build( l , mid - 1 ) ] = rt;
		if( mid < r )Fa[ Ch[rt][1] = build( mid + 1 , r ) ] = rt;
		Up( rt );return rt;
	}
	
}tree[MAXN<<2];

namespace Segment_Tree{
	
	#define Lson rt<<1 , l , mid
	#define Rson rt<<1|1 , mid + 1 , r
	
	void Build( int rt , int l , int r ){
		For( i , l , r )B[i] = A[i];
		sort( l + A , r + 1 + A );
		tree[rt].Rt = tree[rt].build( l , r );
		For( i , l , r )A[i] = B[i];
		if( l == r )return;
		int mid = l + r >> 1;
		Build( Lson );Build( Rson );
	}
	
	int Get_Rank( int rt , int l , int r , int L , int R , int k ){
		if( l > R || r < L )return 0;
		if( l >= L && r <= R )return tree[rt].Qrank( k );
		int mid = l + r >> 1;
		return Get_Rank( Lson , L , R , k ) + Get_Rank( Rson , L , R , k );
	}
	
	int Get_Num( int L , int R , int k ){
		int l = 0 , r = Inf , Res;
		while( l <= r ){
			int mid = l + r >> 1;
			if( Get_Rank( 1 , 1 , n , L , R , mid ) + 1 <= k )Res = mid , l = mid + 1;
			else r = mid - 1;
		}
		return Res;
	}
	
	void Modify( int rt , int l , int r , int pos , int k ){
		tree[rt].Del( A[pos] );
		tree[rt].Insert( k );
		if( l == r )return;
		int mid = l + r >> 1;
		if( pos <= mid )Modify( Lson , pos , k );
		else Modify( Rson , pos , k );
	}
	
}using namespace Segment_Tree;

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Read( A[i] );
	
	Build( 1 , 1 , n );
	
	while( m-- ){
		int x , y , z;
		char ch = getchar();
		while( ch != 'Q' && ch != 'C' )ch = getchar();
		Read( x );Read( y );
		if( ch == 'C' )Modify( 1 , 1 , n , x , y ) , A[x] = y;
		else Read( z ) , printf("%d\n",Get_Num( x , y , z ));
	}
	
	return 0;
}
