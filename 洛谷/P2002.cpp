#include<cstdio>
#include<algorithm>

#define For( i , _Begin , _End ) for( int i=_Begin;i<=_End;i++ )

template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

static const int MAXN = 1e5 +1;
static const int MAXM = 5e5 +1;

int n , m , Ans , A , B;
int Idg[MAXN];
int Nt[MAXM] , H[MAXM] , To[MAXM] , Ct;

void Ins( int F , int T ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
}

int Rank[MAXN];
int Dfn[MAXN] , Low[MAXN] , St[MAXN] , Tp , Cnt;
bool It[MAXN];
void Tarjan( int x ){
	int y;
	Dfn[x] = Low[x] = ++Ct;
	St[++Tp] = x;It[x] = true;
	for( int i = H[x] ; i ; i = Nt[i] ){
		y = To[i];
		if( !Dfn[y] ) Tarjan( y ) , Low[x] = std::min( Low[x] , Low[y] );
		else if( It[y] ) Low[x] = std::min( Low[x] , Dfn[y] );
	}
	if( Dfn[x] != Low[x] )return;
	Cnt++;
	do{
		y = St[Tp--];
		It[y] = false;
		Rank[y] = Cnt;
	}while( y != x );
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , m )Read( A ) , Read( B ) , Ins( A , B );
	
	Ct = 0;
	For( i , 1 , n )
		if( !Dfn[i] )Tarjan( i );
	
	For( i , 1 , n )
		for( int j = H[i] ; j ; j = Nt[j] )
			if( Rank[i] != Rank[To[j]] )
				Idg[Rank[To[j]]]++;
	
	For( i , 1 , Cnt )Ans += !Idg[i];
	printf("%d\n",Ans);
	return 0;
}
