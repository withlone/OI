#include<map>
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

static const int maxn = 2e4 + 10;
static const int maxm = 5e4 + 10;

int n , m;
int A[maxm] , B[maxm];

int Ht[maxn] , Nt[maxm] , To[maxm] , Ct;
void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
}

int cnt , dct;
int bel[maxn] , size[maxn];
bool V[maxn];int stack[maxn] , tp;
int dfn[maxn] , Low[maxn];
void tarjan( int x ){
	int y;
	V[x] = true;stack[ ++tp ] = x;
	dfn[x] = Low[x] = ++dct;
	Rep( i , Ht[x] , Nt[i] ){
		y = To[i];
		if( !dfn[y] )tarjan( y ) , Low[x] = min( Low[x] , Low[y] );
		else if( V[y] )Low[x] = min( Low[x] , dfn[y] );
	}
	if( dfn[x] != Low[x] )return;
	cnt++;
	do{
		V[ y = stack[ tp-- ] ] = false;
		bel[y] = cnt;
	}while( x != y );
}

int idg[maxn] , odg[maxn];
int Idg[maxn] , Odg[maxn];

int Fa[maxn];
int Find( int t ){ return t == Fa[t] ? t : Fa[t] = Find( Fa[t] ) ; }

int main(){
	
	while( scanf( "%d%d" , &n , &m ) != EOF ){
		
		Ct = tp = cnt = dct = 0;
		For( i , 1 , n )
			Idg[i] = Odg[i] = Ht[i] = dfn[i] = Low[i] = V[i] = 0 , Fa[i] = i;
		
		For( i , 1 , m ){
			int x , y;
			Read( x );Read( y );
			Ins( x , y );
			A[i] = x;B[i] = y;
		}
		
		For( i , 1 , n )if( !dfn[i] )
			tarjan( i );
		
		map< int , bool >mp[maxn];
		
		For( i , 1 , m )if( bel[ A[i] ] != bel[ B[i] ] && !mp[ bel[ B[i] ] ][ bel[ A[i] ] ] )
			Idg[ bel[ B[i] ] ]++ , Odg[ bel[ A[i] ] ]++ ,  mp[ bel[ B[i] ] ][ bel[ A[i] ] ] = true ,
			Fa[ Find( bel[ B[i] ] ) ] = Find( bel[ A[i] ] );
		
		int ans = 0;
		
		For( i , 1 , cnt )size[i] = idg[i] = odg[i] = 0;
		
		For( i , 1 , cnt ){
			idg[ Find( i ) ] += !Idg[i] ,
			odg[ Find( i ) ] += !Odg[i] ;
			if( Find( i ) == i )ans++;
			size[ Find( i ) ]++;
		}
		
		if( cnt == 1 && size[ Find( 1 ) ] == 1 ){ puts("0") ; continue ; }
		
		int t1 = 0 , t2 = 0;
		
		For( i , 1 , cnt )
			if( Find( i ) == i )
				t1 += idg[i] , t2 += odg[i];
		
		ans = max( t1 , t2 );
		
		printf("%d\n",ans);
		
	}
	
	return 0;
}
