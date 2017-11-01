#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= i##END ; i++ )

static const int MAXN = 25e4 +1;
static const int Inf = 0x7fffffff;

int n , m , tot;
int Rt , Num;

int Fa[MAXN] , Ch[MAXN][2] , Key[MAXN] , Sz[MAXN];
char Name[MAXN][11] , Opt[11];char ch;

map < string , int >Ref;

int GS( int );
int Find( int );
void Up( int );
void Del( int );
void Rotate( int );
void Insert( int );
void Splay( int , int );

char Getchar();

void print( int );

int main(){
	
	Rt = 1;Num = 2;
	Fa[2] = 1;Ch[1][1] = 2;
	Sz[1] = 2;Sz[2] = 1;
	Key[1] = Inf;Key[2] = -Inf;
	
	scanf( "%d" , &n );
	
	while( n-- ){
		int x = 0;
		ch = Getchar();
		scanf("%s",Opt);
		if( ch == '+' ){
			scanf( "%d" , &x );
			if( Ref[ Opt ] )Del( Ref[ Opt ] );
			Insert( x );
			strcpy( Name[Num] , Opt );
			Ref[ Opt ] = Num;
		}
		else if( Opt[0] >= '0' && Opt[0] <= '9' ){
			For( i , 0 , strlen( Opt ) - 1 )x = x * 10 + Opt[i] - '0';
			int p = Find( x );
			tot = Sz[Ch[Rt][1]] - 1;
			if( Sz[Ch[Rt][1]] > 10 ){
				tot = 10;
				int tmp = Find( Sz[Ch[Rt][0]] + 12 );
				Splay( p , 0 );Splay( tmp , Rt );
				print( Ch[Ch[Rt][1]][0] );
			}
			else print( Ch[Rt][1] );
			puts("");
		}
		else{
			Splay( Ref[ Opt ] , 0 );
			printf( "%d\n" , Sz[Ch[Rt][0]] );
		}
	}
	
	return 0;
}

char Getchar(){
	char ch = getchar();
	while( ch != '+' && ch != '?' )ch = getchar();
	return ch;
}

int GS( int x ){ return x == Ch[Fa[x]][1]; }

void Up( int x ){ Sz[x] = Sz[Ch[x][0]] + Sz[Ch[x][1]] + 1; }

void Rotate( int x ){
	int p = GS( x ) , fa = Fa[x] , gfa = Fa[fa];
	Ch[fa][p] = Ch[x][p^1];
	if( Ch[x][p^1] )Fa[ Ch[x][p^1] ] = fa;
	Ch[x][p^1] = fa;
	Fa[fa] = x;
	Fa[x] = gfa;
	if( gfa )Ch[gfa][ Ch[gfa][1] == fa ] = x;
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
			if( !x ){ Splay( p , 0 ) ; return p; }
			p = Ch[p][1];
		}
}

void Insert( int x ){
	int p = Rt , fa = 0;
	while( 1 ){
		fa = p;p = Ch[p][ x <= Key[p] ];
		if( !p ){
			Sz[ ++Num ] = 1;Key[Num] = x;
			p = Num;
			Fa[p] = fa;Ch[fa][ x <= Key[fa] ] = p;
			return Splay( p , 0 );
		}
	}
}

void Del( int x ){
	Splay( x , 0 );
	int p = Ch[x][0];
	while( Ch[p][1] )p = Ch[p][1];
	Splay( p , 0 );
	Fa[ Ch[Rt][1] = Ch[x][1] ] = Rt;
	Sz[Rt]--;
}

void print( int x ){
	if( !x )return;
	print( Ch[x][0] );
	if( x != 1 && x != 2 ){
		printf("%s",Name[x]);
		if( --tot )putchar(' ');
	}
	print( Ch[x][1] );
}
