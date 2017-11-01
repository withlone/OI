#include<cstdio>

#define For( i , _Begin , _End ) for( register int i=(_Begin);i<=(_End);i++ )

template< typename Type >void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e5 +1;

int n , m , q;

int Ft[MAXN];

int Key[MAXN] , Fa[MAXN] , Ch[MAXN][2] , Sz[MAXN];

int GS( int );
int Find( int , int );
void Up( int );
void Splay( int );
void Rotate( int );
void Insert( int , int );

int find( int );
void Go( int , int );

char Getchar();

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Read( Key[i] ) , Sz[i] = 1 , Ft[i] = i;
	For( i , 1 , m ){
		int x , y , xx ,yy;
		Read( x );Read( y );
		xx = find( x );yy = find( y );
		if( xx == yy )continue;
		Splay( x );Splay( y );
		if( Sz[x] > Sz[y] )x ^= y ^= x ^= y;
		Go( x , y );Ft[xx] = yy;
	}
	Read( q );
	while( q-- ){
		char ch = Getchar();int x , y;Read( x );Read( y );
		if( ch == 'B' ){
			int xx = find( x ) , yy = find( y );
			if( xx != yy ){
				Splay( x );Splay( y );
				if( Sz[x] > Sz[y] )x ^= y ^= x ^= y;
				Go( x , y );Ft[xx] = yy;
			}
		}
		else{
			Splay( x );
			if( Sz[x] < y )puts("-1");
			else printf("%d\n",Find( x , y ));
		}
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
void Splay( int x ){
	for( int fa;fa = Fa[x];Rotate( x ) )
		if( Fa[fa] )Rotate( GS( fa ) == GS( x ) ? fa : x );
}
int Find( int y , int x ){
	int p = y;
	while( 1 )
		if( x <= Sz[Ch[p][0]] )p = Ch[p][0];
		else{
			x -= Sz[Ch[p][0]] + 1;
			if( !x )return p;
			p = Ch[p][1];
		}
}
void Insert( int x , int y ){
	int p = y , fa = 0;
	while( 1 ){
		fa = p;p = Ch[p][Key[x] > Key[p]];
		if( !p ){
			Fa[x] = fa;Ch[fa][Key[x] > Key[fa]] = x;
			Up( fa );Splay( x );
			return;
		}
	}
}

int find( int x ){ return x == Ft[x] ? x : Ft[x] = find( Ft[x] ); }
void Go( int x , int y ){
	if( !x )return;
	Go( Ch[x][0] , y );
	Go( Ch[x][1] , y );
	Insert( x , y );
}

char Getchar(){
	char ch = getchar();
	while( ch > 'Z' || ch < 'A' )ch = getchar();
	return ch;
}
