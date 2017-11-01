#include<map>
#include<cstdio>

using namespace std ;

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

typedef long long LL ;
static const LL maxn = 4e12 ;
static const int maxm = 1e8 + 10 ;

LL n ;

map < LL , LL > G ;

LL dfs( LL x ){
	if( !G[x] )
		G[x] = ( dfs( x / 2 ) + dfs( x / 3 ) + dfs( x / 5 ) + dfs( x / 7 ) ) ;
	return G[x] ;
}

int main(){
	
	freopen( "losttemple.in" , "r" , stdin ) ;
	freopen( "losttemple.out" , "w" , stdout ) ;
	
	scanf( "%lld" , &n ) ;
	
	G[0LL] = G[1LL] = 1LL ;
	
	printf("%lld\n" , dfs( n ) ) ;
	
	return 0 ;
}
