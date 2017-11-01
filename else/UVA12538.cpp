#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using std :: pair;
using std :: make_pair;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

typedef pair< int , int > par;
static const int maxn = 5e6 +1;

int n , dit , edit;
char s[maxn];

namespace treap{
	
	int Cnt;int root[maxn];
	char Key[maxn];
	int Fix[maxn] , Ch[maxn][2] , Sz[maxn];
	int Stk[maxn] , tp;
	
	void Up( int rt ){ Sz[rt] = Sz[ Ch[rt][0] ] + Sz[ Ch[rt][1] ] + 1; }
	
	int Build(){
		For( i , 0 , strlen( s ) - 1 ){
			Key[ ++Cnt ] = s[i];
			Fix[Cnt] = rand();
			Sz[Cnt] = 1;
			Stk[ tp + 1 ] = 0;
			while( tp && Fix[Cnt] < Fix[ Stk[tp] ] )Up( Stk[ tp-- ] );
			Ch[Cnt][0] = Stk[ tp + 1 ];
			if( Stk[tp] )Ch[ Stk[tp] ][1] = Cnt;
			Stk[ ++tp ] = Cnt;
			Up( Cnt );
		}
		while( tp )Up( Stk[ tp-- ] );
		return Stk[1];
	}
	
	int copy( int y ){
		int x = ++Cnt;
		Key[x] = Key[y];Fix[x] = Fix[y];
		Ch[x][0] = Ch[y][0];Ch[x][1] = Ch[y][1];
		Sz[x] = Sz[y];
		return x;
	}
	
	int merge( int x , int y ){
		if( !( x * y ) )return x + y;
		int t;
		if( Fix[x] < Fix[y] ){
			t = copy( x );
			Ch[t][1] = merge( Ch[t][1] , y );
		}
		else{
			t = copy( y );
			Ch[t][0] = merge( x , Ch[t][0] );
		}
		return Up( t ) , t;
	}
	
	par Split( int x , int y ){
		if( !x )return make_pair( 0 , 0 );
		int t = copy( x );par p;
		if( Sz[ Ch[t][0] ] >= y ){
			p = Split( Ch[t][0] , y );
			Ch[t][0] = p.second;p.second = t;
		}
		else{
			p = Split( Ch[t][1] , y - Sz[ Ch[t][0] ] - 1 );
			Ch[t][1] = p.first;p.first = t;
		}
		return Up( t ) , p;
	}
	
	void Ins( int x ){
		par p = Split( root[edit] , x );
		int t = Build();
		root[++edit] = merge( merge( p.first , t ) , p.second );
	}
	
	void Del( int x , int y ){
		par p1 = Split( root[edit] , x - 1 );
		par p2 = Split( p1.second , y );
		root[++edit] = merge( p1.first , p2.second );
	}
	
	void Ergo( int rt ){
		if( !rt )return;
		dit += ( 'c' == Key[rt] );
		Ergo( Ch[rt][0] );
		putchar( Key[rt] );
		Ergo( Ch[rt][1] );
	}
	
	void Display( int x , int y , int z ){
		par p1 = Split( root[x] , y - 1 );
		par p2 = Split( p1.second , z );
		Ergo( p2.first );puts("");
	}
	
}using namespace treap;

int main(){
	
	srand( 20010206 );
	
	scanf( "%d" , &n );
	
	for( int i = 1 ; i <= n ; i++ ){
		int opt , x , y , z;
		scanf( "%d" , &opt );
		if( opt == 1 ){
			scanf( "%d%s" , &x , s );
			x -= dit;
			Ins( x );
		}
		else if( opt == 2 ){
			scanf( "%d%d" , &x , &y );
			x -= dit;y -= dit;
			Del( x , y );
		}
		else{
			scanf( "%d%d%d" , &x , &y , &z );
			x -= dit;y -= dit;z -= dit;
			Display( x , y , z );
		}
	}
	
	return 0;
}
