#include<cstdio>
#include<algorithm>

using std :: swap;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 3e5 +1;

int n , m;

bool Flag[MAXN];
int Fa[MAXN] , Ch[MAXN][2] , val[MAXN] , Sm[MAXN];

int GS( int );
bool Is_Rot( int );
void Up( int );
void Pd( int );
void Down( int );
void Splay( int );
void Rotate( int );

void Access( int );
void MRot( int );
int Find( int );

int Get_Xor( int , int );
void Link( int , int );
void Cut( int , int );

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Read( val[i] ) , Sm[i] = val[i];
	while( m-- ){
		int Opt , x , y;
		Read( Opt );Read( x );Read( y );
		switch( Opt ){
			case 0:printf("%d\n",Get_Xor( x , y ));break;
			case 1:if( Find( x ) != Find( y ) )Link( x , y );break;
			case 2:if( Find( x ) == Find( y ) )Cut( x , y );break;
			case 3:Access( x );Splay( x );val[x] = y;Up( x );break;
		}
	}
	return 0;
}

bool Is_Rot( int x ){ return x != Ch[Fa[x]][0] && x != Ch[Fa[x]][1]; }
int GS( int x ){ return x == Ch[Fa[x]][1]; }
void Up( int x ){ Sm[x] = Sm[Ch[x][0]] ^ Sm[Ch[x][1]] ^ val[x]; }
void Pd( int x ){
	if( !Flag[x] )return;
	Flag[x] = 0;
	int &l = Ch[x][0] , &r = Ch[x][1];
	if( l )Flag[l] ^= 1;
	if( r )Flag[r] ^= 1;
	swap( l , r );
}
void Down( int x ){
	int Stk[MAXN] , Tp = 0;
	Stk[++Tp] = x;
	for( ;!Is_Rot( x );x = Fa[x] )Stk[++Tp] = Fa[x];
	while( Tp )Pd( Stk[Tp--] );
}
void Rotate( int x ){
	int p = GS( x ) , fa = Fa[x] , gfa = Fa[fa];
	if( !Is_Rot( fa ) )Ch[gfa][GS(fa)] = x;
	Fa[x] = gfa;
	Ch[fa][p] = Ch[x][p^1];
	if( Ch[x][p^1] )Fa[Ch[x][p^1]] = fa;
	Ch[x][p^1] = fa;
	Fa[fa] = x;
	Up( fa );Up( x );
}
void Splay( int x ){
	Down( x );
	for( ;!Is_Rot( x );Rotate( x ) )
		if( !Is_Rot( Fa[x] ) )Rotate( GS( Fa[x] ) == GS( x ) ? Fa[x] : x );
}

void Access( int x ){
	int t = 0;
	while( x ){
		Splay( x );
		Ch[x][1] = t;
		Up( x );
		t = x;x = Fa[x];
	}
}
void MRot( int x ){
	Access( x );
	Splay( x );
	Flag[x] ^= 1;
}
int Find( int x ){
	Access( x );
	Splay( x );
	while( Ch[x][0] )x = Ch[x][0];
	return x;
}

int Get_Xor( int x , int y ){
	MRot( x );
	Access( y );Splay( y );
	return Sm[y];
}
void Link( int x , int y ){
	MRot( x );
	Fa[x] = y;
}
void Cut( int x , int y ){
	MRot( x );
	Access( y );Splay( y );
	Ch[y][0] = Fa[Ch[y][0]] = 0;Up( y );
}
