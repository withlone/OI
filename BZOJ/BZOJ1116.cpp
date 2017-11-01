#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e5 + 10;
static const int maxm = 2e5 + 10;

int n , m;
int Fa[maxn];
bool V[maxn];

int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Fa[i] = i;
	For( i , 1 , m ){
		int x , y , fx , fy;
		Read( x );Read( y );
		fx = Find( x );fy = Find( y );
		if( fx == fy )V[fx] = true;
		else Fa[fx] = fy;
	}
	
	For( i , 1 , n )V[ Find( i ) ] |= V[i];
	
	For( i , 1 , n )
		if( !V[ Find( i ) ] )return puts("NIE") , 0 ;
	
	puts("TAK");
	
	return 0;
}
