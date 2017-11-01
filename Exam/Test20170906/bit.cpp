#include<cstdio>
#include<algorithm>

using namespace std ;

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

static const int maxn = 1e4 + 10 ;
static const int maxm = 1e5 + 10 ;

int n ;
int cnt ;

int pos[maxm] ;

void init(){
	pos[ ++cnt ] = 1 ;
	for( ; pos[cnt] <= 1e9 ; ++cnt )
		pos[cnt + 1] = pos[cnt] + cnt ;
}

int main(){
	
	freopen( "bit.in" , "r" , stdin ) ;
	freopen( "bit.out" , "w" , stdout ) ;
	
	init() ;
	
	scanf( n ) ;
	
	while( n-- ){
		int x , y ;
		scanf( x ) ;
		y = lower_bound( 1 + pos , 1 + cnt + pos , x ) - pos ;
		puts( pos[y] == x ? "1" : "0" ) ;
	}
	
	return 0 ;
}
