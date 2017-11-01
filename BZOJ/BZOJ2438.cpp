#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e5 + 10;
static const int maxm = 6e5 + 10;

int n , m;

int H[maxn] , Nt[maxm] , To[maxm] , Ct;
void Ins( int x , int y ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
}

int size[maxn];
int cnt;int stack[maxn] , tp;
int dfn[maxn] , Low[maxn] , BL[maxn];bool V[maxn];
void tarjan( int x ){
	int y;
	stack[ ++tp ] = x;
	dfn[x] = Low[x] = ++cnt;V[x] = true;
	Rep( i , H[x] , Nt[i] ){
		y = To[i];
		if( !dfn[y] )tarjan( y ) , Low[x] = min( Low[x] , Low[y] );
		else if( V[y] )Low[x] = min( Low[x] , dfn[y] );
	}
	if( dfn[x] != Low[x] )return;
	++Ct;
	do{
		y = stack[ tp-- ];
		BL[y] = Ct;
		V[y] = false;
		++size[Ct];
	}while( x != y );
}

int A[maxm] , B[maxm] , Idg[maxn];

bool chk( int x ){
	Rep( i , H[x] , Nt[i] )
		if( Idg[ To[i] ] == 1 )return false;
	return true;
}

int main(){
	
	Read( n );Read( m );
	
	For( i , 1 , m ){
		int x , y;
		Read( x );Read( y );
		Ins( x , y );
		A[i] = x;B[i] = y;
	}
	
	Ct = 0;
	For( i , 1 , n )if( !dfn[i] )
		tarjan( i );
	
	For( i , 1 , n )H[i] = 0;
	
	cnt = Ct;Ct = 0;
	For( i , 1 , m )
		if( BL[ A[i] ] != BL[ B[i] ] )
			Idg[ BL[ B[i] ] ]++ , Ins( BL[ A[i] ] , BL[ B[i] ] );
	
	bool f = 0;int ans = 0;
	For( i , 1 , cnt ){
		if( !Idg[i] )++ans;
		if( !Idg[i] && size[i] == 1 && chk( i ) )f = 1;
	}
	ans -= f;
	
	printf("%.6lf\n",( n - ans ) * 1.0 / n);
	
	return 0;
}
