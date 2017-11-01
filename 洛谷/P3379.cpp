#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type min ( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 5e5 + 10;
static const int maxm = maxn << 1;
static const int maxx = 21;

int n , m , rt;

namespace Fast_Lca{
	
	int bin[maxx] , Log[maxm];
	int ST[maxm][maxx];
	int Dep[maxn] , pos[maxn] , cnt;
	int H[maxn] , Nt[maxm] , To[maxm] , Ct;
	void Ins( int x , int y ){
		Nt[ ++Ct ] = H[x];
		H[x] = Ct;
		To[Ct] = y;
	}
	
	void Dfs( int x , int f ){
		Dep[x] = Dep[f] + 1;
		ST[ ++cnt ][0] = x;
		if( !pos[x] )pos[x] = cnt;
		Rep( i , H[x] , Nt[i] ){
			int y = To[i];
			if( y == f )continue;
			Dfs( y , x );
			ST[ ++cnt ][0] = x;
		}
	}
	
	void Init(){
		Dfs( rt , 0 );
		Dep[0] = 0x7fffffff;
		bin[0] = 1;
		For( i , 1 , 20 )bin[i] = bin[i - 1] << 1;
		For( i , 2 , cnt )Log[i] = Log[i >> 1] + 1;
		Lop( i , cnt , 1 )
			For( j , 1 , 20 )
				if( i + bin[j] - 1 > cnt )break;
				else ST[i][j] = ( Dep[ ST[i][j - 1] ] < Dep[ ST[i + bin[j - 1]][j - 1] ] ? ST[i][j - 1] : ST[i + bin[j - 1]][j - 1] );
	}
	
	int Rmq( int l , int r ){
		int t = Log[r - l + 1];
		return Dep[ ST[l][t] ] < Dep[ ST[r - bin[t] + 1][t] ] ?
			ST[l][t] : ST[r - bin[t] + 1][t];
	}
	
}using namespace Fast_Lca;

int main(){
	
	Read( n );Read( m );Read( rt );
	For( i , 1 , n - 1 ){
		int x , y;
		Read( x );Read( y );
		Ins( x , y );Ins( y , x );
	}
	
	Init();
	
	while( m-- ){
		int x , y;
		Read( x );Read( y );
		if( pos[x] > pos[y] )x ^= y ^= x ^= y;
		printf("%d\n",Rmq( pos[x] , pos[y] ));
	}
	
	return 0;
}
