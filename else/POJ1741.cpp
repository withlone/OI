#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )
#define Rep( i , _Begin , _Add ) for( int i=(_Begin);i; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e4 +1;

int n , k , u , v , w , Sum , Ans , Rt;
int H[MAXN] , Nt[MAXN<<1] , To[MAXN<<1] , Dt[MAXN<<1] , Ct;
int Sz[MAXN] , f[MAXN] , Dep[MAXN] , d[MAXN];
bool Vis[MAXN];

void Ins( int , int , int );
void Get_root( int , int );
void Get_deep( int , int );
int Cal( int , int );
void Sol( int );


int main(){
	
	f[0] = 0x7fffffff;
	while( ~scanf("%d%d",&n,&k) , n+k ){
		Ans = Rt = Ct = 0;Sum = n;
		memset( H , 0 ,sizeof H );
		memset( Vis , 0 , sizeof Vis );
		For( i , 1 , n-1 ){
			Read( u );Read( v );Read( w );
			Ins( u , v , w );Ins( v , u , w );
		}
		Get_root( 1 , 0 );
		Sol( Rt );
		printf("%d\n",Ans);
	}
	return 0;
}

void Ins( int F , int T , int D ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
	Dt[Ct] = D;
}
void Get_root( int x , int Fa ){
	Sz[x] = 1;f[x] = 0;
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( Vis[y] || y == Fa )continue;
		Get_root( y , x );
		Sz[x] += Sz[y];
		f[x] = max( f[x] , Sz[y] );
	}
	f[x] = max( f[x] , Sum - Sz[x] );
	if( f[x] < f[Rt] )Rt = x;
}
void Get_deep( int x , int Fa ){
	Dep[++Dep[0]] = d[x];
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( Vis[y] || y == Fa )continue;
		d[y] = d[x] + Dt[i];
		Get_deep( y , x );
	}
}
int Cal( int x , int v ){
	d[x] = v;Dep[0] = 0;
	Get_deep( x , 0 );
	sort( 1 + Dep , 1 + Dep[0] + Dep );
	int l = 1 , r = Dep[0] , Res = 0;
	while( l < r )
		if( Dep[l] + Dep[r] <= k )Res += r - (l++);
		else r--;
	return Res;
}
void Sol( int x ){
	Ans += Cal( x , 0 );
	Vis[x] = true;
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( Vis[y] )continue;
		Ans -= Cal( y , Dt[i] );
		Rt = 0;Sum = Sz[y];
		Get_root( y , 0 );
		Sol( Rt );
	}
}
