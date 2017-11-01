#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

#define mem( x ) memset( x , 0 , sizeof x )
static const int maxn = 50;
static const int maxx = maxn * maxn;
static const int maxm = maxx << 1;

int n;
int m;
int Case;

int num[maxn][maxn];
char mp[maxn][maxn];

int Sz[maxx];

int Ct;
int Ht[maxx];
int Nt[maxm];
int To[maxm];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
}

int A[maxm];
int B[maxm];

bool V[maxx];

int dct;
int dfn[maxx];
int Low[maxx];

int tp;
int stack[maxx];

int cnt;
int bel[maxx];
int val[maxx];

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
		val[cnt] += Sz[y];
	}while( x != y );
}

int Idg[maxx];

void tuopu(){
	int dis[maxx] , ans = 0;
	queue< int >que;
	mem( dis );
	For( i , 1 , cnt )if( !Idg[i] )
		que.push( i ) , dis[i] = val[i];
	while( !que.empty() ){
		int x = que.front();que.pop();
		Rep( i , Ht[x] , Nt[i] ){
			int y = To[i];
			if( !--Idg[y] )que.push( y );
			dis[y] = max( dis[y] , dis[x] + val[y]);
		}
	}
	printf("%d\n",dis[ bel[1] ]);
}

int main(){
	
	Read( Case );
	
	while( Case-- ){
		
		cnt = tp = 0;
		mem( Sz );mem( num );mem( Ht );mem( Idg );
		mem( V );mem( dfn );mem( Low );mem( val );
		
		Read( n );Read( m );
		
		For( i , 1 , n )scanf( "%s" , mp[i] + 1 );
		
		int nct = 0;
		For( i , 1 , n )For( j , 1 , m )num[i][j] = ++nct;
		
		Ct = 0;
		For( i , 1 , n )For( j , 1 , m )
			if( mp[i][j] != '#' ){
				if( mp[i][j] != '*' )Sz[ num[i][j] ] = mp[i][j] - '0';
				if( mp[i + 1][j] != '#' && num[i + 1][j] )
					Ins( num[i][j] , num[i + 1][j] ) , A[Ct] = num[i][j] , B[Ct] = num[i + 1][j];
				if( mp[i][j + 1] != '#' && num[i][j + 1] )
					Ins( num[i][j] , num[i][j + 1] ) , A[Ct] = num[i][j] , B[Ct] = num[i][j + 1];
				if( mp[i][j] == '*' ){
					int x , y;
					Read( x );Read( y );++x;++y;
					if( mp[x][y] != '#' && num[x][y] )
						Ins( num[i][j] , num[x][y] ) , A[Ct] = num[i][j] , B[Ct] = num[x][y];
				}
			}
		
		For( i , 1 , n * m )if( !dfn[i] )
			tarjan( i );
		
		mem( Ht );
		
		int temp = Ct;Ct = 0;
		For( i , 1 , temp )
			if( bel[ A[i] ] != bel[ B[i] ] )
				Ins( bel[ B[i] ] , bel[ A[i] ] ) ,
				Idg[ bel[ A[i] ] ]++;
		
		tuopu();
	}
	
	return 0;
}
