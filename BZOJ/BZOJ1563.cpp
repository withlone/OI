#include<cmath>
#include<cstdio>
#include<cstring>

using namespace std;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}

typedef long long LL;
typedef long double LD;
static const LD Inf = 1e18;
static const int MAXN = 1e5 +1;

int Case;char s[31];
int n , Std , P;
int H , T;
int L[MAXN] , R[MAXN] , p[MAXN];
LD f[MAXN] , Sum[MAXN];

void Init();
void Solve();
void Updata( int );

LD Pow( LD , int );
LD Calc( int , int );

int main(){
	
	Read( Case );
	while( Case-- )Solve();
	return 0;
}

void Init(){
	Read( n );Read( Std );Read( P );
	For( i , 1 , n )scanf("%s",s) , Sum[i] = Sum[i-1] + strlen( s );
}
void Solve(){
	Init();
	H = 0;T = 1;
	L[1] = 1;R[1] = n;p[1] = 0;
	For( i , 1 , n ){
		while( R[H] < i )H++;
		f[i] = Calc( p[H] , i );
		Updata( i );
	}
	if( f[n] <= Inf )printf("%lld\n",(long long)f[n]);
	else puts("Too hard to arrange");
	puts("--------------------");
}
void Updata( int x ){
	while( L[T] > x && Calc( p[T] , L[T] ) > Calc( x , L[T] ) )R[--T] = R[T+1];
	int l = L[T], r = R[T] , Res = R[T] + 1;
	while( l <= r ){
		int Mid = l + r >> 1;
		if( Calc( x , Mid ) < Calc( p[T] , Mid ) )r = Mid - 1 , Res = Mid;
		else l = Mid + 1;
	}
	if( Res <= R[T] ){
		R[++T] = R[T-1];
		L[T] = Res;
		p[T] = x;
		R[T-1] = Res - 1;
	}
}

LD Pow( LD x , int y ){
	LD Res = 1;
	for( ;y;x *= x , y>>=1 )
		if( y & 1 )Res *= x;
	return Res;
}
LD Calc( int x , int y ){ return f[x] + Pow( abs( Sum[y] - Sum[x] + y - ( x + 1 ) - Std ) , P ); }
