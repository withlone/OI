#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int n = 1e4 + 1;
static const int maxn = 1e4 + 10;
static const int maxm = maxn << 2;

int m;
int top;

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
int Dt[maxm];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = z;
}

void read_in(){
	scanf( m ) ;
	For( i , 1 , m ){
		int x , y;
		scanf( x ) ; scanf( y ) ; ++y ;
		Ins( x , y , 2 ) ;
		if( y > top )top = y;
	}
	For( i , 1 , top )Ins( i - 1 , i , 0 ) , Ins( i , i - 1 , -1 );
}

int dis[maxn];
bool V[maxn];

void spfa(){
	int que[maxn] , H = 0 , T = -1;
	que[ ++T ] = 0;
	memset( dis , -0x3f , sizeof dis );
	dis[0] = 0;
	while( H != ( T + 1 ) % n ){
		int x = que[ H++ ];V[x] = false;
		if( H == n )H = 0;
		Rep( i , Ht[x] , Nt[i] ){
			int y = To[i];
			if( dis[y] < dis[x] + Dt[i] ){
				dis[y] = dis[x] + Dt[i];
				if( !V[y] ){
					V[y] = true;
					if( T == n - 1 )que[T = 0] = y;
					else que[ ++T ] = y;
				}
			}
		}
	}
	printf("%d\n" , dis[top] );
}

int main(){
	
	read_in();
	
	spfa();
	
	return 0;
}
