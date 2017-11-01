#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e4 + 10;
static const int maxm = maxn << 1;

int n , N;

int H[maxn] , Nt[maxm] , To[maxm] , Ct;

void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

int Sz[maxn];bool V[maxn];
void Dfs( int x , int f ){
	Sz[x] = 1;
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( y == f )continue;
		Dfs( y , x );
		Sz[x] += Sz[y];
		if( Sz[y] > N )V[x] = true;
	}
	if( n - Sz[x] > N )V[x] = true;
}

int main(){
	
	Read( n );
	
	For( i , 1 , n - 1 ){
		int x , y;
		Read( x );Read( y );
		Ins( x , y );Ins( y , x );
	}
	
	N = n >> 1;
	Dfs( 1 , 0 );
	
	bool f = 0;
	For( i , 1 , n )
		if( !V[i] )printf("%d\n",i) , f = 1;
	
	if( !f )puts("NONE");
	
	return 0;
}
