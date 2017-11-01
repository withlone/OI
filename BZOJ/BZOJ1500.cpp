#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

static const int Inf  = 1e9;
static const int MAXN = 5e5 +1;

int n , m;
int A[MAXN];char s[10];
int Stk[MAXN] , Tp;

int Rt , Num;
int Fa[MAXN] , Ch[MAXN][2] , Key[MAXN] , Sz[MAXN];
int Sum[MAXN] , L[MAXN] , R[MAXN] , Mx[MAXN];
bool Flag[MAXN] , Lz[MAXN];

int New();

int GS( int );
int Find( int );
void Up( int );
void Pd( int );
void Rotate( int );
void Splay( int , int );

void Trip( int );
void Insert( int , int );
void Delete( int , int );
void Reverse( int , int );
void Make_Same( int , int );
void Build( int , int , int );
int Get_Sum( int , int );

void reverse( int );
void Replace( int , int );

int main(){
	
	Num = 2;Rt = 1;
	Fa[2] = 1;Ch[1][1] = 2;
	Sz[2] = 1;Sz[1] = 2;
	Key[0] = L[0] = R[0] = Mx[0] = Key[1] = Key[2] = Sum[1] = Sum[2] = L[1] = L[2] = R[1] = R[2] = -Inf;
	
	Read( n );Read( m );
	
	Insert( 0 , n );
	
	while( m-- ){
		scanf("%s",s);
		if( !strcmp( s , "MAX-SUM" ) )printf("%d\n",Mx[Rt]);
		else{
			int pos , tot;
			Read( pos );Read( tot );
			if( !strcmp( s , "INSERT" ) )Insert( pos , tot );
			if( !strcmp( s , "DELETE" ) )Delete( pos , tot );
			if( !strcmp( s , "MAKE-SAME" ) )Make_Same( pos , tot );
			if( !strcmp( s , "REVERSE" ) )Reverse( pos , tot );
			if( !strcmp( s , "GET-SUM" ) )printf("%d\n",Get_Sum( pos , tot ));
		}
	}
	
	return 0;
}

int New(){
	int tmp;
	if( Tp )tmp = Stk[Tp--];
	else tmp = ++Num;
	Sz[tmp] = 1;
	Key[tmp] = Sum[tmp] = L[tmp] = R[tmp] = Mx[tmp] = -Inf;
	Fa[tmp] = Ch[tmp][0] = Ch[tmp][1] = Lz[tmp] = Flag[tmp] = 0;
	return tmp;
}
void Build( int l , int r , int rt ){
	int Mid = l + r >> 1;
	Key[rt] = A[Mid];
	if( l == r ){ Sum[rt] = L[rt] = R[rt] = Mx[Rt] = Key[rt];Sz[rt] = 1;return; }
	if( l < Mid ){ Fa[Ch[rt][0] = New()] = rt;Build( l , Mid - 1 , Ch[rt][0] ); }
	if( Mid < r ){ Fa[Ch[rt][1] = New()] = rt;Build( Mid + 1 , r , Ch[rt][1] ); }
	Up( rt );
}
void Trip( int x ){
	if( !x )return;
	Stk[++Tp] = x;
	Trip( Ch[x][0] );
	Trip( Ch[x][1] );
}
void Insert( int pos , int tot ){
	For( i , 1 , tot )Read( A[i] );
	int x = Find( pos + 1 ) , y = Find( pos + 2 );
	Splay( x , 0 );Splay( y , Rt );
	Ch[y][0] = New();Fa[Ch[y][0]] = y;
	Build( 1 , tot , Ch[y][0] );
	Up( y );Up( x );
}
void Delete( int pos , int tot ){
	int x = Find( pos ) , y = Find( pos + tot + 1 );
	Splay( x , 0 );Splay( y , Rt );
	Trip( Ch[y][0] );
	Ch[y][0] = 0;
	Up( y );Up( x );
}
void Make_Same( int pos , int tot ){
	int x = Find( pos ) , y = Find( pos + tot + 1 );
	Splay( x , 0 );Splay( y , Rt );
	Read( pos );
	Replace( Ch[y][0] , pos );
	Up( y );Up( x );
}
void Reverse( int pos , int tot ){
	int x = Find( pos ) , y = Find( pos + tot + 1 );
	Splay( x , 0 );Splay( y , Rt );
	reverse( Ch[y][0] );
	Up( y );Up( x );
}
int Get_Sum( int pos , int tot ){
	int x = Find( pos ) , y = Find( pos + tot + 1 );
	Splay( x , 0 );Splay( y , Rt );
	return Sum[Ch[y][0]];
}

void Replace( int x , int d ){
	if( !x )return;
	Key[x] = d;Sum[x] = d * Sz[x];
	L[x] = R[x] = Mx[x] = max( d , d * Sz[x] );
	Lz[x] = 1;
}
void reverse( int x ){
	if( !x )return;
	swap( L[x] , R[x] );
	swap( Ch[x][0] , Ch[x][1] );
	Flag[x] ^= 1;
}

int GS( int x ){ return x == Ch[Fa[x]][1]; }
void Up( int x ){
	int l = Ch[x][0] , r = Ch[x][1];
	Sz[x] = Sz[l] + Sz[r] + 1;
	Sum[x] = Sum[l] + Sum[r] + Key[x];
	L[x] = max( L[l] , Sum[l] + Key[x] + max( 0 , L[r] ) );
	R[x] = max( R[r] , Sum[r] + Key[x] + max( 0 , R[l] ) );
	Mx[x] = max( max( Mx[l] , Mx[r] ) , max( R[l] , 0 ) + max( L[r] , 0 ) + Key[x] );
}
void Pd( int x ){
	int &l = Ch[x][0] , &r = Ch[x][1];
	if( Flag[x] ){
		Flag[x] = 0;
		if( l )reverse( l );
		if( r )reverse( r );
	}
	if( Lz[x] ){
		Lz[x] = 0;
		if( l )Replace( l , Key[x] );
		if( r )Replace( r , Key[x] );
	}
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
	Pd( x );
	for( int fa;( fa = Fa[x] ) != y;Rotate( x ) )
		if( Fa[fa] != y )Rotate( GS( x ) == GS( fa ) ? fa : x );
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
