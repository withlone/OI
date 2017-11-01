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

static const int maxn = 50 + 10;
static const int maxm = 2450 + 10;
static const int maxx = 5e3 + 10;
static const int maxe = 6e5 + 10;
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;
int people_number;

int start_point[maxm];
int end_point[maxm];
int ticket_limit[maxm];

void read_in(){
	scanf( n ) ; scanf( m ) ; scanf( people_number ) ;
	For( i , 1 , m )
		scanf( start_point[i] ) , scanf( end_point[i] ) , scanf( ticket_limit[i] ) ;
}

int Ct = 1 ;
int Ht[maxx];
int Nt[maxe];
int to[maxe];
int cap[maxe];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

namespace get_maxflow{
	
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
				int t = dfs( to[i] , min( maxflow , cap[i] ) ) ;
				if( t )
					return cap[i] -= t , cap[i ^ 1] += t , t ;
			}
		return 0 ;
	}
	
	int dinic(){
		int res = 0 , t;
		while( bfs() ){
			memcpy( cur , Ht , sizeof cur );
			while( t = dfs( S , inf ) ) res += t ;
		}
		return res ;
	}
	
}

int cnt;
int number[maxn << 1][maxn];

void preparation(){
	For( i , 1 , n + people_number )
		For( j , 1 , n )
			number[i][j] = ++cnt;
}

void Get_S_and_T(){
	S = 0 ; T = ++cnt ;
}

void edge_S_to_begin(){
	For( i , 1 , n + people_number )
		Ins( S , number[i][1] , inf ) ;
}

void edge_end_to_T(){
	For( i , 1 , n + people_number )
		Ins( number[i][n] , T , inf ) ;
}

void Run(){
	int res = 0 ;
	
	Get_S_and_T();
	
	edge_S_to_begin();
	
	edge_end_to_T();
	
	For( day , 1 , n + people_number ){
		For( i , 1 , m )
			Ins( number[day][ start_point[i] ] , number[day + 1][ end_point[i] ] , ticket_limit[i] );
		if( ( res += get_maxflow :: dinic() ) >= people_number )return printf("%d\n" , day ) , void ();
	}
}

int main(){
	
	read_in();
	
	preparation();
	
	Run();
	
	return 0;
}
