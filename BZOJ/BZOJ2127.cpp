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

static const int maxn = 100 + 10;
static const int maxx = maxn * maxn * 5;
static const int maxm = 28 * maxx;
static const int inf = ~0U >> 1;

int n;
int m;
int u;
int v;
int S;
int T;
int ans;

int Ct = 1;
int Ht[maxx];
int Nt[maxm];
int to[maxm];
int cap[maxm];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

int cnt;
int num[maxn][maxn];

void preparation(){
	For( i , 1 , n )For( j , 1 , m )
		num[i][j] = ++cnt;
}

void read_in(){
	scanf( n ) ; scanf( m ) ;
	
	preparation();
	
	S = 0 ; T = 5 * cnt + 1 ;
	
	For( i , 1 , n )For( j , 1 , m )
		scanf( u ) , Ins( S , num[i][j] , u ) , ans += u;
	
	For( i , 1 , n )For( j , 1 , m )
		scanf( u ) , Ins( num[i][j] , T , u ) , ans += u;
	
	For( i , 1 , n - 1 )For( j , 1 , m )
		scanf( u ) , v = num[i][j] + cnt , ans += u ,
		Ins( S , v , u ) ,
		Ins( v , num[i][j] , inf ) ,
		Ins( v , num[i + 1][j] , inf );
	
	For( i , 1 , n - 1 )For( j , 1 , m )
		scanf( u ) , v = num[i][j] + cnt * 2 , ans += u ,
		Ins( v , T , u ) ,
		Ins( num[i][j] , v , inf ) ,
		Ins( num[i + 1][j] , v , inf ) ;
	
	For( i , 1 , n )For( j , 1 , m - 1 )
		scanf( u ) , v = num[i][j] + cnt * 3 , ans += u ,
		Ins( S , v , u ) ,
		Ins( v , num[i][j] , inf ) ,
		Ins( v , num[i][j + 1] , inf ) ;
	
	For( i , 1 , n )For( j , 1 , m - 1 )
		scanf( u ) , v = num[i][j] + cnt * 4 , ans += u ,
		Ins( v , T , u ) ,
		Ins( num[i][j] , v , inf ) ,
		Ins( num[i][j + 1] , v , inf ) ;
}

int cur[maxx];
int dep[maxx];

bool bfs(){
	static int que[maxx];
	int head = 0 , tail = 0 ;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head != tail ){
		int x = que[ ++head ] ;
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[to[i]] && cap[i] ){
				dep[to[i]] = dep[x] + 1 ;
				if( to[i] == T )return true;
				que[ ++tail ] = to[i] ;
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
	return 0 ;
}

int dinic(){
	int res = 0 , t ;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur ) ;
		while( t = dfs( S , inf ) )res += t ;
	}
	return res ;
}

int main(){
	
	read_in();
	
	printf("%d\n" , ans - dinic() );
	
	return 0;
}
