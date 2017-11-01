#include<cstdio>
#include<queue>
#include<cstring>

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )
#define Rep( i , _Begin , _Add ) for( int i=_Begin;i;i=_Add )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 2e5 +1;
static const int MAXM = 1e6 +1;

int n , m , A , B , C;
int Nt1[MAXM] , To1[MAXM] , H1[MAXM] , Dt1[MAXM] , Ct;

void Ins1( int F , int T , int D ){
	Nt1[++Ct] = H1[F];
	H1[F] = Ct;
	To1[Ct] = T;
	Dt1[Ct] = D;
}

int Rank[MAXN];
int Dfn[MAXN] , Low[MAXN] , St[MAXN] , Tp , Cnt;
bool It[MAXN];
void Tarjan( int x ){
	int y;
	Dfn[x] = Low[x] = ++Ct;
	It[x] = true;St[++Tp] = x;
	Rep( i , H1[x] , Nt1[i] ){
		y = To1[i];
		if( !Dfn[y] )Tarjan( y ) , Low[x] = min( Low[x] , Low[y] );
		else if( It[y] )Low[x] = min( Low[x] , Dfn[y] );
	}
	if( Dfn[x] != Low[x] )return;
	Cnt++;
	do{
		y = St[Tp--];
		It[y] = false;
		Rank[y] = Cnt;
	}while( x != y );
}

int Nt[MAXM] , To[MAXM] , H[MAXM] , Dt[MAXM];

void Ins( int F , int T , int D ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
	Dt[Ct] = D;
}

std::queue< int >Que;
int Dis[MAXN];bool Vis[MAXN];
int Spfa(){
	memset( Dis , 0x3f , sizeof Dis );
	Que.push( Rank[1] );
	Dis[Rank[1]] = 0;
	while( !Que.empty() ){
		int x = Que.front();Que.pop();Vis[x] = false;
		Rep( i , H[x] , Nt[i] ){
			int y = To[i];
			if( Dis[y] > Dis[x] + Dt[i] ){
				Dis[y] = Dis[x] + Dt[i];
				if( !Vis[y] ){
					Vis[y] = 1;
					Que.push( y );
				}
			}
		}
	}
	return Dis[Rank[n]];
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , m )Read( A ) , Read( B ) , Read( C ) , Ins1( A , B , C );
	
	Ct = 0;
	For( i , 1 , n )
		if( !Dfn[i] )Tarjan( i );
	
	Ct = 0;
	For( x , 1 , n )
		Rep( j , H1[x] , Nt1[j] ){
			int y = To1[j];
			if( Rank[x] != Rank[y] )Ins( Rank[x] , Rank[y] , Dt1[j] );
		}
	
	printf("%d\n",Spfa());
	
	return 0;
}
