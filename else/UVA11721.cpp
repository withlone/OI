#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

#define mem( x ) memset( x , 0 , sizeof x )
static const int maxn = 1e3 + 10;
static const int maxm = 2e3 + 10;

int cases;
int n;
int m;

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
int Dt[maxm];
int Idg[maxn];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = z;
	Idg[y]++;
}

bool V[maxn];
int dis[maxn];
int Ind[maxn];

bool Vis[maxn];

void Dfs( int x ){
	Vis[x] = true;
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( !Vis[y] )Dfs( y );
	}
}

void spfa(){
	int que[ maxn * maxn ] , H = 0 , T = -1;
	mem( V );mem( Ind );mem( Vis );mem( dis );
	For( i , 1 , n )que[ ++T ] = i;
	while( H <= T ){
		int x = que[ H++ ];V[x] = false;
		if( Vis[x] )continue;
		Rep( i , Ht[x] , Nt[i] ){
			int y = To[i];
			if( dis[y] > dis[x] + Dt[i] ){
				dis[y] = dis[x] + Dt[i];
				if( !V[y] ){
					V[y] = true;
					if( ++Ind[y] > n )Dfs( y );
					else que[ ++T ] = y , Ind[y]++;
				}
			}
		}
	}
}

int main(){
	
	Read( cases );
	
	For( I , 1 , cases ){
	
		printf("Case %d:" , I );
		
		Ct = 0;
		mem( Ht );mem( Idg );
		
		Read( n );Read( m );
		
		For( i , 1 , m ){
			int x , y , z;
			Read( x );Read( y );Read( z );++x;++y;
			Ins( y , x , z );
		}
		
		spfa();
		
		bool f = 0;
		For( i , 1 , n )if( Vis[i] )
			printf(" %d", i - 1 ) , f = 1;
		
		if( !f )puts(" impossible");
		else puts("");
		
	}
	
	return 0;
}
