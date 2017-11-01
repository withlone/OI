#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' )f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';In *= f;
}
#define Read( x ) scanf("%d",&x)

static const int MAXN = 262150;

int n , m;

namespace Zkw{
	
	int M;
	int Sum[MAXN] , Left[MAXN] , _D[MAXN];
	
	void Modify( int l , int r , int K , int D ){
		for( int s = l + M - 1 , t = r + M + 1 ; s ^ t ^ 1 ; s >>= 1 , t >>= 1 ){
			if( ~s & 1 )Sum[ s^1 ] += ( Left[ s^1 ] - l ) * D + K , _D[ s^1 ] += D;
			if(  t & 1 )Sum[ t^1 ] += ( Left[ t^1 ] - l ) * D + K , _D[ t^1 ] += D;
		}
	}
	
	int Query( int x ){
		int Res = 0;
		for( int i = x + M ; i ; i >>= 1 )Res += Sum[i] + ( x - Left[i] ) * _D[i];
		return Res;
	}
	
}using namespace Zkw;

int main(){
	
	Read( n );Read( m );
	for( M = 1 ; M < n + 2 ; M <<= 1 );
	For( i , 1 , n )Read( Sum[ i + M ] ) , Left[ i + M ] = i;
	Rep( i , M , 1 )Left[i] = Left[ i<<1 ];
	
	while( m-- ){
		int opt , l , r , K , D;
		Read( opt );
		if( opt == 1 )Read( l ) , Read( r ) , Read( K ) , Read( D ) , Modify( l , r , K , D );
		else Read( K ) , printf("%d\n",Query( K ));
	}
	
	return 0;
}
