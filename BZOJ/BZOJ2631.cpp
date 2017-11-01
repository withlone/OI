#include<cstdio>

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline void swap( Type &x , Type &y ){ x ^= y ^= x ^= y; }
template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

typedef unsigned int LL;
static const int Mod  = 51061;
static const int MAXN = 1e5 +1;

int n , m;
bool Flag[MAXN];
int Fa[MAXN] , Ch[MAXN][2];
LL Key[MAXN] , Add[MAXN] , Mul[MAXN] , Sm[MAXN] , Sz[MAXN];

bool Is_Rot( int );
int GS( int );
void Up( int );
void Pd( int );
void Down( int );
void Splay( int );
void Rotate( int );

int Find( int );
void MRot( int );
void Access( int );

void Cut( int , int );
void Link( int , int );

void Ach( int , int );
void Cal( int , int , int );

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Key[i] = 1 , Mul[i] = 1;
	
	For( i , 1 , n-1 ){
		int x , y;
		Read( x );Read( y );
		Link( x , y );
	}
	while( m-- ){
		LL x , y , z;
		char ch = getchar();
		while( ch != '+' && ch != '-' && ch != '*' && ch != '/' )ch = getchar();
		Read( x );Read( y );
		if( ch == '+' ){
			Read( z );
			Ach( x , y );
			Cal( y , 1 , z );
		}
		if( ch == '-' ){
			Cut( x , y );
			Read( x );Read( y );
			Link( x , y );
		}
		if( ch == '*' ){
			Read( z );
			Ach( x , y );
			Cal( y , z , 0 );
		}
		if( ch == '/' ){
			Ach( x , y );
			printf("%d\n",Sm[y] %= Mod);
		}
	}
	return 0;
}

bool Is_Rot( int x ){ return x != Ch[Fa[x]][0] && x != Ch[Fa[x]][1]; }
int GS( int x ){ return x == Ch[Fa[x]][1]; }
void Up( int x ){
	int l = Ch[x][0] , r = Ch[x][1];
	Sm[x] = ( Sm[l] + Sm[r] + Key[x] ) % Mod;
	Sz[x] = Sz[l] + Sz[r] + 1;
}
void Pd( int x ){
	int &l = Ch[x][0] , &r = Ch[x][1];
	if( Flag[x] ){
		Flag[x] ^= 1;
		if( l )Flag[l] ^= 1;
		if( r )Flag[r] ^= 1;
		swap( l , r );
	}
	if( Add[x] || Mul[x] != 1 )Cal( l , Mul[x] , Add[x] ) , Cal( r , Mul[x] , Add[x] );
	Add[x] = 0;Mul[x] = 1;
}
void Down( int x ){
	int Stk[MAXN] , Tp;
	Stk[Tp = 1] = x;
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

int Find( int x ){
	Access( x );
	Splay( x );
	while( Ch[x][0] )x = Ch[x][0];
	return x;
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

void Link( int x , int y ){
	MRot( x );
	Fa[x] = y;
}
void Cut( int x , int y ){
	Ach( x , y );
	Ch[y][0] = Fa[Ch[y][0]] = 0;Up( y );
}

void Ach( int x , int y ){
	MRot( x );Access( y );Splay( y );
}
void Cal( int x , int mul , int add ){
	if( !x )return;
	Add[x] = ( Add[x] * mul + add ) % Mod;
	Mul[x] = ( Mul[x] * mul ) % Mod;
	Key[x] = ( Key[x] * mul + add ) % Mod;
	Sm[x] = ( Sm[x] * mul + Sz[x] * add ) % Mod;
}
