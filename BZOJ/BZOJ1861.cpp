#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

static const int MAXN = 8e4 +1;

int n , m;
int A[MAXN];
char Opt[100];

int Rt;
int Fa[MAXN] , Ch[MAXN][2] , Sz[MAXN];

int Pre();
int Next();
int GS( int );
int Find( int );
void Up( int );
void Del( int );
void Rotate( int );
void Splay( int , int );

void Top( int );
void Bottom( int );
void INSERT( int );

int Build( int , int );

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Read( A[i] );
	
	For( i , 1 , n )Sz[i] = 1;
	
	Rt = Build( 1 , n );
	
	while( m-- ){
		int x;
		scanf("%s",Opt);Read( x );
		if( !strcmp( Opt , "Top" ) )Top( x );
		if( !strcmp( Opt , "Ask" ) )Splay( x , 0 ) , printf("%d\n",Sz[Ch[x][0]]);
		if( !strcmp( Opt , "Query" ) )printf("%d\n",Find( x ));
		if( !strcmp( Opt , "Bottom" ) )Bottom( x );
		if( !strcmp( Opt , "Insert" ) )INSERT( x );
	}
	
	return 0;
}

int GS( int x ){ return x == Ch[Fa[x]][1]; }
void Up( int x ){ Sz[x] = Sz[Ch[x][0]] + Sz[Ch[x][1]] + 1; }
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
	for( int fa;( fa = Fa[x] ) != y;Rotate( x ) )
		if( Fa[fa] != y )Rotate( GS( fa ) == GS( x ) ? fa : x );
	if( !y )Rt = x;
}
int Find( int x ){
	int p = Rt;
	while( 1 )
		if( x <= Sz[Ch[p][0]] )p = Ch[p][0];
		else{
			x -= Sz[Ch[p][0]] + 1;
			if( !x )return p;
			p = Ch[p][1];
		}
}
int Pre(){
	int p = Ch[Rt][0];
	while( Ch[p][1] )p = Ch[p][1];
	return p;
}
int Next(){
	int p = Ch[Rt][1];
	while( Ch[p][0] )p = Ch[p][0];
	return p;
}
void Del( int x ){
	Splay( x , 0 );
	if( !Ch[Rt][0] )Fa[ Rt = Ch[Rt][1] ] = 0;
	else if( !Ch[Rt][1] )Fa[ Rt = Ch[Rt][0] ] = 0;
	else{
		Splay( Pre() , 0 );
		Fa[Ch[x][1]] = Rt;
		Ch[Rt][1] = Ch[x][1];
		Up( Rt );
	}
	Ch[x][0] = Ch[x][1] = Fa[x] = 0;Sz[x] = 1;
}

void Top( int x ){
	Del( x );
	Fa[ Ch[x][1] = Rt ] = x;
	Fa[ Rt = x ] = 0;
	Up( Rt );
}
void Bottom( int x ){
	Del( x );
	Fa[ Ch[x][0] = Rt ] = x;
	Fa[ Rt = x ] = 0;
	Up( Rt );
}
void INSERT( int x ){
	int t , y;Read( t );
	if( !t )return;
	Splay( x , 0 );
	if( t == -1 )y = Pre();
	else y = Next();
	if( !y )return;
	Splay( y , 0 );Splay( x , Rt );
	int p = GS( x );
	int Son_x = Ch[x][p] , Son_y = Ch[y][p^1];
	Ch[x][p^1] = Son_y;Ch[x][p] = y;
	Ch[y][p^1] = 0;Ch[y][p] = Son_x;
	Fa[Ch[x][0]] = Fa[Ch[x][1]] = x;
	Fa[Ch[y][0]] = Fa[Ch[y][1]] = y;
	Rt = x;Fa[x] = 0;
	Up( y );Up( x );
	Fa[0] = Ch[0][0] = Ch[0][1] = 0;
}

int Build( int l , int r ){
	if( l == r )return A[l];
	int Mid = l + r >> 1 , rt = A[Mid];
	if( l < Mid )Fa[ Ch[rt][0] = Build( l , Mid - 1 ) ] = rt;
	if( Mid < r )Fa[ Ch[rt][1] = Build( Mid + 1 , r ) ] = rt;
	Up( rt );return rt;
}
