#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e3 + 10;
static const int maxm = 6e3 + 10;

int cases;
int n;
int m;

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];

int A[maxm];
int B[maxm];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
}

void read_in(){
	scanf( n ) ; scanf( m ) ;
	Ct = 0;
	For( i , 1 , n )Ht[i] = 0;
	For( i , 1 , m ){
		int x , y ;
		scanf( x ) ; scanf( y );
		Ins( x , y );
		A[i] = x;B[i] = y;
	}
}

int dct;
int dfn[maxn];
int Low[maxn];
bool V[maxn];
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
		y = To[i];
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

int Idg[maxn];

void rebuild(){
	Ct = 0;
	For( i , 1 , n )Idg[i] = Ht[i] = 0;
	For( i , 1 , m )if( bel[ A[i] ] != bel[ B[i] ] )
		Ins( bel[ A[i] ] , bel[ B[i] ] ) , Idg[ bel[ B[i] ] ]++;
}

bool tuopu(){
	int que[maxn] , H = 0 , T = -1;
	For( i , 1 , n )if( !Idg[i] )que[ ++T ] = i;
	while( H <= T ){
		if( T - H > 0 )return false;
		int x = que[ H++ ];
		Rep( i , Ht[x] , Nt[i] )
			if( !--Idg[ To[i] ] )que[ ++T ] = To[i];
	}
	return H == cnt;
}

int main(){
	
	scanf( cases );
	
	while( cases-- ){
		
		read_in();
		
		dct = cnt = tp = 0;
		For( i , 1 , n )V[i] = bel[i] = dfn[i] = Low[i] = 0;
		For( i , 1 , n )if( !dfn[i] )
			tarjan( i );
		
		rebuild();
		
		puts( tuopu() || cnt == 1 ? "Yes" : "No" );
		
	}
	
	return 0;
}
