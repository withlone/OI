#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >inline void swap( type &x , type &y ){ type t = x ; x = y ; y = t ; }
template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 8e2 + 10;
static const int maxm = 15e3 + 10;
static const int maxx = maxn << 1;
static const int maxe = 3 * maxn + maxm << 1;
static const int mod = ( 1 << 11 ) - 1;
static const int inf = ~0U >> 1;

int n;
int m;
int S;
int T;

int location_time[maxn];
int start_point[maxm];
int end_point[maxm];
int cost_path[maxm];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )
		scanf( location_time[i] ) ;
	For( i , 1 , m )
		scanf( start_point[i] ) , scanf( end_point[i] ) , scanf( cost_path[i] ) ;
}

void Get_S_and_T(){
	S = 0 ; T = n << 1 | 1 ;
}

int Ct = 1 ;
int Ht[maxx];
int Nt[maxe];
int to[maxe];
int Dt[maxe];
int cap[maxe];

void Ins( int x , int y , int p , int q ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = p ; cap[Ct] = q ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; Dt[Ct] = -p; cap[Ct] = 0 ;
}

void edge_S_to_left(){
	For( i , 1 , n )
		Ins( S , i , 0 , 1 ) ;
}

void edge_right_to_T(){
	For( i , 1 + n , n + n )
		Ins( i , T , 0 , 1 ) ;
}

void adjust_edge_point(){
	For( i , 1 , m )
		if( start_point[i] > end_point[i] )
			swap( start_point[i] , end_point[i] ) ;
}

void edge_from_real_edge(){
	adjust_edge_point();
	For( i , 1 , m )
		Ins( start_point[i] , end_point[i] + n , cost_path[i] , 1 ) ;
}

void edge_of_location(){
	For( i , 1 + n , n + n )
		Ins( S , i , location_time[i - n] , 1 ) ;
}

void build_edge(){
	
	Get_S_and_T();
	
	edge_S_to_left();
	
	edge_right_to_T();
	
	edge_of_location();
	
	edge_from_real_edge();
	
}

bool V[maxx];
int que[mod + 10];
int dis[maxx];
int pre[maxx];

void EK(){
	int ans = 0 ;
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
			cap[ pre[i] ] -= maxflow , cap[ pre[i] ^ 1 ] += maxflow ;
		ans += dis[T] * maxflow ;
	}
	printf("%d\n" , ans );
}

int main(){
	
	read_in();
	
	build_edge();
	
	EK();
	
	return 0 ;
}
