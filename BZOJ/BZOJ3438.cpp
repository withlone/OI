#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e3 + 10;
static const int maxx = maxn * 3;
static const int maxm = 5e6 + 10;
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;
int ans;

int val_a[maxn];
int val_b[maxn];
int c1[maxn];
int c2[maxn];
int size[maxn];
int set[maxn][maxn];

void read_in(){
	scanf( n ) ;
	For( i , 1 , n )scanf( val_a[i] ) ;
	For( i , 1 , n )scanf( val_b[i] ) ;
	scanf( m ) ;
	For( i , 1 , m ){
		scanf( size[i] ) , scanf( c1[i] ) , scanf( c2[i] ) ;
		For( j , 1 , size[i] )scanf( set[i][j] ) ;
	}
}

int Ct = 1;
int Ht[maxx];
int Nt[maxm];
int to[maxm];
int cap[maxm];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

void preparation(){
	For( i , 1 , n )ans += val_a[i] + val_b[i] ;
	For( i , 1 , m )ans += c1[i] + c2[i] ;
}

void build_edge(){
	S = 0 ; T = n + ( m << 1 ) + 1 ;
	For( i , 1 , n )
		Ins( S , i , val_a[i] ) ,
		Ins( i , T , val_b[i] ) ;
	For( i , 1 , m ){
		Ins( S , i + n , c1[i] ) ,
		Ins( i + n + m , T , c2[i] ) ;
		For( j , 1 , size[i] )
			Ins( i + n , set[i][j] , inf ) ,
			Ins( set[i][j] , i + n + m , inf ) ;
	}
}

int dep[maxx];
int cur[maxx];

bool bfs(){
	static int que[maxx];
	int head = 0 , tail = -1;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head <= tail ){
		int x = que[ head++ ] ;
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[to[i]] && cap[i] ){
				dep[to[i]] = dep[x] + 1;
				if( to[i] == T )return true;
				que[ ++tail ] = to[i];
			}
	}
	return false;
}

int dfs( int x , int maxflow ){
	if( x == T )return maxflow ;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[to[i]] == dep[x] + 1 && cap[i] ){
			int t = dfs( to[i] , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t;
		}
	return 0;
}

void Dinic(){
	int t;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = dfs( S , inf ) )ans -= t;
	}
	printf("%d\n" , ans );
}

int main(){
	
	read_in();
	
	preparation();
	
	build_edge();
	
	Dinic();
	
	return 0;
}
