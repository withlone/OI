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

typedef long long LL;
static const int maxn = 1e5 +1;
static const int maxm = maxn << 1;

int n , m , q , Mct , Qct , Fac;
LL v[maxn] , w[maxn];
int c[maxn] , Lst[maxn];
int H[maxn] , Nt[maxm] , To[maxm] , Ct;
int Dep[maxn] , Dfn[maxn] , Fa[maxn][18] , Cnt;
int Stk[maxn] , tp , BL[maxn];
bool Vis[maxn];int num[maxn];
LL ans[maxn] , sum;

struct Modify{ int x , col1 , col2; }M[maxn];

struct Query{
	int l , r , id , x;
	bool operator < ( Query tmp ) const {
		return BL[l] < BL[tmp.l] || BL[l] == BL[tmp.l] && BL[r] < BL[tmp.r] || BL[l] == BL[tmp.l] && BL[r] == BL[tmp.r] && x < tmp.x ;
	}
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

void modify( int x ){
	if( !Vis[x] )Vis[x] = true , sum += w[ ++num[ c[x] ] ] * v[ c[x] ];
	else Vis[x] = false , sum -= w[ num[ c[x] ]-- ] * v[ c[x] ];
}

void Solve( int x , int y ){
	while( x != y )
		if( Dep[x] > Dep[y] )modify( x ) , x = Fa[x][0];
		else modify( y ) , y = Fa[y][0];
}

int main(){
	
	Read( n );Read( m );Read( q );Fac = pow( n , 2.0 / 3 );
	For( i , 1 , m )Read( v[i] );
	For( i , 1 , n )Read( w[i] );
	For( i , 1 , n - 1 ){
		int x , y;
		Read( x );Read( y );
		Ins( x , y );Ins( y , x );
	}
	For( i , 1 , n )Read( c[i] ) , Lst[i] = c[i];
	
	Ct = 0;
	Dep[1] = 1;
	Dfs( 1 );
	while( tp )BL[ Stk[ tp-- ] ] = Ct + 1;
	
	For( j , 1 , 17 )For( i , 1 , n )
		Fa[i][j] = Fa[ Fa[i][j-1] ][j-1];
	
	For( i , 1 , q ){
		int t , x , y;
		Read( t );Read( x );Read( y );
		if( !t )M[ ++Mct ] = (Modify){ x , Lst[x] , y } , Lst[x] = y;
		else{
			if( Dfn[x] > Dfn[y] )swap( x , y );
			Q[ ++Qct ] = (Query){ x , y , Qct , Mct };
		}
	}
	
	sort( 1 + Q , 1 + Qct + Q );
	
	int x = 0;
	Q[0].l = Q[0].r = 1;
	For( i , 1 , Qct ){
		while( x < Q[i].x ){
			++x;
			if( Vis[ M[x].x ] )sum = sum - w[ num[ c[ M[x].x ] ]-- ] * v[ c[ M[x].x ] ] + w[ ++num[ M[x].col2 ] ] * v[ M[x].col2 ];
			c[ M[x].x ] = M[x].col2;
		}
		while( x > Q[i].x ){
			if( Vis[ M[x].x ] )sum = sum - w[ num[ c[ M[x].x ] ]-- ] * v[ c[ M[x].x ] ] + w[ ++num[ M[x].col1 ] ] * v[ M[x].col1 ];
			c[ M[x].x ] = M[x].col1;
			--x;
		}
		Solve( Q[i - 1].l , Q[i].l );
		Solve( Q[i - 1].r , Q[i].r );
		int Lca = QLca( Q[i].l , Q[i].r );
		modify( Lca );
		ans[ Q[i].id ] = sum;
		modify( Lca );
	}
	
	For( i , 1 , Qct )printf("%lld\n",ans[i]);
	
	return 0;
}
