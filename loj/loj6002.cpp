#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 4e2 + 10;
static const int maxm = (maxn << 2) + 12e3 + 10;
static const int Inf = 0x7fffffff;

int n;
int m;
int S;
int T;
int tot;

int Ct = 1;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
int Cm[maxm];
int cap[maxm];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	Cm[Ct] = x;
	To[Ct] = y;
	cap[Ct] = z;
}

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , m ){
		int x , y ;
		scanf( x ) ; scanf( y ) ;
		Ins( x , y + n , 1 ) ; Ins( y + n , x , 0 ) ;
	}
}

void build_edge(){
	S = 0 ; T = n << 1 | 1 ; tot = T + 1 ;
	For( i , 1 , n )
		Ins( S , i , 1 ) , Ins( i , S , 0 ) ,
		Ins( i + n , T , 1 ) , Ins( T , i + n , 0 ) ;
}

int cur[maxn];
int dep[maxn];

#define y To[i]

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = -1;
	que[ ++tail ] = S;
	memset( dep , 0 , sizeof( int ) * tot ) ;
	dep[S] = 1;
	while( head <= tail ){
		int x = que[ head++ ];
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[y] && cap[i] ){
				dep[y] = dep[x] + 1 ;
				if( y == T )return true;
				que[ ++tail ] = y;
			}
	}
	return false;
}

int Dfs( int x , int maxflow ){
	if( x == T )return maxflow;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[y] == dep[x] + 1 && cap[i] ){
			int t = Dfs( y , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t;
		}
	return 0;
}

#undef y

int Dinic(){
	int res = 0 , t;
	while( bfs() ){
		memcpy( cur , Ht , sizeof( int ) * tot ) ;
		while( t = Dfs( S , Inf ) )res += t ;
	}
	return res;
}

int Nxt[maxn];
bool V[maxn];

void display(){
	int ans = n - Dinic();
	For( i , 2 , m << 1 ){
		if( !cap[i] )Nxt[ Cm[i] ] = To[i] - n;
		++i;
	}
	For( i , 1 , n )if( !V[i] ){
		int t = i ;
		while( Nxt[t] )
			V[t] = true , printf("%d " , t ) , t = Nxt[t] ;
		printf("%d\n" , t );V[t] = true;
	}
	printf("%d\n" , ans );
}

int main(){
	
	read_in();
	
	build_edge();
	
	display();
	
	return 0;
}
