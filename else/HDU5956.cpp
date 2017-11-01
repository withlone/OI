#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
using namespace std;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )
#define Rep( i , _Begin , _Add ) for( int i=(_Begin);i; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

typedef long long LL;
typedef pair< bool , int > Pair;
static const int MAXN = 1e5 +1;

int Case , n , P , u , v , w;LL Ans;
LL f[MAXN] , d[MAXN];
int Que[MAXN] , H , T;
int Ht[MAXN] , Nt[MAXN<<1] , To[MAXN<<1] , Dt[MAXN<<1] , Ct;

LL Sqr( LL );
LL Up( int , int );
LL Down( int , int );
void Dfs( int , int );
void Ins( int , int , int );

int main(){
	
	Read( Case );
	while( Case-- ){
		H = T = Ans = Ct = 0;memset( Ht , 0 , sizeof Ht );
		Read( n );Read( P );
		For( i , 1 , n - 1 ){
			Read( u );Read( v );Read( w );
			Ins( u , v , w );Ins( v , u , w );
		}
		f[1] = -P;
		Dfs( 1 , 0 );
		
		printf("%lld\n",Ans);
	}
	return 0;
}

void Ins( int F , int T , int D ){
	Nt[++Ct] = Ht[F];
	Ht[F] = Ct;
	To[Ct] = T;
	Dt[Ct] = D;
}
LL Sqr( LL x ){ return x * x; }
LL Up( int x , int y ){ return f[x] + Sqr( d[x] ) - f[y] - Sqr( d[y] ); }
LL Down( int x , int y ){ return d[x] - d[y] << 1; }
void Dfs( int x , int Fa ){
	stack< Pair >Stk;
	if( x != 1 ){
		while( H < T && Up( Que[H+1] , Que[H] ) <= d[x] * Down( Que[H+1] , Que[H] ) )
			Stk.push( make_pair( 0 , Que[H++] ) );
		f[x] = f[Que[H]] + Sqr( d[x] - d[Que[H]] ) + 1LL*P;
		while( H < T && Up( x , Que[T] ) * Down( Que[T] , Que[T-1] ) <= Up( Que[T] , Que[T-1] ) * Down( x , Que[T] ) )
			Stk.push( make_pair( 1 , Que[T--] ) );
	}
	Que[++T] = x;
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( y == Fa )continue;
		d[y] = d[x] + Dt[i];
		Dfs( y , x );
	}
	T--;
	while( !Stk.empty() ){
		Pair tmp = Stk.top();Stk.pop();
		if( !tmp.first ) Que[--H] = tmp.second;
		else Que[++T] = tmp.second;
	}
	Ans = max( Ans , f[x] );
}
