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

static const int maxn = 1e4 + 10;
static const int maxm = 2e4 + 10;

int n;
int m;

char Getchar(){
	char ch = getchar();
	while( ch != '<' && ch != '=' && ch != '>' )ch = getchar();
	return ch;
}

int Fa[maxn];

int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

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
char rela[maxm];
bool V[maxn];

bool read_in(){
	int tot = Ct = 0;
	For( i , 1 , n )Fa[i] = i , V[i] = Idg[i] = Ht[i] = 0;
	For( i , 1 , m )
		scanf( A[i] ) , rela[i] = Getchar() , scanf( B[i] ) , ++A[i] , ++B[i];
	For( i , 1 , m )if( rela[i] == '=' )
		Fa[ Find( A[i] ) ] = Find( B[i] );
	For( i , 1 , m )V[ A[i] ] = V[ B[i] ] = true;
	For( i , 1 , m )
		if( rela[i] == '<' )Ins( Find( A[i] ) , Find( B[i] ) );
		else if( rela[i] == '>' )Ins( Find( B[i] ) , Find( A[i] ) );
	For( i , 1 , n )if( !V[i] )return false;
	return true;
}

int f;

int tuopu(){
	int que[maxn] , H = 0 , T = -1;f = 0;
	For( i , 1 , n )if( !Idg[i] && Find( i ) == i )que[ ++T ] = i;
	while( H <= T ){
		if( T - H > 0 )f = 2;
		int x = que[ H++ ];
		Rep( i , Ht[x] , Nt[i] )
			if( Find( x ) == Find( To[i] ) )return 1;
			else if( !--Idg[ To[i] ] )que[ ++T ] = To[i];
	}
	For( i , 1 , n )
		if( Idg[i] != 0 )return 1;
	return f;
}

int main(){
	
	while( scanf( "%d%d" , &n , &m ) != EOF ){
		
		f = 0;
		
		if( !read_in() )f = 2;
		
		switch( tuopu() ){
			case 0:puts("OK");break;
			case 1:puts("CONFLICT");break;
			case 2:puts("UNCERTAIN");break;
		}
		
	}
	
	return 0;
}
