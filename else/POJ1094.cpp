#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type max( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 27;
static const int maxm = maxn * maxn;

int n;
int m;

int Getchar(){
	char ch = getchar();
	while( ch > 'Z' || ch < 'A' )ch = getchar();
	return ch - 'A' + 1;
}

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];

int Idg[maxn];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Idg[y]++;
}

int A[maxm];
int B[maxm];

void read_in(){
	For( i , 1 , m )A[i] = Getchar() , B[i] = Getchar();
}

int que[maxn];
int tuopu(){
	int idg[maxn];
	int H = 0 , T = -1;bool res = 0;
	For( i , 1 , n )if( !( idg[i] = Idg[i] ) )que[ ++T ] = i;
	while( H <= T ){
		if( T - H > 0 )res = true;
		int x = que[ H++ ] ;
		Rep( i , Ht[x] , Nt[i] )
			if( !--idg[ To[i] ] )que[ ++T ] = To[i];
	}
	if( H != n )return 1;
	if( res )return 2;
	return 0;
}

void working(){
	bool f = Ct = 0;
	For( i , 1 , n )Idg[i] = Ht[i] = 0;
	For( i , 1 , m ){
		Ins( A[i] , B[i] );
		switch( tuopu() ){
			case 0 :
				printf("Sorted sequence determined after %d relations: " , i );
				For( j , 0 , n - 1 )putchar( que[j] + 'A' - 1 );
				putchar( '.' ) , putchar( '\n' );f = 1;break;
			case 1 :
				printf("Inconsistency found after %d relations.\n" , i );f = 1;break;
		}
		if( f )break;
	}
	if( !f )puts("Sorted sequence cannot be determined.");
}

int main(){
	
	while( scanf( n ) , scanf( m ) , n + m ){
		
		read_in();
		
		working();
		
	}
	
	return 0;
}
