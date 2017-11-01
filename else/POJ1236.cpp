#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type max( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 100 + 10;
static const int maxm = maxn * maxn;

int n;
int m;
int A[maxm];
int B[maxm];

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct; 
	To[Ct] = y;
}

bool V[maxn];

int tp;
int stack[maxn];

int dct;
int dfn[maxn];
int Low[maxn];

int cnt;
int bel[maxn];

void tarjan( int x ){
	int y;
	V[x] = true;
	stack[ ++tp ] = x;
	dfn[x] = Low[x] = ++dct;
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( !dfn[y] )tarjan( y ) , Low[x] = min( Low[x] , Low[y] );
		else if( V[y] )Low[x] = min( Low[x] , dfn[y] );
	}
	if( dfn[x] != Low[x] )return;
	++cnt;
	do{
		y = stack[ tp-- ];
		V[y] = false;
		bel[y] = cnt;
	}while( x != y );
}

int Idg[maxn];
int Odg[maxn];

int Fa[maxn];
int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int idg[maxn];
int odg[maxn];
int size[maxn];

bool mp[maxn][maxn];

int main(){
	
	Read( n );
	
	For( i , 1 , n ){
		int x;
		while( Read( x ) , x )
			++m , Ins( A[m] = i , B[m] = x );
	}
	
	For( i , 1 , n )if( !dfn[i] )
		tarjan( i );
	
	For( i , 1 , cnt )Fa[i] = i;
	
	For( i , 1 , m )
		if( bel[ A[i] ] != bel[ B[i] ] && !mp[ bel[ A[i] ] ][ bel[ B[i] ] ] )
			mp[ bel[ A[i] ] ][ bel[ B[i] ] ] = true ,
			Idg[ bel[ B[i] ] ]++ , Odg[ bel[ A[i] ] ]++ ,
			Fa[ Find( bel[ B[i] ] ) ] = Find( bel[ A[i] ] );
	
	int ans = 0;
	For( i , 1 , cnt )
		ans += !Idg[i];
	
	printf("%d\n",ans);
	
	For( i , 1 , cnt ){
		idg[ Find( i ) ] += !Idg[i] ,
		odg[ Find( i ) ] += !Odg[i] ;
		size[ Find( i ) ]++;
	}
	int t1 = 0 , t2 = 0;
	
	For( i , 1 , cnt )
		if( Find( i ) == i )
			t1 += idg[i] , t2 += odg[i];
	
	if( cnt == 1 && size[ Find( 1 ) ] == 1 )t1 = t2 = 0;
	printf("%d\n",max( t1 , t2 ) );
	
	return 0;
}
