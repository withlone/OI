#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}
template< typename Type >inline void printf( Type x ){
	if( x > 9 )printf( x / 10 );
	putchar( x % 10 + '0' );
}

static const int maxn = 4e3 + 10;
static const int maxm = 2e5 + maxn;

int n;
int ans[maxn];

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
}

bool V[maxn];
int dct;
int dfn[maxn];
int Low[maxn];
int tp;
int stack[maxn];
int cnt;
int bel[maxn];

void tarjan( int x ){
	int y;
	V[x] = true;
	stack[ ++tp ] = x;
	dfn[x] = Low[x] = ++dct;
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( !dfn[y] )tarjan( y ) , Low[x] = min( Low[x] , Low[y] );
		else if( V[y] )Low[x] = min( Low[x] , dfn[y] );
	}
	if( dfn[x] != Low[x] )return;
	++cnt;
	do{
		y = stack[ tp-- ];
		V[y] = false;
		bel[y] = cnt;
	}while( x != y );
}

int main(){
	
	Read( n );
	
	For( i , 1 , n ){
		int m , x;
		Read( m );
		while( m-- ){
			Read( x );
			Ins( i , x + n );
		}
	}
	
	For( i , 1 , n ){
		int x;
		Read( x );
		Ins( x + n , i );
	}
	
	For( i , 1 , n << 1 )if( !dfn[i] )
		tarjan( i );
	
	For( i , 1 , n ){
		
		int size = 0;
		Rep( j , Ht[i] , Nt[j] )
			if( bel[i] == bel[ To[j] ] )
				ans[ ++size ] = To[j] - n;
		
		sort( 1 + ans , 1 + size + ans );
		
		printf( size );
		For( j , 1 , size )
			putchar( ' ' ) , printf( ans[j] );
		
		putchar( '\n' );
		
	}
	
	return 0;
}
