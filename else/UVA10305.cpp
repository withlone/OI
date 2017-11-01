#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

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

static const int maxn = 100 + 10;
static const int maxm = maxn * maxn;

int n;
int m;

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
}

int Idg[maxn];

void read_in(){
	Ct = 0;
	For( i , 1 , n )Idg[i] = Ht[i] = 0;
	For( i , 1 , m ){
		int x , y;
		scanf( x ) ; scanf( y ) ;
		Ins( x , y ) ; Idg[y]++ ;
	}
}

void tuopu(){
	int que[maxn] , H = 0 , T = -1 , cnt = 0;
	For( i , 1 , n )if( !Idg[i] )que[ ++T ] = i;
	while( H <= T ){
		int x = que[ H++ ];
		printf( x ) , putchar( ++cnt == n ? '\n' : ' ' );
		Rep( i , Ht[x] , Nt[i] )
			if( !--Idg[ To[i] ] )que[ ++T ] = To[i];
	}
}

int main(){
	
	while( scanf( n ) , scanf( m ) , n + m ){
		
		read_in();
		
		tuopu();
		
	}
	
	return 0;
}
