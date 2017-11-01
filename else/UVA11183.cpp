#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}
template< typename Type >inline void printf( Type x ){
	if( x < 0 )putchar( '-' ) , x = -x;
	if( x > 9 )printf( x / 10 );
	putchar( x % 10 + '0' );
}

static const int Inf = 1e4;
static const int maxn = 1e3 + 10;
static const int maxm = 4e4 + 10;

int cases;
int n;
int m;

struct edge{ int x , y , z ; }e[maxm];

int in[maxn];
int Fa[maxn];
int pre[maxn];
int bel[maxn];

bool LZ(){
	int res = 0;
	while( true ){
		
		For( i , 1 , n )in[i] = Inf , bel[i] = Fa[i] = pre[i] = 0;bel[1] = 1;
		
		For( i , 1 , m )
			if( e[i].x != e[i].y && e[i].z < in[ e[i].y ] )
				in[ e[i].y ] = e[i].z , pre[ e[i].y ] = e[i].x;
		
		For( i , 2 , n )if( !pre[i] )return false;
		
		int cnt = 1;
		
		For( i , 2 , n ){
			res += in[i];
			int x = i , y;
			while( x != 1 && Fa[x] != i && !bel[x] )Fa[x] = i , x = pre[x];
			if( x != 1 && !bel[x] ){
				++cnt;y = x;
				do{
					bel[y] = cnt;
					y = pre[y];
				}while( x != y );
			}
		}
		
		if( cnt == 1 )return printf( res ) , putchar( '\n' ) , true;
		
		For( i , 2 , n )if( !bel[i] )bel[i] = ++cnt;
		n = cnt;
		
		For( i , 1 , m ){
			e[i].z -= in[ e[i].y ];
			e[i].x = bel[ e[i].x ];e[i].y = bel[ e[i].y ];
		}
		
	}
}

int main(){
	
	scanf( cases );
	
	For( I , 1 , cases ){
		
		printf("Case #%d: " , I );
		
		scanf( n );scanf( m );
		
		For( i , 1 , m )
			scanf( e[i].x ) , scanf( e[i].y ) , scanf( e[i].z ) ,
			++e[i].x , ++e[i].y;
		
		if( !LZ() )puts("Possums!");
		
	}
	
	return 0;
}
