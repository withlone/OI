#include<cstdio>
#include<algorithm>

using std :: min;

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )
#define Rep( i , _Begin , _Add ) for( int i=(_Begin);i; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e4 +1;
static const int MAXM = 5e4 +1;

int n , m , u , v , Cnt , Ans;
int A[MAXM] , B[MAXM];
int Odg[MAXN];bool Vis[MAXN];
bool It[MAXN];int Stk[MAXN] , Tp;
int H[MAXM] , Nt[MAXM] , To[MAXM] , Ct;
int Dfn[MAXN] , Low[MAXN] , Rk[MAXN] , Sz[MAXN];

void Init();
void Tarjan( int );
void Ins( int , int );

int main(){
	
	Init();
	
	For( i , 1 , n )
		if( !Dfn[i] )Tarjan( i );
	Ct = 0;
	
	For( i , 1 , m )
		if( Rk[A[i]] != Rk[B[i]] )Odg[Rk[A[i]]]++;
	
	For( i , 1 , Cnt )
		if( !Odg[i] )Ct++ , Ans = Sz[i];
	
	if( Ct > 1 )puts("0");
	else printf("%d\n",Ans);
	
	return 0;
}

void Init(){
	Read( n );Read( m );
	For( i , 1 , m )Read( A[i] ) , Read( B[i] ) , Ins( A[i] , B[i] );
	Ct = 0;
}
void Ins( int F , int T ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
}
void Tarjan( int x ){
	int y;
	Dfn[x] = Low[x] = ++Ct;
	Stk[++Tp] = x;It[x] = true;
	Rep( i , H[x] , Nt[i] ){
		y = To[i];
		if( !Dfn[y] )Tarjan( y ) , Low[x] = min( Low[x] , Low[y] );	
		else if( It[y] )Low[x] = min( Low[x] , Dfn[y] );
	}
	if( Low[x] != Dfn[x] )return;
	Cnt++;
	do{
		y = Stk[Tp--];
		It[y] = false;
		Rk[y] = Cnt;
		Sz[Cnt]++;
	}while( y != x );
}
