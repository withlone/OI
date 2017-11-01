#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 100 + 10;
static const int maxm = 1000 + 10;

int T , n , m;

int Fa[maxn] , dis[maxn];

int Find( int x ){
	if( x == Fa[x] )return x;
	int t = Find( Fa[x] );
	dis[x] += dis[ Fa[x] ];
	return Fa[x] = t;
}

int main(){
	
	Read( T );
	
	while( T-- ){
		
		Read( n );Read( m );
		
		For( i , 0 , n )Fa[i] = i , dis[i] = 0;
		
		bool ans = false;
		
		For( i , 1 , m ){
			int x , y , z;
			Read( x );Read( y );Read( z );--x;
			if( z < 0 )z = -z;else x ^= y ^= x ^= y;
			if( ans )continue;
			int fx = Find( x ) , fy = Find( y );
			if( fx == fy )ans = ( dis[x] - dis[y] != z );
			else if( dis[x] >= z + dis[y] )Fa[fy] = fx , dis[fy] = dis[x] - dis[y] - z;
			else Fa[fx] = fy , dis[fx] = dis[y] + z - dis[x];
		}
		
		puts( !ans ? "true" : "false" );
		
	}
	
	return 0;
}
