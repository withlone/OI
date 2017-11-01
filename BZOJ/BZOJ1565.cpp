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

static const int maxn = 40 + 10;
static const int maxx = maxn * maxn;
static const int maxm = 1e6 + 10;
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;
int ans ;

int val[maxx];
int size[maxx];
int set[maxx][maxx][2];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n * m ){
		scanf( val[i] ) ; scanf( size[i] ) ;
		For( j , 1 , size[i] )
			scanf( set[i][j][0] ) , scanf( set[i][j][1] ) ,
			set[i][j][0]++ , set[i][j][1]++ ;
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

int Get( int x , int y ){ return (x - 1) * m + y ; }

void build_edge(){
	S = 0 ; T = n * m + 1 ;
	For( i , 1 , n * m )
		if( val[i] > 0 )
			Ins( S , i , val[i] ) ;
		else
			Ins( i , T , -val[i] ) ;
	For( i , 1 , n )For( j , (i - 1) * m + 1 , i * m )
		For( k , j + 1 , i * m )Ins( j , k , inf ) ;
	For( i , 1 , n * m )For( j , 1 , size[i] )
		Ins( Get( set[i][j][0] , set[i][j][1] ) , i , inf ) ;
}

int dct;

bool V[maxx];

int dfn[maxx];
int Low[maxx];

int cnt;
int Sz[maxx];
int bel[maxx];

int tp;
int stack[maxx];

void tarjan( int x ){
	int y;
	V[x] = true ; stack[ ++tp ] = x;
	dfn[x] = Low[x] = ++dct ;
	Rep( i , Ht[x] , Nt[i] )if( cap[i] ){
		y = to[i] ;
		if( !dfn[y] )tarjan( y ) , Low[x] = min( Low[x] , Low[y] ) ;
		else if( V[y] )Low[x] = min( Low[x] , dfn[y] ) ;
	}
	if( dfn[x] != Low[x] )return;
	++cnt;
	do{
		y = stack[ tp-- ];
		V[y] = false;
		Sz[cnt]++;
		bel[y] = cnt;
	}while( x != y );
}

bool Vis[maxx];
bool visit[maxx];

void dfs( int x ){
	visit[x] = true;
	Rep( i , Ht[x] , Nt[i] )
		if( cap[i] ){
			Vis[x] |= Vis[to[i]];
			if( !visit[to[i]] )dfs( to[i] );
		}
}

void preparation(){
	For( i , 1 , n * m )if( !dfn[i] )
		tarjan( i ) ;
	For( i , 1 , n * m )
		if( Sz[ bel[i] ] > 1 )Vis[i] = true;
	For( i , 1 , n * m )if( !visit[i] )
		dfs( i );
	For( i , 1 , n * m )if( !Vis[i] && val[i] > 0 )
		ans += val[i];
}

int dep[maxx];
int cur[maxx];

bool bfs(){
	static int que[maxx];
	int head = 0 , tail = -1 ;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head <= tail ){
		int x = que[ head++ ] ;
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[to[i]] && cap[i] && !Vis[ to[i] ] ){
				dep[to[i]] = dep[x] + 1 ;
				if( to[i] == T )return true;
				que[ ++tail ] = to[i];
			}
	}
	return false;
}

int dfs( int x , int maxflow ){
	if( x == T )return maxflow ;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[to[i]] == dep[x] + 1 && cap[i] && !Vis[ to[i] ] ){
			int t = dfs( to[i] , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0;
}

void dinic(){
	int t;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = dfs( S , inf ) )ans -= t ;
	}
	printf("%d\n" , ans ) ;
}

int main(){
	
	read_in();
	
	build_edge();
	
	preparation();
	
	dinic();
	
	return 0;
}
