#include<cstdio>
#include<cstdlib>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 20 + 10;
static const int maxm = 13 + 10;
static const int maxk = 50 + 10;
static const int maxd = 100 + 10;
static const int maxx = maxd * maxn;
static const int maxe = 1e6 + 10;
static const int Inf = 0x7fffffff;

int n;
int m;
int k;
int S;
int T;

int H[maxm];
int r[maxm];
int St[maxm][maxn];

void read_in(){
	scanf( n ) ; scanf( m ) ; scanf( k ) ;
	For( i , 1 , m ){
		scanf( H[i] ) ; scanf( r[i] ) ;
		For( j , 1 , r[i] ){
			scanf( St[i][j] ) ;
			if( !St[i][j] )St[i][j] = n + 1 ;
			else if( St[i][j] == -1 )St[i][j] = n + 2 ;
		}
	}
}

bool cct[maxn][maxn];

void Floyd_check(){
	S = 0 ; T = n + 3 ;
	cct[S][n + 1] = cct[n + 2][T] = true;
	For( i , 1 , m )
		For( j , 1 , r[i] )
			if( j == r[i] )cct[ St[i][j] ][ St[i][1] ] = true;
			else cct[ St[i][j] ][ St[i][j + 1] ] = true;
	For( k , S , T )
		For( i , S , T )
			For( j , S , T )
				cct[i][j] |= cct[i][k] & cct[k][j] ;
	if( !cct[S][T] ){
		puts("0");
		exit( 0 );
	}
}

int cnt;
int num[maxd][maxn];

int Ct = 1;
int Ht[maxx];
int Nt[maxe];
int to[maxe];
int cap[maxe];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

void preparation(){
	For( i , 0 , maxd - 1 )
		For( j , 1 , n + 2 )
			num[i][j] = ++cnt;
	S = 0 ; T = cnt + 1 ;
	For( i , 0 , maxd - 1 ){
		Ins( S , num[i][n + 1] , Inf ) ,
		Ins( num[i][n + 2] , T , Inf ) ;
		if( i == maxd - 1 )return;
		For( j , 1 , n + 2 )
			Ins( num[i][j] , num[i + 1][j] , Inf ) ;
	}
}

int cur[maxx];
int dep[maxx];

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
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0;
}

int Dinic(){
	int res = 0 , t;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = dfs( S , Inf ) )res += t ;
	}
	return res;
}

int Get( int x , int y ){ return x % y + 1 ; }

void Run(){
	int tot = 0;
	For( d , 1 , 100 ){
		For( i , 1 , m )
		Ins( num[d - 1][ St[i][Get( d - 1 , r[i] )] ] , num[d][ St[i][Get( d , r[i] )] ] , H[i] ) ;
		if( ( tot += Dinic() ) >= k )return printf("%d\n" , d ) , void();
	}
}

int main(){
	
	read_in();
	
	Floyd_check();
	
	preparation();
	
	Run();
	
	return 0;
}#include<cstdio>
#include<cstdlib>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 20 + 10;
static const int maxm = 13 + 10;
static const int maxk = 50 + 10;
static const int maxd = 100 + 10;
static const int maxx = maxd * maxn;
static const int maxe = 1e6 + 10;
static const int Inf = 0x7fffffff;

int n;
int m;
int k;
int S;
int T;

int H[maxm];
int r[maxm];
int St[maxm][maxn];

void read_in(){
	scanf( n ) ; scanf( m ) ; scanf( k ) ;
	For( i , 1 , m ){
		scanf( H[i] ) ; scanf( r[i] ) ;
		For( j , 1 , r[i] ){
			scanf( St[i][j] ) ;
			if( !St[i][j] )St[i][j] = n + 1 ;
			else if( St[i][j] == -1 )St[i][j] = n + 2 ;
		}
	}
}

bool cct[maxn][maxn];

void Floyd_check(){
	S = 0 ; T = n + 3 ;
	cct[S][n + 1] = cct[n + 2][T] = true;
	For( i , 1 , m )
		For( j , 1 , r[i] )
			if( j == r[i] )cct[ St[i][j] ][ St[i][1] ] = true;
			else cct[ St[i][j] ][ St[i][j + 1] ] = true;
	For( k , S , T )
		For( i , S , T )
			For( j , S , T )
				cct[i][j] |= cct[i][k] & cct[k][j] ;
	if( !cct[S][T] ){
		puts("0");
		exit( 0 );
	}
}

int cnt;
int num[maxd][maxn];

int Ct = 1;
int Ht[maxx];
int Nt[maxe];
int to[maxe];
int cap[maxe];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

void preparation(){
	For( i , 0 , maxd - 1 )
		For( j , 1 , n + 2 )
			num[i][j] = ++cnt;
	S = 0 ; T = cnt + 1 ;
	For( i , 0 , maxd - 1 ){
		Ins( S , num[i][n + 1] , Inf ) ,
		Ins( num[i][n + 2] , T , Inf ) ;
		if( i == maxd - 1 )return;
		For( j , 1 , n + 2 )
			Ins( num[i][j] , num[i + 1][j] , Inf ) ;
	}
}

int cur[maxx];
int dep[maxx];

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
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0;
}

int Dinic(){
	int res = 0 , t;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = dfs( S , Inf ) )res += t ;
	}
	return res;
}

int Get( int x , int y ){ return x % y + 1 ; }

void Run(){
	int tot = 0;
	For( d , 1 , 100 ){
		For( i , 1 , m )
		Ins( num[d - 1][ St[i][Get( d - 1 , r[i] )] ] , num[d][ St[i][Get( d , r[i] )] ] , H[i] ) ;
		if( ( tot += Dinic() ) >= k )return printf("%d\n" , d ) , void();
	}
}

int main(){
	
	read_in();
	
	Floyd_check();
	
	preparation();
	
	Run();
	
	return 0;
}
