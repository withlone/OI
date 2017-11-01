#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline void swap( Type &x , Type &y ){ x ^= y ^= x ^= y; }
template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1024 * 1024  << 1 | 1;

int n , m;
char Opt[50] , s[MAXN];

int Stk[MAXN] , Tp;

int Rt , Num , pos;
bool Flag[MAXN];char Key[MAXN];
int Fa[MAXN] , Sz[MAXN] , Ch[MAXN][2];

int GS( int );
void Up( int );
void Pd( int );
void Rotate( int );
void Down( int , int );
void Splay( int , int );

char Get();
void Del();
void Flip();
void Insert();

void Build( int , int , int );

int main(){
	
	pos = Rt = 1;Num = 2;
	Fa[2] = 1;Ch[1][1] = 2;
	Sz[2] = 1;Sz[1] = 2;
	
	Read( m );
	while( m-- ){
		scanf("%s",Opt);
		if( !strcmp( Opt , "Get" ) )printf("%c\n",Get());
		if( !strcmp( Opt , "Prev" ) )pos--;
		if( !strcmp( Opt , "Next" ) )pos++;
		if( !strcmp( Opt , "Move" ) )Read( n ) , pos = ++n;
		if( !strcmp( Opt , "Insert" ) )Read( n ) , Insert();
		if( !strcmp( Opt , "Delete" ) )Read( n ) , Del();
		if( !strcmp( Opt , "Rotate" ) )Read( n ) , Flip();
	}
	return 0;
}

int GS( int x ){ return x == Ch[Fa[x]][1]; }
void Up( int x ){ Sz[x] = Sz[Ch[x][0]] + Sz[Ch[x][1]] + 1; }
void Pd( int x ){
	if( !Flag[x] )return;
	Flag[x] = 0;
	int &l = Ch[x][0] , &r = Ch[x][1];
	if( l )Flag[l] ^= 1;
	if( r )Flag[r] ^= 1;
	swap( l , r );
}
void Down( int x , int y ){
	Tp = 0;
	for( int p=x;p != y;p=Fa[p] )
		Stk[++Tp] = p;
	while( Tp )Pd( Stk[Tp--] );
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

void Build( int l , int r , int rt ){
	int Mid = l + r >> 1;
	Key[rt] = s[Mid];Sz[rt] = 1;
	if( l == r )return;
	if( l < Mid ){ Fa[ Ch[rt][0] = ++Num ] = rt;Build( l , Mid - 1 , Ch[rt][0] ); }
	if( Mid < r ){ Fa[ Ch[rt][1] = ++Num ] = rt;Build( Mid + 1 , r , Ch[rt][1] ); }
	Up( rt );
}

char Get(){ return Key[Find( pos + 1 )]; }
void Insert(){
	For( i , 1 , n ){
		s[i] = 10;
		while( s[i] == 10 )s[i] = getchar();
	}
	int x = Find( pos ) , y = Find( pos + 1 );
	Splay( x , 0 );Splay( y , Rt );
	Fa[ Ch[y][0] = ++Num ] = y;
	Build( 1 , n , Ch[y][0] );
	Up( y );Up( x );
}
void Del(){
	int x = Find( pos ) , y = Find( pos + n + 1 );
	Splay( x , 0 );Splay( y , Rt );
	Ch[y][0] = 0;
	Up( y );Up( x );
}
void Flip(){
	int x = Find( pos ) , y = Find( pos + n + 1 );
	Splay( x , 0 );Splay( y , Rt );
	Flag[Ch[y][0]] ^= 1;
}
