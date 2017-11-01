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

typedef unsigned long long ULL;
static const int MAXN = 1e5 +1;

char Seq[MAXN];
int n , m , Rt , Num;
ULL Hex[MAXN];

void Init();
char Get( bool );

int Fa[MAXN] , Ch[MAXN][2] , Sz[MAXN] , Key[MAXN];
ULL h[MAXN];

int GS( int x ){ return Ch[Fa[x]][1] == x; }
void UP( int x ){
	int l = Ch[x][0] , r = Ch[x][1];
	Sz[x] = Sz[l] + Sz[r] + 1;
	h[x] = h[l] + Hex[Sz[l]] * Key[x] + Hex[Sz[l]+1] * h[r];
}
void Rotate( int x ){
	int p = GS( x ) , fa = Fa[x] , gfa = Fa[fa];
	Ch[fa][p] = Ch[x][p^1];
	if( Ch[x][p^1] )Fa[Ch[x][p^1]] = fa;
	Ch[x][p^1] = fa;
	Fa[fa] = x;
	Fa[x] = gfa;
	if( gfa )Ch[gfa][Ch[gfa][1] == fa] = x;
	UP( fa );UP( x );
}
void Splay( int x , int y ){
	for( int fa;( fa = Fa[x] ) != y;Rotate( x ) )
		if( Fa[fa] != y )Rotate( GS( x ) == GS( fa ) ? fa : x );
	if( !y )Rt = x;
}
int Find( int x ){
	int p = Rt;
	while( 1 )
		if( x <= Sz[Ch[p][0]] )p = Ch[p][0];
		else{
			x -= Sz[Ch[p][0]] + 1;
			if( !x ){
				Splay( p , 0 );
				return p;
			}
			p = Ch[p][1];
		}
}
void Insert( int x , int pos ){
	int A = Find( pos ) , B = Find( pos + 1 );
	Splay( A , 0 );Splay( B , Rt );
	Ch[B][0] = ++Num;
	h[Num] = Key[Num] = x;
	Sz[Num] = 1;Fa[Num] = B;
	UP( B );UP( A );
}
int Query( int x , int y ){
	int A = Find( x ) , B = Find( y + 1 );
	Splay( A , 0 );Splay( B , Rt );
	return h[Ch[B][0]];
}
void Solve( int x , int y ){
	int l = 0 , r = min( Num - x , Num - y ) - 1 , Res = 0;
	while( l <= r ){
		int Mid = l + r >> 1;
		if( Query( x , x + Mid ) == Query( y , y + Mid ) )Res = Mid , l = Mid + 1;
		else r = Mid - 1;
	}
	printf("%d\n",Res);
}

int main(){
	
	Init();
	
	Read( m );
	while( m-- ){
		char ch = Get( 0 );
		int x , y;
		Read( x );
		if( ch == 'Q' )Read( y ) , Solve( x , y );
		else if( ch == 'R' ){
			ch = Get( 1 );
			Find( x+1 );
			Key[Rt] = ch - 'a';UP( Rt );
		}
		else{
			ch = Get( 1 );
			Insert( ch - 'a' , x + 1 );
		}
	}
	return 0;
}

void Init(){
	scanf("%s",Seq);
	n = strlen( Seq );
	Hex[0] = 1;
	For( i , 1 , MAXN-1 )Hex[i] = Hex[i-1] * 27;
	Rt = 1;Num = 2;
	Fa[2] = 1;Ch[1][1] = 2;
	For( i , 0 , n-1 )Insert( Seq[i]-'a' , i+1 );
}
char Get( bool Flag ){
	char ch = getchar();
	if( !Flag )while( ch > 'Z' ||ch < 'A' )ch=getchar();
	else while( ch > 'z' || ch < 'a' )ch=getchar();
	return ch;
}
