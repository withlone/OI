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
static const LL Inf   = 1e18;
static const int MAXN = 2e5 +1;

struct Data{
	int rk;LL val;
	bool operator < ( Data tmp ) const { return val > tmp.val; }
}A[MAXN];

int n , type;LL w;
int Stk[MAXN] , Tp;
int Fa[MAXN] , F[MAXN] , Sz[MAXN];LL pv[MAXN] , qv[MAXN] , lv[MAXN];
int H[MAXN] , Nt[MAXN<<1] , To[MAXN<<1] , Ct;LL Dt[MAXN<<1];
LL f[MAXN] , d[MAXN];bool Vis[MAXN];

void Init();
void Get_d( int );
void Ins( int , int , int );

void Dfs( int );
void CDQ( int , int );
double Slope( int , int );
void Get_root( int , int , int& );

int main(){
	
	Init();
	
	CDQ( 1 , n );
	
	For( i , 2 , n )printf("%lld\n",f[i]);
	
	return 0;
}

void Init(){
	Read( n );Read( type );
	For( i , 2 , n ){
		Read( Fa[i] );Read( w );Read( pv[i] );Read( qv[i] );Read( lv[i] );
		Ins( Fa[i] , i , w );f[i] = Inf;
	}
	Get_d( 1 );F[0] = n + 1;Ct = 0;
}
void Ins( int F , int T , int D ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
	Dt[Ct] = D;
}
void Get_d( int x ){ Rep( i , H[x] , Nt[i] )d[To[i]] = d[x] + Dt[i] , Get_d( To[i] ); }

void Dfs( int x ){
	A[++Ct] = (Data){ x , d[x] - lv[x] };
	Rep( i , H[x] , Nt[i] )if( !Vis[To[i]] )Dfs( To[i] );
}
void Get_root( int x , int Sum , int& rt ){
	Sz[x] = 1;F[x] = 0;
	Rep( i , H[x] , Nt[i] )if( !Vis[To[i]] ){
		Get_root( To[i] , Sum , rt );
		Sz[x] += Sz[To[i]];F[x] = max( F[x] , Sz[To[i]] );
	}
	F[x] = max( F[x] , Sum - Sz[x] );
	if( Sz[x] > 1 && F[x] < F[rt] )rt = x;
}
double Slope( int x , int y ){ return 1.0 * ( f[x] - f[y] ) / ( d[x] - d[y] ); }
void CDQ( int x , int Sum ){
	if( Sum == 1 )return;
	int rt = 0;
	Get_root( x , Sum , rt );
	Rep( i , H[rt] , Nt[i] )Vis[To[i]] = true;
	CDQ( x , Sum - Sz[rt] + 1 );
	Tp = Ct = 0;
	Rep( i , H[rt] , Nt[i] )Dfs( To[i] );
	sort( 1 + A , 1 + Ct + A );
	int p = rt;
	For( i , 1 , Ct ){
		while( p != Fa[x] && d[A[i].rk] - d[p] <= lv[A[i].rk] ){
			while( Tp > 1 && Slope( p , Stk[Tp] ) >= Slope( Stk[Tp] , Stk[Tp-1] ) )Tp--;
			Stk[++Tp] = p;p = Fa[p];
		}
		if( Tp ){
			int l = 1 , r = Tp;
			while( l <= r ){
				int Mid = l + r >>1;if( Mid == Tp ){ l = Tp;break; }
				if( Slope( Stk[Mid+1] , Stk[Mid] ) >= pv[A[i].rk] )l = Mid + 1;
				else r = Mid - 1;
			}
			f[A[i].rk] = min( f[A[i].rk] , f[Stk[l]] + ( d[A[i].rk] - d[Stk[l]] ) * pv[A[i].rk] + qv[A[i].rk] );
		}
	}
	Rep( i , H[rt] , Nt[i] )CDQ( To[i] , Sz[To[i]] );
}
