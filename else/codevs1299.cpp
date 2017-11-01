#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 5e5 + 10;

int n , m;

int Fa[maxn];
int Find( int x ){
	int t = x;
	while( t != Fa[t] )t = Fa[t];
	while( x != t ){
		int temp = Fa[x];
		Fa[x] = t;
		x = temp;
	}
	return t;
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Fa[i] = i;
	For( i , 1 , m ){
		int x , y;
		Read( x );Read( y );
		
		for( int j = Find( x ) ; j <= y && j ; j = Find( j ) ){
			--n;
			Fa[j] = j + 1;
		}
		
		printf("%d\n",n);
	}
	
	return 0;
}
