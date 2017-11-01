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

static const int maxn = 200 + 10;
static const int maxm = 2e4 + 10;
static const int maxx = maxn << 1;
static const int maxe = maxn + maxm << 1;
static const int mod = ( 1 << 9 ) - 1;
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;

int start_point[maxm];
int end_point[maxm];
int cost_road[maxm];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , m )	
		scanf( start_point[i] ) , scanf( end_point[i] ) , scanf( cost_road[i] ) ;
}

int Ct = 1;
int Ht[maxx];
int Nt[maxe];
int to[maxe];
int Dt[maxe];
int cap[maxe];

void Ins( int x , int y , int p , int q ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = p ; cap[Ct] = q ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; Dt[Ct] = -p; cap[Ct] = 0 ;
}

void edge_point_to_point(){
	Ins( 1 , 1 + n , 0 , inf ) ,
	Ins( n , n + n , 0 , inf ) ;
	For( i , 2 , n - 1 )
		Ins( i , i + n , 0 , 1 );
}

void real_edge(){
	For( i , 1 , m )
		Ins( start_point[i] + n , end_point[i] , cost_road[i] , 1 );
}

void build_edge(){
	S = 1 ; T = n << 1;
	
	edge_point_to_point();
	
	real_edge();
	
}

void EK(){
	static int que[mod + 50];
	static int dis[maxx];
	static int pre[maxx];
	static bool V[maxx];
	int len = 0 , flow = 0;
	while( true ){
		memset( V , 0 , sizeof V ) ;
		memset( dis , 0x3f , sizeof dis ) ;
		int head = 0 , tail = 0 ;
		que[ ++tail ] = S ; dis[S] = 0 ;
		while( head != tail ){
			int x = que[ ++head &= mod ] ; V[x] = false ;
			Rep( i , Ht[x] , Nt[i] )
				if( dis[to[i]] > dis[x] + Dt[i] && cap[i] ){
					dis[to[i]] = dis[x] + Dt[i] ; pre[to[i]] = i ;
					if( !V[to[i]] )
						V[to[i]] = true , que[ ++tail &= mod ] = to[i] ;
				}
		}
		if( dis[T] == dis[T + 1] )break;
		int maxflow = inf ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )maxflow = min( maxflow , cap[ pre[i] ] ) ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			cap[ pre[i] ] -= maxflow , cap[pre[i] ^ 1] += maxflow ;
		flow += maxflow ;
		len += maxflow * dis[T];
	}
	printf("%d %d\n" , flow , len ) ;
}

int main(){
	
	read_in();
	
	build_edge();
	
	EK();
	
	return 0 ;
}
