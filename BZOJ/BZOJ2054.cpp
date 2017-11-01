#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e5 + 10;
static const int maxm = 1e6 + 10;

int n , m , p , q;
int Col[maxm];

int Fa[maxm];
int Find( int x ){
	int t = x;
	while( t != Fa[t] )t = Fa[t];
	while( t != x ){
		int temp = Fa[x];
		Fa[x] = t;
		x = temp;
	}
	return t;
}

int main(){
	
	Read( n );Read( m );Read( p );Read( q );
	For( i , 1 , n )Fa[i] = i;
	
	Lop( i , m , 1 ){
		int x = ( i * p + q ) % n + 1 , y = ( i * q + p ) % n + 1;
		if( x > y )x ^= y ^= x ^= y;
		for( int j = Find( x ) ; j <= y && j ; j = Find( j ) ){
			Col[j] = i;
			Fa[j] = j + 1;
		}
	}
	
	For( i , 1 , n )printf("%d\n",Col[i]);
	
	return 0;
}
