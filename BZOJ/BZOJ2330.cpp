#include<cstdio>

#define For( i , _Begin , _End ) for( int i=(_Begin);i<=(_End);i++ )
#define Rep( i , _Begin , _Add ) for( int i=(_Begin);i; i = (_Add) )

template< typename Type >inline Type min ( Type x , Type y ){ return x < y ? x : y; }
template< typename Type >inline Type max ( Type x , Type y ){ return x > y ? x : y; }
template< typename Type >inline void Read( Type &In ){
	In=0;char ch=getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

typedef long long LL;
static const int MAXN = 1e5 +1;

int n , m , Cnt;
int A[MAXN] , B[MAXN] , C[MAXN];
int Rk[MAXN] , Sz[MAXN] , Idg[MAXN] , Num[MAXN];
int Dfn[MAXN] , Low[MAXN];
bool It[MAXN];int St[MAXN] , Tp;
int H[MAXN] , Nt[MAXN<<1] , To[MAXN<<1] , Dt[MAXN<<1] , Ct;

void Init();
void Dfs( int );
void Tarjan( int );
void Ck( int , int , int );
void Ins( int , int , int );

int main(){
	
	Init();
	
	For( i , 1 , n )
		if( !Dfn[i] )Tarjan( i );
	
	For( i , 1 , m )
		if( Rk[A[i]] == Rk[B[i]] && ( C[i] == 2 || C[i] == 4 ) )return puts("-1") , 0;
	
	Ct = 0;
	For( i , 1 , n )H[i] = Idg[i] = 0;
	For( i , 1 , m )
		if( Rk[A[i]] != Rk[B[i]] )Ck( Rk[A[i]] , Rk[B[i]] , C[i] );
	
	For( i , 1 , Cnt )
		if( !Idg[i] )Dfs( i );
	
	LL Ans = 0;
	For( i , 1 , Cnt )Ans += Sz[i] * Num[i];
	printf("%lld\n",Ans);
	
	return 0;
}

void Init(){
	Read( n );Read( m );
	For( i , 1 , m ){
		int x , y , z;
		Read( z );Read( x );Read( y );
		A[i] = x;B[i] = y;C[i] = z;
		Ck( x , y , z );
	}
	Ct = 0;
}
void Ins( int F , int T , int D ){
	Nt[++Ct] = H[F];
	H[F] = Ct;
	To[Ct] = T;
	Dt[Ct] = D;
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
		Rk[y] = Cnt;
		Num[Cnt]++;
	}while( y != x );
}
void Dfs( int x ){
	Sz[x] = max( Sz[x] , 1 );
	Rep( i , H[x] , Nt[i] ){
		int y = To[i];
		Dfs( y );
		Sz[x] = max( Sz[x] , Sz[y] + Dt[i] );
	}
}
void Ck( int x , int y , int z ){
	switch( z ){
		case 1:Ins( x , y , 0 );Ins( y , x , 0 );break;
		case 2:Ins( y , x , 1 );Idg[x]++;break;
		case 3:Ins( x , y , 0 );Idg[y]++;break;
		case 4:Ins( x , y , 1 );Idg[y]++;break;
		case 5:Ins( y , x , 0 );Idg[x]++;break;
	}
}
