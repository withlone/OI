#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )
#define mem( x ) memset( x , 0 , sizeof x )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 1e5 +1;
static const int maxm = maxn << 1;

int T , n , m , Qct1 , Qct2 , Ct , Cnt , Dfn_Cnt , Fac1 , Fac2;
int v[maxn] , w[maxn] , val[maxn];
int _v[maxn] , _w[maxn] , _val[maxn];
int Dep[maxn] , Dfn[maxn] , End[maxn] , Fa[maxn][18];
int Stk[maxn] , tp , BL[maxn];
int H[maxn] , Nt[maxm] , To[maxm];
bool Vis[maxn];int num[maxn];LL sum[maxn] , ans[maxn];

struct Query1{
	int l , r , p , q , id;
	bool operator < ( Query1 t ) const { return l/Fac1 < t.l/Fac1 || l/Fac1 == t.l/Fac1 && r/Fac1 < t.r/Fac1 || l/Fac1 == t.l/Fac1 && r/Fac1 == t.r/Fac1 && r < t.r; }
}Q1[maxn];

struct Query2{
	int l , r , p , q , id;
	bool operator < ( Query2 t ) const { return BL[l] < BL[t.l] || BL[l] == BL[t.l] && BL[r] < BL[t.r] || BL[l] == BL[t.l] && BL[r] == BL[t.r] && Dfn[r] < Dfn[t.r]; }
}Q2[maxn];

void modify( int );
void Ins( int , int );
void Solve( int , int );
LL Gcd( LL , LL );
int Dfs( int );
int QLca( int , int );

int main(){
	
	Read( T );
	
	For( Case , 1 , T ){
		
		tp = Qct1 = Qct2 = Ct = Dfn_Cnt = 0;
		mem( H );mem( Dep );mem( num );mem( sum );mem( Vis );mem( Fa );
		
		Read( n );Read( m );Fac1 = sqrt( n + 0.5 );Fac2 = pow( n , 2.0 / 3 ) * 0.5;
		
		For( i , 1 , n )Read( v[i] ) , val[i] = w[i] = v[i];
		
		sort( 1 + w , 1 + n + w );
		Cnt = unique( 1 + w , 1 + n + w ) - w - 1;
		For( i , 1 , n )v[i] = lower_bound( 1 + w , 1 + Cnt + w , v[i] ) - w;
		
		For( i , 1 , n - 1 ){
			int x , y;
			Read( x );Read( y );
			Ins( x , y );Ins( y , x );
		}
		
		Ct = 0;
		Dep[1] = 1;
		Dfs( 1 );
		++Ct;
		while( tp )BL[ Stk[ tp-- ] ]= Ct;
		
		For( j , 1 , 17 )For( i , 1 , n )
			Fa[i][j] = Fa[ Fa[i][j - 1] ][j - 1];
		
		For( i , 1 , m ){
			int opt , x , y , p , q;
			Read( opt );Read( x );Read( y );Read( p );Read( q );
			if( opt == 1 )Q1[ ++Qct1 ] = (Query1){ Dfn[x] , End[x] , p , q , i };
			else Q2[ ++Qct2 ] = (Query2){ x , y , p , q , i };
		}
		
		sort( 1 + Q1 , 1 + Qct1 + Q1 );
		sort( 1 + Q2 , 1 + Qct2 + Q2 );
		
		int l = 1 , r = 0;
		For( i , 1 , Qct1 ){
			while( r < Q1[i].r )++r , sum[ num[ _v[r] ] ] -= _val[r] , sum[ ++num[ _v[r] ] ] += _val[r];
			while( l > Q1[i].l )--l , sum[ num[ _v[l] ] ] -= _val[l] , sum[ ++num[ _v[l] ] ] += _val[l];
			while( r > Q1[i].r )sum[ num[ _v[r] ] ] -= _val[r] , sum[ --num[ _v[r] ] ] += _val[r] , --r;
			while( l < Q1[i].l )sum[ num[ _v[l] ] ] -= _val[l] , sum[ --num[ _v[l] ] ] += _val[l] , ++l;
			ans[ Q1[i].id ] = Gcd( sum[ Q1[i].p ] , sum[ Q1[i].q ] );
		}
		
		mem( num );mem( sum );
		
		Q2[0].l = Q2[0].r = 1;
		For( i , 1 , Qct2 ){
			Solve( Q2[i - 1].l , Q2[i].l );
			Solve( Q2[i - 1].r , Q2[i].r );
			int Lca = QLca( Q2[i].l , Q2[i].r );
			modify( Lca );ans[ Q2[i].id ] = Gcd( sum[ Q2[i].p ] , sum[ Q2[i].q ] );modify( Lca );
		}
		
		printf("Case #%d:\n",Case);
		For( i , 1 , m )printf("%lld\n",ans[i]);
		
	}
	
	return 0;
}

void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

LL Gcd( LL x , LL y ){ return !y ? x : Gcd( y , x % y ) ; }

int Dfs( int x ){
	int size = 0;
	Dfn[x] = ++Dfn_Cnt;
	_v[ Dfn_Cnt ] = v[x];_w[ Dfn_Cnt ] = w[x];_val[ Dfn_Cnt ] = val[x];
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( y == Fa[x][0] )continue;
		Fa[y][0] = x;
		Dep[y] = Dep[x] + 1;
		size += Dfs( y );
		if( size >= Fac2 ){
			++Ct;
			while( size-- )BL[ Stk[ tp-- ] ] = Ct;
			size = 0;
		}
	}
	End[x] = Dfn_Cnt;
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
	if( Vis[x] )Vis[x] = false , sum[ num[ v[x] ] ] -= val[x] , sum[ --num[ v[x] ] ] += val[x];
	else Vis[x] = true , sum[ num[ v[x] ] ] -= val[x] , sum[ ++num[ v[x] ] ] += val[x];
}

void Solve( int x , int y ){
	while( x != y )
		if( Dep[x] > Dep[y] )modify( x ) , x = Fa[x][0];
		else modify( y ) , y = Fa[y][0];
}
