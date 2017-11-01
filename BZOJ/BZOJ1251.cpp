#include<cstdio>
#include<algorithm>
using namespace std;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch-'0';In *= f;
}

typedef long long LL;
static const int MAXN = 5e4 +1;

int n , m , Rt , Num , Opt;
int Fa[MAXN] , Ch[MAXN][2] , Sz[MAXN];
LL Key[MAXN] , Mx[MAXN] , Lazy[MAXN];
bool Flag[MAXN];

int GS( int x ){ return Ch[Fa[x]][1] == x; }
void Up( int x ){
	int l = Ch[x][0] , r = Ch[x][1];
	Sz[x] = Sz[l] + Sz[r] + 1;
	Mx[x] = -0x7fffffff;
	if( l )Mx[x] = max( Mx[x] , Mx[l] );
	if( r )Mx[x] = max( Mx[x] , Mx[r] );
	Mx[x] = max( Mx[x] , Key[x] );
}
void Pd( int x ){
	int &l = Ch[x][0] , &r = Ch[x][1];
	if( Flag[x] ){
		swap( l , r );
		if( l )Flag[l] ^= 1;
		if( r )Flag[r] ^= 1;
		Flag[x] ^= 1;
	}
	if( Lazy[x] ){
		if( l )Lazy[l] += Lazy[x] , Mx[l] += Lazy[x] , Key[l] += Lazy[x];
		if( r )Lazy[r] += Lazy[x] , Mx[r] += Lazy[x] , Key[r] += Lazy[x];
		Lazy[x] = 0;
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
			if( !x ){
				Splay( p , 0 );
				return p;
			}
			p = Ch[p][1];
		}
	}
}
LL Query( int l , int r ){
	if( l == 1 && r == n )return Mx[Rt];
	if( l == 1 ){
		r = Find( r + 1 );
		return Mx[Ch[r][0]];
	}
	if( r == n ){
		l = Find( l - 1 );
		return Mx[Ch[l][1]];
	}
	l = Find( l - 1 );r = Find( r + 1 );
	Splay( l , 0 );Splay( r , Rt );
	return Mx[Ch[r][0]];
}

int Build( int , int );

int main(){
	
	Read( n );Read( m );
	Rt = Build( 1 , n );
	while( m-- ){
		int x , y , p;
		Read( Opt );Read( x );Read( y );
		if( Opt == 1 ){
			Read( p );
			if( x == 1 && y == n )Lazy[Rt] += p , Mx[Rt] += p , Key[Rt] += p;
			else if( x == 1 ){
				y = Find( y + 1 );
				Mx[Ch[y][0]] += p;
				Key[Ch[y][0]] += p;
				Lazy[Ch[y][0]] += p;
			}
			else if( y == n ){
				x = Find( x - 1 );
				Mx[Ch[x][1]] += p;
				Key[Ch[x][1]] += p;
				Lazy[Ch[x][1]] += p;
			}
			else{
				x = Find( x - 1 );y = Find( y + 1 );
				Splay( x , 0 );Splay( y , Rt );
				Mx[Ch[y][0]] += p;
				Key[Ch[y][0]] += p;
				Lazy[Ch[y][0]] += p;
			}
		}
		else if( Opt == 2 ){
			if( x == 1 && y == n )Flag[Rt] ^= 1;
			else if( x == 1 ){
				y = Find( y + 1 );
				Flag[Ch[y][0]] ^= 1;
			}
			else if( y == n ){
				x = Find( x - 1 );
				Flag[Ch[x][1]] ^= 1;
			}
			else{
				x = Find( x - 1 );y = Find( y + 1 );
				Splay( x , 0 );Splay( y , Rt );
				Flag[Ch[y][0]] ^= 1;
			}
		}
		else printf("%lld\n",Query( x , y ));
	}
	return 0;
}

int Build( int l , int r ){
	Sz[l] = Sz[r] = 1;
	if( l == r )return l;
	if( l + 1 == r ){
		Fa[l] = r;
		Ch[r][0] = l;
		Up( r );
		return r;
	}
	int Mid = l + r >>1;
	Fa[Ch[Mid][0] = Build( l , Mid-1 )] = 
	Fa[Ch[Mid][1] = Build( Mid+1 , r )] = Mid;
	Up( Mid );return Mid;
}
