#include<algorithm>
#include<cstdio>
#include<cmath>

using std :: sort;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline Type max ( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

typedef long long LL;
static const int maxn = 1e5 +1;
static const int maxm = 7e6 +1;

int n , m , q , u , v , t;
int Que[3][maxm] , H[3] , T[3];

void Get( int &tmp , int &pos ){
	if( H[0] < T[0] )tmp = Que[0][ 1 + H[0] ] , pos = 0;
	if( H[1] < T[1] && Que[1][ 1 + H[1] ] > tmp )tmp = Que[1][ 1 + H[1] ] , pos = 1;
	if( H[2] < T[2] && Que[2][ 1 + H[2] ] > tmp )tmp = Que[2][ 1 + H[2] ] , pos = 2;
	H[pos]++;
}

bool cmp( int x , int y ){ return x > y ; }

int main(){
	
	freopen( "earthworm.in" , "r" , stdin ) ;
	freopen( "earthworm.out" , "w" , stdout ) ;
	
	Read( n );Read( m );Read( q );Read( u );Read( v );Read( t );
	
	For( i , 1 , n )Read( Que[0][i] );
	sort( 1 + Que[0] , 1 + n + Que[0] , cmp );
	
	T[0] = n;
	For( i , 1 , m ){
		int tmp = -0x7fffffff , pos;
		Get( tmp , pos );tmp += ( i - 1 ) * q;
		if( !( i % t ) )printf("%d ",tmp);
		int p1 = ( int )floor( ( long long )tmp * u * 1.0 / v ) , p2 = tmp - p1;
		Que[1][ ++T[1] ] = p1 - i * q;
		Que[2][ ++T[2] ] = p2 - i * q;
	}puts("");
	
	For( i , 1 , n + m ){
		int tmp = -0x7fffffff , pos;
		Get( tmp , pos );tmp += m * q;
		if( !( i % t ) )printf("%d ",tmp);
	}puts("");
	
	return 0;
}
