#include<cstdio>

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e5 +1;

int Rt , Num;
int n , Limit , Opt , tot , Delta;
int Fa[MAXN] , Ch[MAXN][2] , Key[MAXN] , Sz[MAXN] , Sm[MAXN];

char Getchar();

int GS( int );
int Find( int );
void Up( int );
void Del( int );
void Splay( int );
void Insert( int );
void Rotate( int );

int main(){
	
	Read( n );Read( Limit );
	while( n-- ){
		char ch = Getchar();
		Read( Opt );
		if( ch == 'I' )if( Opt >= Limit )Insert( Opt - Delta ) , tot++;
		if( ch == 'A' )Delta += Opt;
		if( ch == 'S' )Delta -= Opt , Del( Limit );
		if( ch == 'F' ){
			if( Opt > Sz[Rt] )puts("-1");
			else printf("%d\n",Key[Find( Sz[Rt] - Opt + 1 )] + Delta);
		}
	}
	printf("%d\n",tot - Sz[Rt]);
	return 0;
}

int GS( int x ){ return x == Ch[Fa[x]][1]; }
void Up( int x ){ Sz[x] = Sz[Ch[x][0]] + Sz[Ch[x][1]] + Sm[x]; }
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
void Splay( int x ){
	for( int fa;fa = Fa[x];Rotate( x ) )
		if( Fa[fa] )Rotate( GS( fa ) == GS( x ) ? fa : x );
	Rt = x;
}
void Insert( int x ){
	if( !Rt ){
		Rt = ++Num;
		Key[Rt] = x;Sm[Rt] = Sz[Rt] = 1;
		return;
	}
	int p = Rt , fa = 0;
	while( 1 ){
		if( Key[p] == x ){
			Sm[p]++;Sz[p]++;
			Splay( p );
			return;
		}
		fa = p;p = Ch[p][x > Key[p]];
		if( !p ){
			p = ++Num;
			Sm[p] = Sz[p] = 1;Key[p] = x;
			Ch[fa][x > Key[fa]] = p;Fa[p] = fa;
			Up( fa );Splay( p );
			return;
		}
	}
}
void Del( int x ){
	int p = Rt , fa = 0;x -= Delta;
	while( p ){
		if( Key[p] < x )p = Ch[p][1];
		else fa = p , p = Ch[p][0];
	}
	if( Key[fa] < x )Rt = 0;
	else{
		Splay( fa );
		Ch[fa][0] = 0;
		Up( fa );
	}
}
int Find( int x ){
	int p = Rt;
	while( 1 ){
		if( x <= Sz[Ch[p][0]] )p = Ch[p][0];
		else{
			x -= Sz[Ch[p][0]] + Sm[p];
			if( x <= 0 )return p;
			p = Ch[p][1];
		}
	}
}

char Getchar(){
	char ch = getchar();
	while( ch > 'Z' ||ch < 'A' )ch = getchar();
	return ch;
}
