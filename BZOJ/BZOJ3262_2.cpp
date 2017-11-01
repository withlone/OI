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
static const int maxn = 1e5 +1;
static const int maxm = 2e6 +1;
static const int maxx = 17e6;

int n , m;
int num[maxn] , ans[maxn];
int Stk[maxn] , tp;

struct data{
	int x , y , z;
	bool operator <  ( data t ) const { return x < t.x || x == t.x && y < t.y || x == t.x && y == t.y && z < t.z; }
	bool operator == ( data t ) const { return x == t.x && y == t.y && z == t.z ; }
}Q[maxn];

namespace treap{
	
	int root[maxm] , Ct;
	int Sz[maxx] , Ch[maxx][2] , Fix[maxx] , Key[maxx];
	
	void Up( int rt ){ Sz[rt] = Sz[ Ch[rt][0] ] + Sz[ Ch[rt][1] ] + 1; }
	
	int merge( int x , int y ){
		return !( x * y ) ? x ^ y : Fix[x] < Fix[y] ?
			( Ch[x][1] = merge( Ch[x][1] , y ) , Up( x ) , x ) :
			( Ch[y][0] = merge( x , Ch[y][0] ) , Up( y ) , y ) ;
	}
	
	par Split( int x , int y ){
		if( !x )return make_pair( 0 , 0 );
		par p;
		if( Sz[ Ch[x][0] ] >= y ){
			p = Split( Ch[x][0] , y );
			Ch[x][0] = p.second;p.second = x;
		}
		else{
			p = Split( Ch[x][1] , y - Sz[ Ch[x][0] ] - 1 );
			Ch[x][1] = p.first;p.first = x;
		}
		return Up( x ) , p;
	}
	
	int Find( int rt , int x ){
		if( !rt )return 0;
		int p = rt , Res = 0;
		while( p )
			if( Key[p] >= x )p = Ch[p][0];
			else Res += Sz[ Ch[p][0] ] + 1 , p = Ch[p][1];
		return Res;
	}
	
	void Insert( int &rt , int x ){
		Key[ ++Ct ] =x;Fix[Ct] = rand();Sz[Ct] = 1;
		if( !rt )return rt = Ct , void();
		int t = Find( rt , x );
		par p = Split( rt , t );
		rt = merge( merge( p.first , Ct ) , p.second );
	}
	
	int Qrank( int rt , int x ){
		if( !rt )return 0;
		int p = rt , Res = 0;
		while( p )
			if( Key[p] > x )p = Ch[p][0];
			else Res += Sz[ Ch[p][0] ] + 1 , p = Ch[p][1];
		return Res;
	}
	
}using namespace treap;

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
	
	srand( time ( NULL ) );
	
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
