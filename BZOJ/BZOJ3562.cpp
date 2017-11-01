#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 5e3 + 10;
static const int maxm = 2e5 + 10;
static const int maxq = 1e4 + 10;

int Fa[maxn];
int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int n , m , q , ans;
bool tmp[maxn][maxn];
int mp[maxn][maxn];char opt[maxq];
int _A[maxm] , _B[maxm];
int A[maxm] , B[maxm] , C[maxq] , D[maxq];

bool V[maxn];int Stk[maxn] , tp;
bool Dfs( int x , int y ){
	if( x == y )return true;
	V[x] = true;Stk[ ++tp ] = x;
	For( z , 1 , n )
		if( mp[x][z] && !V[z] && z != x )
		if( Dfs( z , y ) )return true;
	return false;
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Fa[i] = i;
	For( i , 1 , m )Read( A[i] ) , Read( B[i] ) , mp[ A[i] ][ B[i] ] = mp[ B[i] ][ A[i] ] = 1
	 , _A[i] = A[i] , _B[i] = B[i];
	
	Read( q );
	For( i , 1 , q ){
		opt[i] = getchar();
		while( opt[i] > 'Z' || opt[i] < 'A' )opt[i] = getchar();
		if( opt[i] != 'Q' )Read( C[i] ) , Read( D[i] ) , mp[ C[i] ][ D[i] ] = mp[ D[i] ][ C[i] ] = 0;
	}
	
	For( i , 1 , m )tmp[ A[i] ][ B[i] ] = mp[ A[i] ][ B[i] ];
	
	For( i , 1 , m )
		if( tmp[ A[i] ][ B[i] ] )Fa[ Find( A[i] ) ] = Find( B[i] ) , mp[ A[i] ][ B[i] ] = mp[ B[i] ][ A[i] ] = 0;
	
	For( i , 1 , m )A[i] = Find( A[i] ) , B[i] = Find( B[i] );
	
	For( i , 1 , m )
		if( !tmp[ _A[i] ][ _B[i] ] && A[i] != B[i] )++mp[ A[i] ][ B[i] ] , ++mp[ B[i] ][ A[i] ];
	
	
	For( i , 1 , q )C[i] = Find( C[i] ) , D[i] = Find( D[i] );
	
	For( i , 1 , n )
		For( j , i , n )
			if( mp[i][j] )Fa[ Find( i ) ] = Find( j );
	
	For( i , 1 , n )if( Find( i ) == i )++ans;
	
	For( i , 1 , q )
		if( opt[i] == 'Q' )printf("%d\n",ans);
		else if( opt[i] == 'A' ){
			tp = 0;
			if( !Dfs( C[i] , D[i] ) )--ans;
			while( tp )V[ Stk[ tp-- ] ] = false;
			++mp[ C[i] ][ D[i] ] , ++mp[ D[i] ][ C[i] ];
		}
		else{
			int t = mp[ C[i] ][ D[i] ];
			--mp[ C[i] ][ D[i] ] , --mp[ D[i] ][ C[i] ];
			tp = 0;
			if( !Dfs( C[i] , D[i] ) )++ans;
			while( tp )V[ Stk[ tp-- ] ] = false;
		}
	
	return 0;
}
