#include<queue>
#include<cstdio>
#include<cstring>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 100 + 10;
static const int maxm = 6e3 + 10;

int n;
int m;
int A[maxm];
int B[maxm];

int mp[maxn][maxn];

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
}

void read_in(){
	Ct = 0;
	memset( Ht , 0 , sizeof( int ) * ( n + 1 ) );
	memset( mp , 0 , sizeof mp );
	For( i , 1 , m ){
		int x , y;
		scanf( x ) ; scanf( y ) ;
		mp[x][y] = mp[y][x] = mp[x][y] + 1;
		A[i] = x ; B[i] = y ;
		Ins( x , y ) ; Ins( y , x ) ;
	}
}

bool flag;
int sum[maxn];
int dis[maxn];
int pre[maxn][maxn];

int que[maxn];
void bfs( int S ){
	int H = 0 , T = -1;
	que[ ++T ] = S;
	memset( dis , -1 , sizeof( int ) * ( n + 1 ) );
	dis[S] = 0;
	while( H <= T ){
		int x = que[ H++ ];
		Rep( i , Ht[x] , Nt[i] ){
			int y = To[i];
			if( !mp[x][y] || dis[y] != -1 )continue;
			if( !flag )pre[S][y] = x;
			dis[y] = dis[x] + 1;
			que[ ++T ] = y;
		}
	}
}

void Run(){
	int ans = 0;
	For( i , 1 , n ){
		bfs( i );
		sum[i] = 0;
		For( j , 1 , n )
			if( -1 == dis[j] ){ ans = -1 ; break ; }
			else sum[i] += dis[j];
		if( ans == -1 )break;
		ans += sum[i];
	}
	
	if( ans == -1 ){
		For( i , 1 , m )puts("INF");
		return;
	}
	
	For( I , 1 , m ){
		int x = A[I] , y = B[I];
		if( mp[x][y] > 1 ){ printf("%d\n" , ans ) ; continue ; }
		
		int tot = 0;
		mp[x][y] = mp[y][x] = 0;
		flag = true;
		
		For( i , 1 , n ){
			if( pre[i][x] != y && pre[i][y] != x ){ tot += sum[i] ; continue ; }
			bfs( i );
			For( j , 1 , n )
				if( -1 == dis[j] ){ tot = -1 ; break ; }
				else tot += dis[j];
			if( tot == -1 )break;
		}
		
		flag = false;
		mp[x][y] = mp[y][x] = 1;
		
		if( tot == -1 )puts("INF");
		else printf("%d\n" , tot );
		
	}
}

int main(){
	
	while( scanf( "%d%d" , &n , &m ) != EOF ){
		
		read_in();
		
		Run();
		
	}
	
	return 0;
}
