#include<cstdio>
#include<algorithm>

using std :: min;
using std :: max;
using std :: sort;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )
#define Rep( i , _Begin , _Add ) for( int i=(_Begin);i; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

typedef long long LL;
static const LL  Inf  = 1e18;
static const int MAXN = 1e5 +1;

struct Data{
	int rk , val;
	bool operator < ( Data tmp ) const { return val > tmp.val; }
}A[MAXN];

int n , u , v , w;
bool Vis[MAXN];
int Stk[MAXN] , Tp;
int S[MAXN] , V[MAXN] , Sz[MAXN] , F[MAXN] , Fa[MAXN];
int Ht[MAXN] , Nt[MAXN<<1] , To[MAXN<<1] , Dt[MAXN<<1] , Ct;
LL f[MAXN] , d[MAXN];

void Init();
void Dfs( int );
void Get_d( int );
void CDQ( int , int );
double Slope( int , int );
void Ins( int , int , int );
void Get_root( int , int , int& );

int main(){
	
	#define Judge
	
	#ifdef Judge
		freopen("harbingers.in","r",stdin);
		freopen("harbingers.out","w",stdout);
	#endif
	
	Init();
	
	CDQ( 1 , n );
	
	For( i , 2 , n )printf("%lld ",f[i] + S[i]);
	
	return 0;
}

void Init(){
	Read( n );
	For( i , 1 , n-1 )Read( u ) , Read( v ) , Read( w ) , Ins( u , v , w ) , Ins( v , u , w );
	For( i , 2 , n )Read( S[i] ) , Read( V[i] ) , f[i] = Inf;
	Ct = 0;Get_d( 1 );F[0] = n + 1;
}
void Ins( int F , int T , int D ){
	Nt[++Ct] = Ht[F];
	Ht[F] = Ct;
	To[Ct] = T;
	Dt[Ct] = D;
}
void Get_d( int x ){
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( y == Fa[x] )continue;
		Fa[y] = x;d[y] = d[x] + Dt[i];
		Get_d( y );
	}
}
void Get_root( int x , int Sum , int& rt ){
	Sz[x] = 1;F[x] = 0;
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( Vis[y] || y == Fa[x] )continue;
		Get_root( y , Sum , rt );
		Sz[x] += Sz[y];F[x] = max( F[x] , Sz[y] );
	}
	F[x] = max( F[x] , Sum - Sz[x] );
	if( Sz[x] > 1 && F[x] < F[rt] )rt = x;
}
void Dfs( int x ){
	A[++Ct] = (Data){ x , d[x] };
	Rep( i , Ht[x] , Nt[i] )if( !Vis[To[i]] && To[i] != Fa[x] )Dfs( To[i] );
}
double Slope( int x , int y ){ return 1.0 * ( f[x] + S[x] - f[y] - S[y] ) / ( d[x] - d[y] ); }
void CDQ( int x , int Sum ){
	if( Sum == 1 )return;
	int rt = 0;
	Get_root( x , Sum , rt );
	Rep( i , Ht[rt] , Nt[i] )if( To[i] != Fa[rt] )Vis[To[i]] = true;
	CDQ( x , Sum - Sz[rt] + 1 );
	Tp = Ct = 0;
	Rep( i , Ht[rt] , Nt[i] )if( To[i] != Fa[rt] )Dfs( To[i] );
	sort( 1 + A , 1 + Ct + A );
	int p = rt;
	For( i , 1 , Ct ){
		while( p != Fa[x] ){
			while( Tp > 1 && Slope( p , Stk[Tp] ) >= Slope( Stk[Tp] , Stk[Tp-1] ) )Tp--;
			Stk[++Tp] = p;p = Fa[p];
		}
		if( Tp ){
			int l = 1 , r = Tp;
			while( l <= r ){
				int Mid = l + r >>1;if( Mid == Tp ){ l = Mid;break; }
				if( Slope( Stk[Mid+1] , Stk[Mid] ) >= V[A[i].rk] )l = Mid + 1;
				else r = Mid - 1;
			}
			f[A[i].rk] = min( f[A[i].rk] , f[Stk[l]] + ( d[A[i].rk] - d[Stk[l]] ) * V[A[i].rk] + S[Stk[l]] );
		}
	}
	Rep( i , Ht[rt] , Nt[i] )if( To[i] != Fa[rt] )CDQ( To[i] , Sz[To[i]] );
}/*
5
1 2 20
2 3 12
2 4 1
4 5 3
26 9
1 10
500 2
2 30

*/
