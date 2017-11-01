#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef pair< int , int > par;
static const int maxn = 1e5 + 1;
static const int maxm = 2e6 + 1;
static const int maxx = 17e6;

int n , m;
int num[maxn] , ans[maxn];
int Stk[maxn] , tp;

struct data{
	int x , y , z;
	bool operator <  ( data t ) const { return x < t.x || x == t.x && y < t.y || x == t.x && y == t.y && z < t.z; }
	bool operator == ( data t ) const { return x == t.x && y == t.y && z == t.z ; }
}Q[maxn];

namespace Scapegoat{
	
	static const double OK = 0.75;
	
	int root[maxm] , Ct;
	int E[maxx] , top;
	int Sz[maxx] , Ch[maxx][2] , Fa[maxx] , Key[maxx];
	
	bool Bad( int rt ){ return max( Sz[ Ch[rt][0] ] , Sz[ Ch[rt][1] ] ) > Sz[rt] * OK + 4; }
	
	int GS( int x ){ return Ch[ Fa[x] ][1] == x ; }
	
	void Up( int rt ){ Sz[rt] = Sz[ Ch[rt][0] ] + Sz[ Ch[rt][1] ] + 1; }
	
	void Ergo( int x ){
		if( !x )return;
		Ergo( Ch[x][0] );E[ ++top ] = x;Ergo( Ch[x][1] );
	}
	
	int Build( int l , int r ){
		int mid = l + r >> 1 , rt = E[mid];
		Ch[rt][0] = Ch[rt][1] = 0;
		if( l < mid )Fa[ Ch[rt][0] = Build( l , mid - 1 ) ] = rt;
		if( mid < r )Fa[ Ch[rt][1] = Build( mid + 1 , r ) ] = rt;
		return Up( rt ) , rt;
	}
	
	void RBuild( int &rt , int x ){
		top = 0;Ergo( x );
		int fa = Fa[x] , p = GS( x );
		int t = Build( 1 , top );
		if( fa )Ch[fa][p] = t;
		Fa[t] = fa;
		if( rt == x )rt = t;
	}
	
	void Insert( int &rt , int x ){
		Sz[ ++Ct ] = 1;Key[Ct] = x;
		if( !rt )return rt = Ct , void();
		int p = rt;
		while( 1 ){
			++Sz[p];
			bool t = ( x > Key[p] );
			if( Ch[p][t] )p = Ch[p][t];
			else{
				Ch[p][t] = Ct;Fa[Ct] = p;
				break;
			}
		}
		x = 0;
		for( ; p ; p = Fa[p] )if( Bad( p ) )x = p;
		if( x )RBuild( rt , x );
	}
	
	int Qrank( int rt , int x ){
		int p = rt , Res = 0;
		while( p )
			if( Key[p] > x )p = Ch[p][0];
			else Res += Sz[ Ch[p][0] ] + 1 , p = Ch[p][1];
		return Res;
	}
	
}using namespace Scapegoat;

namespace BIT{
	
	int Lowbit( int x ){ return x & -x ; }
	
	void Add( int x , int y ){
		for( int i = x ; i <= m ; i += Lowbit( i ) )
			Insert( root[i] , y );
	}
	
	int Query( int x ){
		int Res = 0;
		for( int i = Q[x].y ; i ; i -= Lowbit( i ) )Res += Qrank( root[i] , Q[x].z );
		return Res;
	}
	
}using namespace BIT;

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Read( Q[i].x ) , Read( Q[i].y ) , Read( Q[i].z );
	
	sort( 1 + Q , 1 + n + Q );
	
	For( i , 1 , n ){
		if( Q[i] == Q[i + 1] )Stk[ ++tp ] = i;
		else{
			num[i] = Query( i );
			while( tp )num[ Stk[ tp-- ] ] = num[i];
		}
		Add( Q[i].y , Q[i].z );
	}
	
	For( i , 1 , n )ans[ num[i] ]++;
	
	For( i , 0 , n - 1 )printf("%d\n",ans[i]);
	
	return 0;
}
