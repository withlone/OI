#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 5e3 + 10;
static const int maxm = 2e4 + 10;

int n , m;
int A[maxm] , B[maxm];

int Ht[maxn] , Nt[maxm] , To[maxm] , Ct;
void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
}

int dct , cnt;
int stack[maxn] , tp;int bel[maxn];
int dfn[maxn] , Low[maxn];bool V[maxn];
void tarjan( int x , int f ){
	int y;
	stack[ ++tp ] = x;V[x] = true;
	dfn[x] = Low[x] = ++dct;
	Rep( i , Ht[x] , Nt[i] )if( ( f + 1 >> 1 ) != ( i + 1 >> 1 ) ){
		y = To[i];
		if( !dfn[y] )tarjan( y , i ) , Low[x] = min( Low[x] , Low[y] );
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

int Idg[maxn];

int main(){
	
	Read( n );Read( m );
	
	For( i , 1 , m )
		Read( A[i] ) , Read( B[i] ) ,
		Ins( A[i] , B[i] ) , Ins( B[i] , A[i] );
	
	tarjan( 1 , 0 );
	
	For( i , 1 , m )
		if( bel[ A[i] ] != bel[ B[i] ] )
			Idg[ bel[ A[i] ] ]++ , Idg[ bel[ B[i] ] ]++;
	
	int ans = 0;
	For( i , 1 , cnt )if( Idg[i] == 1 )ans++;
	
	printf("%d\n",ans + 1 >> 1);
	
	return 0;
}
