#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e4 + 10;
static const int maxm = 1e5 + 10;

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

bool V[maxn];

int tp;
int stack[maxn];

int cnt;
int dct;
int dfn[maxn];
int Low[maxn];

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
	do
		V[ y = stack[ tp-- ] ] = false;
	while( x != y );
}

int main(){
	
	while( Read( n ) , Read( m ) , n + m ){
		
		cnt = Ct = dct = tp = 0;
		For( i , 1 , n )V[i] = dfn[i] = Low[i] = Ht[i] = 0;
		
		For( i , 1 , m ){
			int x , y;
			Read( x );Read( y );
			Ins( x , y );
		}
		
		For( i , 1 , n )if( !dfn[i] )
			tarjan( i );
		
		puts( cnt == 1 ? "Yes" : "No" );
		
	}
	
	return 0;
}
