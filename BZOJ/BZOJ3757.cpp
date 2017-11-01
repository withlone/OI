#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

static const int maxn = 1e5 +1;
static const int maxm = maxn << 1;

int n , m , Fac , root;
int Col[maxn];
int H[maxn] , Nt[maxm] , To[maxm] , Ct;
int BL[maxn] , Dfn[maxn] , Cnt;
int Fa[maxn][18] , Dep[maxn];
int Stk[maxn] , tp;
int ans[maxn];

struct query{
	int l , r , id , x , y;
	bool operator < ( query tmp ) const { return BL[l] < BL[tmp.l] || BL[l] == BL[tmp.l] && Dfn[r] < Dfn[tmp.r]; }
}Q[maxn];

void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

int Dfs( int x ){
	int size = 0;
	Dfn[x] = ++Cnt;
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( y == Fa[x][0] )continue;
		Fa[y][0] = x;
		Dep[y] = Dep[x] + 1;
		size += Dfs( y );
		if( size >= Fac ){
			++Ct;
			while( size-- )BL[ Stk[ tp-- ] ] = Ct;
			size = 0;
		}
	}
	Stk[ ++tp ] = x;
	return size + 1;
}

int QLca( int x , int y ){
	if( Dep[x] < Dep[y] )swap( x , y );
	int delta = Dep[x] - Dep[y];
	For( i , 0 , 17 )
		if( delta & ( 1 << i ) )x = Fa[x][i];
	if( x == y )return x;
	Lop( i , 17 , 0 )
		if( Fa[x][i] != Fa[y][i] )x = Fa[x][i] , y = Fa[y][i];
	return Fa[x][0];
}

int num[maxn] , sum;bool Vis[maxn];
void modify( int x ){
	if( !Vis[x] )Vis[x] =  true , sum += ( ++num[ Col[x] ] == 1 );
	else Vis[x] = false , sum -= !--num[ Col[x] ];
}
void Solve( int x , int y ){
	while( x != y )
		if( Dep[x] > Dep[y] )modify( x ) , x = Fa[x][0];
		else modify( y ) , y = Fa[y][0];
}

int main(){
	
	Read( n );Read( m );Fac = sqrt( n );
	For( i , 1 , n )Read( Col[i] );
	For( i , 1 , n ){
		int u , v;
		Read( u );Read( v );
		if( !( u * v ) ){ root = u + v;continue; }
		Ins( u , v );Ins( v , u );
	}
	
	Ct = 0;
	Dep[root] = 1;
	Dfs( root );
	++Ct;
	while( tp )BL[ Stk[ tp-- ] ] = Ct;
	
	For( i , 1 , m ){
		Read( Q[i].l ) , Read( Q[i].r ) , Read( Q[i].x ) , Read( Q[i].y ) , Q[i].id = i;
		if( Dfn[ Q[i].l ] > Dfn[ Q[i].r ] )swap( Q[i].l , Q[i].r );
	}
	sort( 1 + Q , 1 + m + Q );
	
	For( j , 1 , 17 )For( i , 1 , n )
		Fa[i][j] = Fa[ Fa[i][j-1] ][j-1];
	
	Solve( Q[1].l , Q[1].r );
	int Lca = QLca( Q[1].l , Q[1].r );
	modify( Lca );
	ans[ Q[1].id ] = sum;
	if( Q[1].x != Q[1].y && num[ Q[1].x ] && num[ Q[1].y ] )ans[ Q[1].id ]--;
	modify( Lca );
	
	For( i , 2 , m ){
		Solve( Q[i - 1].l , Q[i].l );
		Solve( Q[i - 1].r , Q[i].r );
		Lca = QLca( Q[i].l , Q[i].r );
		modify( Lca );
		ans[ Q[i].id ] = sum;
		if( Q[i].x != Q[i].y && num[ Q[i].x ] && num[ Q[i].y ] )ans[ Q[i].id ]--;
		modify( Lca );
	}
	
	For( i , 1 , m )printf("%d\n",ans[i]);
	
	return 0;
}

