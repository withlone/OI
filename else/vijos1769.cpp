#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e5 + 10;
static const int maxm = maxn << 1;

int n , m , prA , prB;
bool Va[maxn] , Vb[maxn];

int Ht[maxn] , Nt[maxm] , To[maxm] , Dt[maxm] , Ct;
void Ins( int x , int y , int num ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = num;
}

int seq[maxn] , Cnt;

int dct , cnt;
bool V[maxn];int stack[maxn] , tp;
int dfn[maxn] , Low[maxn];
int SzA[maxn] , SzB[maxn];
void tarjan( int x , int f ){
	int y;
	V[x] = true;stack[ ++tp ] = x;
	dfn[x] = Low[x] = ++dct;
	SzA[x] = Va[x];SzB[x] = Vb[x];
	Rep( i , Ht[x] , Nt[i] )if( Dt[i] != Dt[f] ){
		y = To[i];
		if( !dfn[y] ){
			tarjan( y , i );
			Low[x] = min( Low[x] , Low[y] );
			SzA[x] += SzA[y];SzB[x] += SzB[y];
			if( Low[y] > dfn[x] )
				if( SzA[y] == prA || SzB[y] == prB || !SzA[y] || !SzB[y] )seq[ ++Cnt ] = Dt[i];
		}
		else if( V[y] )Low[x] = min( Low[x] , dfn[y] );
	}
	if( dfn[x] != Low[x] )return;
	cnt++;
	do
		V[ y = stack[ tp-- ] ] = false;
	while( x != y );
}

int main(){
	
	Read( n );Read( m );Read( prA );Read( prB );
	
	For( i , 1 , prA ){
		int x;
		Read( x );
		Va[x] = true;
	}
	
	For( i , 1 , prB ){
		int x;
		Read( x );
		Vb[x] = true;
	}
	
	For( i , 1 , m ){
		int x , y;
		Read( x );Read( y );
		Ins( x , y , i );Ins( y , x , i );
	}
	
	tarjan( 1 , 0 );
	
	sort( 1 + seq , 1 + Cnt + seq );
	
	printf("%d\n",Cnt);
	
	For( i , 1 , Cnt )printf("%d\n",seq[i]);
	
	puts("");
	
	return 0;
}
