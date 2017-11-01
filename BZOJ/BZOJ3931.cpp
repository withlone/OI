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

typedef long long LL;
static const int maxn = 500 + 10;
static const int maxm = 1e5 + 10;
static const int mod = ( 1 << 9 ) - 1;
static const int maxe = maxm << 1;

int n;
int m;

namespace Dinic{
	
	static const int maxx = maxn << 1;
	static const int inf = ~0U >> 1 ;
	
	int S;
	int T;
	
	int Ct = 1;
	int Ht[maxx];
	int Nt[maxe];
	int to[maxe];
	int cap[maxe];
	
	void Ins( int x , int y , int z ){
		Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
		Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
	}
	
	int dep[maxx];
	int cur[maxx];
	
	bool bfs(){
		static int que[maxx];
		int head = 0 , tail = -1;
		memset( dep , 0 , sizeof dep );
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
		if( x == T )return maxflow ;
		for( int& i = cur[x] ; i ; i = Nt[i] )
			if( dep[to[i]] == dep[x] + 1 && cap[i] ){
				int t = dfs( to[i] , min( maxflow , cap[i] ) );
				if( t )
					return cap[i] -= t , cap[i ^ 1] += t , t;
			}
		return 0;
	}
	
	void Run(){
		LL res = 0 , t;
		while( bfs() ){
			memcpy( cur , Ht , sizeof cur );
			while( t = dfs( S , inf ) )res += t;
		}
		printf("%lld\n" , res );
	}
	
}

int Ct = 1;
int Ht[maxn];
int Nt[maxe];
int to[maxe];
int Dt[maxe];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; Dt[Ct] = z ;
}

int val[maxn];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , m ){
		int x , y , z ;
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		Ins( x , y , z ) ;
	}
	For( i , 1 , n )scanf( val[i] ) ;
}

LL dis[maxn];
bool V[maxn];

void spfa(){
	static int que[mod + 50];
	int head = 0 , tail = -1;
	memset( dis , 0x3f , sizeof dis ) ;
	que[ ++tail ] = 1 ; dis[1] = 0 ;
	while( head != ( tail + 1 ) & mod ){
		int x = que[ head++ ] ; head &= mod ; V[x] = false;
		Rep( i , Ht[x] , Nt[i] )
			if( dis[to[i]] > dis[x] + Dt[i] ){
				dis[to[i]] = dis[x] + Dt[i] ;
				if( !V[to[i]] )
					V[to[i]] = true , que[ ( ++tail ) &= mod ] = to[i];
			}
	}
}

void build_edge(){
	Dinic :: S = 1 + n ; Dinic :: T = n ;
	For( i , 2 , n - 1 )
		Dinic :: Ins( i , i + n , val[i] ) ;
	For( i , 2 , Ct ){
		if( dis[to[i]] - dis[to[i ^ 1]] == Dt[i] )
			Dinic :: Ins( to[i ^ 1] + n , to[i] , Dinic :: inf );
	}
}

int main(){
	
	read_in();
	
	spfa();
	
	build_edge();
	
	Dinic :: Run();
	
	return 0;
}
