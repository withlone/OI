#include<cstdio>
#include<algorithm>
using namespace std;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e5 +1;

int n;
int A[MAXN];
int Stk[MAXN] , Tp;

int Rt;
bool Flag[MAXN];
int Fa[MAXN] , Ch[MAXN][2] , Sz[MAXN];

int GS( int );
int Find( int );
void Pd( int );
void Up( int );
void Rotate( int );
void Flip( int , int );
void Splay( int , int );

int Get( int );
int Build( int , int );
void Down( int , int );

pair< int , int >Sort[MAXN];

int main(){
	
	int x;
	
	Read( n );
	For( i , 1 , n )Read( Sort[i].first ) , Sort[i].second = i;
	sort( 1 + Sort , 1 + n + Sort );
	For( i , 1 , n )A[Sort[i].second] = i;
	
	For( i , 1 , n )Sz[i] = 1;
	
	Rt = Build( 1 , n );
	
	For( i , 1,  n ){
		int p = Get( i );
		printf("%d ",p);
		Flip( i , p );
	}
	puts("");
	return 0;
}

int GS( int x ){ return x == Ch[Fa[x]][1]; }
void Up( int x ){ Sz[x] = Sz[Ch[x][0]] + Sz[Ch[x][1]] + 1; }
void Pd( int x ){
	if( !Flag[x] )return;
	int &l = Ch[x][0] , &r = Ch[x][1];
	Flag[x] = 0;
	if( l )Flag[l] ^= 1;
	if( r )Flag[r] ^= 1;
	swap( l , r );
}
void Rotate( int x ){
	int p = GS( x ) , fa = Fa[x] , gfa = Fa[fa];
	Ch[fa][p] = Ch[x][p^1];
	if( Ch[x][p^1] )Fa[Ch[x][p^1]] = fa;
	Ch[x][p^1] = fa;
	Fa[fa] = x;
	Fa[x] = gfa;
	if( gfa )Ch[gfa][Ch[gfa][1] == fa] = x;
	Up( fa );Up( x );
}
void Splay( int x , int y ){
	Down( x , y );
	for( int fa;( fa = Fa[x] ) != y;Rotate( x ) )
		if( Fa[fa] != y )Rotate( GS( fa ) == GS( x ) ? fa : x );
	if( !y )Rt = x;
}
int Find( int x ){
	int p = Rt;
	while( 1 ){
		Pd( p );
		if( x <= Sz[Ch[p][0]] )p = Ch[p][0];
		else{
			x -= Sz[Ch[p][0]] + 1;
			if( !x )return p;
			p = Ch[p][1];
		}
	}
}
void Flip( int l , int r ){
	if( l == r )return;
	if( l == 1 && r == n )Flag[Rt] ^= 1;
	else if( l == 1 )Splay( Find( r + 1 ) , 0 ) , Flag[Ch[Rt][0]] ^= 1;
	else if( r == n )Splay( Find( l - 1 ) , 0 ) , Flag[Ch[Rt][1]] ^= 1;
	else{
		int x = Find( l - 1 ) , y = Find( r + 1 );
		Splay( x , 0 );Splay( y , Rt );
		Flag[Ch[y][0]] ^= 1;
	}
}

int Get( int x ){
	Splay( x , 0 );
	return Sz[Ch[Rt][0]] + 1;
}
int Build( int l , int r ){
	if( l == r )return A[l];
	int Mid = l + r >> 1 , rt = A[Mid];
	if( l < Mid )Fa[ Ch[rt][0] = Build( l , Mid - 1 ) ] = rt;
	if( Mid < r )Fa[ Ch[rt][1] = Build( Mid + 1 , r ) ] = rt;
	Up( rt );return rt;
}
void Down( int x , int y ){
	Tp = 0;
	for( int p=x;p != y;p=Fa[p] )
		Stk[++Tp] = p;
	while( Tp )Pd( Stk[Tp--] );
}
