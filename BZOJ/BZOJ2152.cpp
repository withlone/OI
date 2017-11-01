#include<cstdio>
#include<algorithm>
using namespace std;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )
#define Rep( i , _Begin , _Add ) for( int i=(_Begin);i; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 2e4 +1;

int n , u , v , w , Rt , Sum , Ans , Up , Down;
int H[MAXN] , Nt[MAXN<<1] , To[MAXN<<1] , Dt[MAXN<<1] , Ct;
int f[MAXN] , Sz[MAXN] , d[MAXN] , Cnt[3];
bool Vis[MAXN];

void Ins( int , int , int );
void Get_root( int , int );
void Get_deep( int , int );
int Calc( int , int );
void Sol( int );
int Gcd( int , int );

int main(){
	
	Read( n );
	For( i , 1 , n-1 ){
		Read( u );Read( v );Read( w );
		Ins( u , v , w );Ins( v , u , w );
	}
	
	Sum = n;
	f[0] = 0x7fffffff;
	Get_root( 1 , 0 );
	Sol( Rt );
	
	Up = Ans;
	Down = n*n;
	int tmp = Gcd( Up , Down );
	printf("%d/%d\n",Up/tmp,Down/tmp);
	
	return 0;
}
int Gcd( int x , int y ){
	while( x ^= y ^= x ^= y %= x );
	return y;
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
		if( y == Fa || Vis[y] )continue;
		Get_root( y , x );
		Sz[x] += Sz[y];
		f[x] = max( f[x] , Sz[y] );
	}
	f[x] = max( f[x] , Sum - Sz[x] );
	if( f[x] < f[Rt] )Rt = x;
}
void Get_deep( int x , int Fa ){
	Cnt[d[x]%3]++;
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( y == Fa || Vis[y] )continue;
		d[y] = d[x] + Dt[i];
		Get_deep( y , x );
	}
}
int Calc( int x , int v ){
	d[x] = v;
	Cnt[0] = Cnt[1] = Cnt[2] = 0;
	Get_deep( x , 0 );
	return Cnt[0] * Cnt[0] + 2 * Cnt[1] * Cnt[2];
}
void Sol( int x ){
	Ans += Calc( x , 0 );
	Vis[x] = true;
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( Vis[y] )continue;
		Ans -= Calc( y , Dt[i] );
		Rt = 0;Sum = Sz[y];
		Get_root( y , 0 );
		Sol( Rt );
	}
}
