#include<cstdio>
#include<cstring>

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

static const int maxn = 10;

int A[5][5];
int ps[maxn][2];

void init(){
	For( i , 1 , 9 ){
		int x = ( i - 1 ) / 3 + 1;
		int y = ( i - 1 ) % 3 + 1;
		ps[i][0] = x;ps[i][1] = y;
	}
}

bool read_in(){
	bool f = 0;
	For( i , 1 , 4 )For( j , 1 , 4 ){
		scanf( A[i][j] );
		if( i > ps[ A[i][j] ][0] + 1 || i < ps[ A[i][j] ][0]
		 || j > ps[ A[i][j] ][1] + 1 || j < ps[ A[i][j] ][1] )
		 	f = true;
	}
	return f;
}

int Ct;
int Ht[maxn];
int Nt[maxn << 2];
int To[maxn << 2];
int Idg[maxn];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Idg[y]++;
}

void build_edge(){
	Ct = 0;
	For( i , 1 , 9 )Idg[i] = Ht[i] = 0;
	For( i , 1 , 9 )
		For( x , ps[i][0] , ps[i][0] + 1 )
			For( y , ps[i][1] , ps[i][1] + 1 )
				if( A[x][y] != i )Ins( i , A[x][y] );
}

bool tuopu(){
	int que[maxn] , H = 0 , T = -1;
	For( i , 1 , 9 )if( !Idg[i] )que[ ++T ] = i;
	while( H <= T ){
		int x = que[ H++ ];
		Rep( i , Ht[x] , Nt[i] )
			if( !--Idg[ To[i] ] )que[ ++T ] = To[i];
	}
	return H != 9;
}

int main(){
	
	init();
	
	while( true ){
		
		char opt[20];
		
		scanf( "%s" , opt );
		
		if( !strcmp( opt , "ENDOFINPUT" ) )break;
		
		if( read_in() )puts("THESE WINDOWS ARE BROKEN");
		else{
			
			build_edge();
			
			puts( tuopu() ? "THESE WINDOWS ARE BROKEN" : "THESE WINDOWS ARE CLEAN" );
			
		}
		
		scanf( "%s" , opt );
		
	}
	
	return 0;
}
