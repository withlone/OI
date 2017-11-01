#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 5e3 + 10;
static const int maxm = 3e4 + 10;

int T , n , m;
int A[maxm] , B[maxm];
int Sz[maxn] , Idg[maxn];

int Ht[maxn] , Nt[maxm] , To[maxm] , Ct;
void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
}

int dct , cnt;
bool V[maxn];
int bel[maxn];
int dfn[maxn] , Low[maxn];
int stack[maxn] , size[maxn] , tp;
void tarjan( int x ){
	int y;
	V[x] = true;
	stack[ ++tp ] = x;
	dfn[x] = Low[x] = ++dct;
	Rep( i , Ht[x] , Nt[i] ){
		y = To[i];
		if( !dfn[y] )tarjan( y ) , Low[x] = min( Low[x] , Low[y] );
		else if( V[y] )Low[x] = min( Low[x] , dfn[y] );
	}
	if( dfn[x] != Low[x] )return;
	++cnt;
	do{
		y = stack[ tp-- ];
		V[y] = false;
		bel[y] = cnt;
		size[cnt]++;
	}while( x != y );
}

void Dfs( int x ){
	Sz[x] = size[x];
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		Dfs( y );
		Sz[x] += Sz[y];
	}
}

bool mp[maxn][maxn];

void Dfs( int x , int &sum ){
	V[x] = true;
	sum += size[x];
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( V[y] )continue;
		Dfs( y , sum );
	}
}

int seq[maxn] , Cnt;

int main(){
	
	Read( T );
	
	For( I , 1 , T ){
		
		Read( n );Read( m );
		
		cnt = dct = tp = 0;
		For( i , 1 , n )size[i] = V[i] = dfn[i] = Low[i] = Sz[i] = Ht[i] = Idg[i] = 0;
		
		For( i , 1 , m )
			Read( A[i] ) , Read( B[i] ) ,
			Ins( ++A[i] , ++B[i] );
		
		For( i , 1 , n )if( !dfn[i] )
			tarjan( i );
		
		Ct = 0;
		For( i , 1 , n )Ht[i] = 0;
		For( i , 1 , m )
			if( bel[ A[i] ] != bel[ B[i] ] && !mp[ bel[ B[i] ] ][ bel[ A[i] ] ] )
				Ins( bel[ B[i] ] , bel[ A[i] ] ) , Idg[ bel[ A[i] ] ]++ ,
				mp[ bel[ B[i] ] ][ bel[ A[i] ] ] = true;
		
		For( i , 1 , m )
			mp[ bel[ B[i] ] ][ bel[ A[i] ] ] = false;
		
		For( i , 1 , cnt )if( !Idg[i] )
			memset( V , 0 , sizeof V ) , Dfs( i , Sz[i] );
		
		int ans = 0;
		For( i , 1 , cnt )if( !Idg[i] && Sz[i] > ans )ans = Sz[i];
		
		printf("Case %d: %d\n", I , ans - 1); 
		
		For( i , 1 , n )V[i] = 0;
		For( i , 1 , cnt )if( !Idg[i] && ans == Sz[i] )V[i] = true;
		
		Cnt = 0;
		For( i , 1 , n )if( V[ bel[i] ] )seq[ ++Cnt ] = i - 1;
		
		For( i , 1 , Cnt )
			printf("%d%c",seq[i] , i == Cnt ? '\n' : ' ');
		
	}
	return 0;
}
