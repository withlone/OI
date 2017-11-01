#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define Rep( i , _Begin , _Add ) for( int i=_Begin;i!=-1;i=_Add )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 100 +10;
static const int MAXM = 500 +10;

int n , m ;
int W[MAXN] , V[MAXN] , D;
int Nt[MAXN] , H[MAXN] , To[MAXN] , Ct;

int Rank[MAXN];
int Dfn[MAXN] , Low[MAXN] , St[MAXN] , Tp , Cnt;
bool It[MAXN];

int w[MAXN] , v[MAXN];
int NxN[MAXN] , HdH[MAXN] , ToT[MAXN];
int f[MAXN][MAXM];

bool Vis[MAXN];

void Init();
void Ins( int,int );
void Tarjan( int );
void Add( int,int );
void Dp( int );
void GV();

int main(){
	
	Init();
	
	GV();
	
	Dp( 0 );
	printf("%d\n",f[0][m]);
	return 0;
}

void Init(){
	memset( H , -1 , sizeof H );
	memset( HdH , -1 , sizeof HdH );
	Read( n );Read( m );
	For( i , 1 , n )Read( W[i] );
	For( i , 1 , n )Read( V[i] );
	For( i , 1 , n ){Read( D ) ;Ins( D , i );}
}
void Ins( int F , int T ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
}
void Tarjan( int x ){
	int y;
	Dfn[x] = Low[x] = ++Ct;
	It[x] = true;St[++Tp] = x;
	Rep( i , H[x] , Nt[i] ){
		y = To[i];
		if( !Dfn[y] )Tarjan( y ) , Low[x] = min( Low[x] , Low[y] );
		else if( It[y] )Low[x] = min( Low[x] , Dfn[y] );
	}
	if( Dfn[x] != Low[x] )return;
	Cnt++;
	do{
		y = St[Tp--];
		It[y] = false;
		Rank[y] = Cnt;
		w[Cnt] += W[y];
		v[Cnt] += V[y];
	}while( x != y );
}
void Add( int F , int T ){
	NxN[++Ct] = HdH[F];
	HdH[F] = Ct;
	ToT[Ct] = T;
}
void Dp( int x ){
	Rep( i , HdH[x] , NxN[i] ){	
		int y = ToT[i];
		For( j , 0 , m )f[y][j] = f[x][j] + v[y];
		Dp( y );
		For( j , w[y] , m )f[x][j] = max( f[x][j] , f[y][j-w[y]] );
	}
}
void GV(){
	Ct = 0;
	For( i , 1 , n )
		if( !Dfn[i] )Tarjan( i );
	Ct = 0;
	For( x , 1 , n )
		Rep( i , H[x] , Nt[i] ){
			int y = To[i];
			if( Rank[x] != Rank[y] )Add( Rank[x] , Rank[y] ) , Vis[Rank[y]] = 1;
		}
	For( i , 1 , Cnt )if( !Vis[i] )Add( 0 , i );
}
