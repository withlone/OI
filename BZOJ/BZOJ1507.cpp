#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

static const int MAXN = 1024 * 1024 +1 << 1;

int n , m , Cur;
char Opt[MAXN] , s[MAXN];

int Rt , Num;
char Key[MAXN];
int Fa[MAXN] , Ch[MAXN][2] , Sz[MAXN];

int New();
int GS( int );
int Find( int );
void Up( int );
void Rotate( int );
void Splay( int , int );

void print( int );
void Build( int , int , int );

void Get();
void Move( int );
void Next();
void Insert();
void Delete();

int main(){
	
	int x;
	
	Cur = Rt = 1;Num = 2;
	Fa[2] = 1;Ch[1][1] = 2;
	Sz[1] = 2;Sz[2] = 1;
	
	Read( m );
	while( m-- ){
		scanf("%s",Opt);
		if( !strcmp( Opt , "Get" ) )Read( n ) , Get() , puts("");
		if( !strcmp( Opt , "Prev" ) )Cur--;
		if( !strcmp( Opt , "Next" ) )Cur++;
		if( !strcmp( Opt , "Move" ) )Read( x ) , Move( x );
		if( !strcmp( Opt , "Insert" ) )Read( n ) , Insert();
		if( !strcmp( Opt , "Delete" ) )Read( n ) , Delete();
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

void Build( int l , int r , int rt ){
	int Mid = l + r >> 1;
	Key[rt] = s[Mid];Sz[rt] = 1;
	if( l == r )return;
	if( l < Mid ){ Fa[ Ch[rt][0] = ++Num ] = rt;Build( l , Mid-1 , Ch[rt][0] ); }
	if( Mid < r ){ Fa[ Ch[rt][1] = ++Num ] = rt;Build( Mid+1 , r , Ch[rt][1] ); }
	Up( rt );
}
void print( int x ){
	if( !x )return;
	print( Ch[x][0] );
	putchar( Key[x] );
	print( Ch[x][1] );
}

void Move( int x ){ Cur = ++x ; }
void Insert(){
	For( i , 1 , n ){
		s[i] = 10;
		while( s[i] == 10 )s[i] = getchar();
	}
	int x = Find( Cur ) , y = Find( Cur + 1 );
	Splay( x , 0 );Splay( y , Rt );
	Fa[ Ch[y][0] = ++Num ] = y;
	Build( 1 , n , Ch[y][0] );
	Up( y );Up( x );
}
void Delete(){
	int x = Find( Cur ) , y = Find( Cur + n + 1 );
	Splay( x , 0 );Splay( y , Rt );
	Ch[y][0] = 0;
	Up( y );Up( x );
}
void Get(){
	int x = Find( Cur ) , y = Find( Cur + n + 1 );
	Splay( x , 0 );Splay( y , Rt );
	print( Ch[y][0] );
}
