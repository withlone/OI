#include<queue>
#include<cstdio>
#include<cstring>

using namespace std;

#define For( i , _begin , _end ) for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )
#define Rep( i , _begin , _add ) for( int i = (_begin) ; i ; i = (_add) )

template< typename type >inline void scanf( type &in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ; ch > '9' || ch < '0' ; ch = getchar() )if( ch == '-' )f = -1 ;
	for( ; ch >='0' && ch <='9' ; ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

static const int maxn = 50 + 10;
static const int maxm = 16 + 10;
static const int maxx = maxn * maxn;
static const int maxe = maxx << 2;

int n;
int m;

int A[maxx];
int mp[maxn][maxn];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )For( j , 1 , n )
		scanf( mp[i][j] ) ;
}

void work( int x , int y ){
	if( x < 1 || x > n || y < 1 || y > n )return;
	if( mp[x][y] != -2 )mp[x][y] = -1;
}

int cnt;
int num[maxn][maxn];

void preparation(){
	For( i , 1 , n )For( j , 1 , n )
		if( mp[i][j] == -2 )
			work( i - 1 , j ) , work( i + 1 , j ) , work( i , j - 1 ) , work( i , j + 1 ) ;
	For( i , 1 , n )For( j , 1 , n )
		if( mp[i][j] >= 0 )num[i][j] = ++cnt , A[cnt] = mp[i][j];
}

int Ct;
int Ht[maxx];
int Nt[maxe];
int to[maxe];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

void build_edge(){
	For( i , 1 , n )For( j , 1 , n )if( num[i][j] ){
		if( num[i - 1][j] )Ins( num[i][j] , num[i - 1][j] ) ;
		if( num[i + 1][j] )Ins( num[i][j] , num[i + 1][j] ) ;
		if( num[i][j - 1] )Ins( num[i][j] , num[i][j - 1] ) ;
		if( num[i][j + 1] )Ins( num[i][j] , num[i][j + 1] ) ;
	}
}

class node{
	
	public :
		int pos;
		int key;
		int dis;
		
		node(){ pos = key = 0 ; dis = ~0U >> 1; }
		node( int a , int b , int c){ pos = a ; key = b ; dis = c ; }
};

bool V[maxx][1 << 16];

void bfs(){
	static queue < node > que;
	que.push( node( 1 , ( A[1] && A[1] <= m ) ? ( 1 << m - A[1] ) : 0 , 0 ) );
	while( !que.empty() ){
		node p = que.front() ; que.pop() ;
		Rep( i , Ht[p.pos] , Nt[i] )if( to[i] != 1 ){
			node nxt = p ; nxt.dis = p.dis + 1;
			if( A[to[i]] > m && !( p.key & ( 1 << 2 * m - A[to[i]] ) ) )continue;
			if( V[to[i]][p.key] )continue;
			V[to[i]][p.key] = true;
			if( A[to[i]] && A[to[i]] <= m )nxt.key |= 1 << m - A[to[i]];
			nxt.pos = to[i];
			que.push( nxt );
			if( to[i] == num[n][n] )return printf("%d\n" , nxt.dis ) , void() ;
		}
	}
	puts("you cheat me!!!");
}

int main(){
	
	freopen("langle.in","r",stdin);
	freopen("langle.out","w",stdout);
	
	read_in();
	
	preparation();
	
	build_edge();
	
	bfs();
	
	return 0;
}
