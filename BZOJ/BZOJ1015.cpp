#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxm = 2e5 + 10;
static const int maxn = maxm << 1;

int n , m , q , tot;
int A[maxm] , B[maxm] , C[maxn];
bool V[maxn];int ans[maxn];

int Fa[maxn];
int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int H[maxn] , Nt[maxn] , To[maxn] , Ct;
void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

int main(){
	
	Read( n );Read( m );
	
	For( i , 1 , n )Fa[i] = i , V[i] = true;
	
	For( i , 1 , m ){
		Read( A[i] );Read( B[i] );
		++A[i];++B[i];
		Ins( A[i] , B[i] );Ins( B[i], A[i] );
	}
	
	Read( q );
	For( i , 1 , q )Read( C[i] ) , V[ ++C[i] ] = false;
	
	For( i , 1 , m )if( V[ A[i] ] && V[ B[i] ] )
		Fa[ Find( A[i] ) ] = Find( B[i] );
	
	For( i , 1 , n )if( V[i] && Find( i ) == i )++tot;
	
	Lop( i , q , 0 ){
		ans[i] = tot;
		V[ C[i] ] = true;++tot;
		Rep( j , H[ C[i] ] , Nt[j] )
			if( V[ To[j] ] && Find( C[i] ) != Find( To[j] ) )--tot , Fa[ Find( C[i] ) ] = Find( To[j] );
	}
	
	For( i , 0 , q )printf("%d\n",ans[i]);
	
	return 0;
}
