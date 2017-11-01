#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 4e4 +1;
static const int maxx = 1e5 +1;
static const int maxm = maxn << 1;

int n , m , Fac , Cnt , Ct;
int Stk[maxn] , tp;
int v[maxn] , w[maxn];
int H[maxn] , Nt[maxm] , To[maxm];
int Dep[maxn] , Dfn[maxn] , BL[maxn] , Fa[maxn][17];
bool Vis[maxn];int ans[maxx] , num[maxn] , sum;

struct Query{
	int l , r , id;
	bool operator < ( Query t ) const { return BL[l] < BL[t.l] || BL[l] == BL[t.l] && Dfn[r] < Dfn[t.r] ; }
}Q[maxx];

int Dfs( int );
int QLca( int , int );
void modify( int );
void Ins( int , int );
void Solve( int , int );

int main(){
	
	Read( n );Read( m );Fac = sqrt( n );
	For( i , 1 , n )Read( v[i] ) , w[i] = v[i];
	
	sort( 1 + w , 1 + n + w );
	Cnt = unique( 1 + w , 1 + n + w ) - w - 1;
	For( i , 1 , n )v[i] = lower_bound( 1 + w , 1 + Cnt + w , v[i] ) - w;
	
	For( i , 1 , n - 1 ){
		int x , y ;
		Read( x );Read( y );
		Ins( x , y );Ins( y , x );
	}
	
	Cnt = Ct = 0;
	Dep[1] = 1;
	Dfs( 1 );
	++Ct;
	while( tp )BL[ Stk[ tp-- ] ] = Ct;
	
	For( j , 1 , 16 )For( i , 1 , n )
		Fa[i][j] = Fa[ Fa[i][j - 1] ][j - 1];
	
	For( i , 1 , m ){
		Read( Q[i].l ) , Read( Q[i].r ) , Q[i].id = i;
		if( Dfn[ Q[i].l ] > Dfn[ Q[i].r ] )swap( Q[i].l , Q[i].r );
	}
	sort( 1 + Q , 1 + m + Q );
	
	Q[0].l = Q[0].r = 1;
	For( i , 1 , m ){
		Solve( Q[i - 1].l , Q[i].l );
		Solve( Q[i - 1].r , Q[i].r );
		int Lca = QLca( Q[i].l , Q[i].r );
		modify( Lca );ans[ Q[i].id ] = sum;modify( Lca );
	}
	
	For( i , 1 , m )printf("%d\n",ans[i]);
	
	return 0;
}

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
	For( i , 0 , 16 )
		if( delta & ( 1 << i ) )x = Fa[x][i];
	if( x == y )return x;
	Lop( i , 16 , 0 )
		if( Fa[x][i] != Fa[y][i] )x = Fa[x][i] , y = Fa[y][i];
	return Fa[x][0];
}

void modify( int x ){
	if( Vis[x] )Vis[x] = false , sum -= !--num[ v[x] ];
	else Vis[x] = true , sum += ( 1 == ++num[ v[x] ] );
}

void Solve( int x , int y ){
	while( x != y )
		if( Dep[x] > Dep[y] )modify( x ) , x = Fa[x][0];
		else modify( y ) , y = Fa[y][0];
}
