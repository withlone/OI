#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 500 + 10;
static const int maxm = 2e3 + 10;
static const int maxe = ( maxn << 1 ) + maxm << 1;
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;
LL ans;
LL tot;

int val[maxn];
int A[maxm];
int B[maxm];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )scanf( val[i] ) , tot += val[i] >= 0 ? val[i] : 0 ;
	for( int i = 1 ; i <= m ; i++ ){
		scanf( A[i] ) , scanf( B[i] ) ;
		if( val[ A[i] ] >= 0 && val[ B[i] ] >= 0 )
			ans += val[ A[i] ] ^ val[ B[i] ] , --i , --m ;
	}
}

int Ct = 1;
int Ht[maxn];
int Nt[maxe];
int to[maxe];
int cap[maxe];

void Ins( int x , int y , int p , int q = 0 ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = p ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = q ;
}

int dep[maxn];
int cur[maxn];

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = -1;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head <= tail ){
		int x = que[ head++ ] ;
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[to[i]] && cap[i] ){
				dep[to[i]] = dep[x] + 1 ;
				if( to[i] == T )return true;
				que[ ++tail ] = to[i];
			}
	}
	return false;
}

int dfs( int x , int maxflow ){
	if( x == T )return maxflow;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[to[i]] == dep[x] + 1 && cap[i] ){
			int t = dfs( to[i] , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0;
}

int dinic(){
	int res = 0 , t ;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur ) ;
		while( t = dfs( S , inf ) )res += t ;
	}
	return res;
}

bool V[maxn];

void dfs( int x ){
	V[x] = true;
	Rep( i , Ht[x] , Nt[i] )
		if( cap[i] && !V[to[i]] )dfs( to[i] ) ;
}

void Run(){
	S = 0 ; T = n + 1 ;
	For( I , 0 , 30 ){
		int t = 1 << I ;
		Ct = 1 ;memset( Ht , 0 , sizeof Ht ) ;
		For( i , 1 , n )if( val[i] >= 0 ){
			if( t & val[i] )
				Ins( S , i , inf ) ;
			else
				Ins( i , T , inf ) ;
		}
		For( i , 1 , m )
			Ins( A[i] , B[i] , 1 , 1 ) ;
		ans += 1LL * t * dinic();
		memset( V , 0 , sizeof V );
		dfs( S ) ;
		For( i , 1 , n )if( val[i] < 0 && V[i] )
			tot += t ;
	}
	printf("%lld\n%lld\n" , ans , tot );
}

int main(){
	
	read_in();
	
	Run();
	
	return 0;
}
