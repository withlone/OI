#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e3 +1;
static const int maxm = maxn << 1;

int n , B;
int H[maxn] , Nt[maxm] , To[maxm];
int Stk[maxn] , tp , Ct;
int BL[maxn] , Cap[maxn];

void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

int Dfs( int x , int f ){
	int size = 0;
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		if( y == f )continue;
		size += Dfs( y , x );
		if( size >= B ){
			Cap[ ++Ct ] = x;
			while( size-- )BL[ Stk[ tp-- ] ] = Ct;
			size = 0;
		}
	}
	Stk[ ++tp ] = x;
	return size + 1;
}

int main(){
	
	Read( n );Read( B );
	For( i , 1 , n - 1 ){
		int x , y;
		Read( x );Read( y );
		Ins( x , y );Ins( y , x );
	}
	
	Ct = 0;
	Dfs( 1 , 0 );
	while( tp )BL[ Stk[ tp-- ] ] = Ct;
	
	printf("%d\n",Ct);
	For( i , 1 , n )printf("%d ",BL[i]);puts("");
	For( i , 1 , Ct )printf("%d ",Cap[i]);puts("");
	
	return 0;
}
