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
static const int maxx = maxn << 1;
static const int maxm = maxn << 3;
static const int mod = ( 1 << 7 ) - 1 ;
static const int inf = ~0U >> 1;

int n;
int m;
int reserves;
int S;
int T;

int U[maxn];
int d[maxn];

void read_in(){
	scanf( n ) ; scanf( m ) ; scanf(  reserves );
	For( i , 1 , n )
		scanf( U[i] ) ;
	For( i , 1 , n )
		scanf( d[i] ) ;
}

int Ct = 1;
int Ht[maxx];
int Nt[maxm];
int to[maxm];
int Dt[maxm];
int cap[maxm];

void Ins( int x , int y , int p , int q ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = p ; cap[Ct] = q ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; Dt[Ct] = -p; cap[Ct] = 0 ;
}

void Get_S_and_T(){
	S = 0 ; T = n << 1 | 1;
}

void edge_direct_buy(){
	For( i , 1 , n )
		Ins( S , i , d[i] , inf ) ;
}

void edge_need_num(){
	For( i , 1 , n )
		Ins( i + n , T , 0 , U[i] ) ;
}

void edge_to_oneself(){
	For( i , 1 , n )
		Ins( i , i + n , 0 , inf ) ;
}

void edge_store_goods(){
	For( i , 1 , n - 1 )
		Ins( i , i + 1 , m , reserves ) ;
}

void build_edge(){
	
	Get_S_and_T();
	
	edge_direct_buy();
	
	edge_need_num();
	
	edge_to_oneself();
	
	edge_store_goods();
	
}

int que[mod + 10];
int dis[maxx];
int pre[maxx];
bool V[maxx];

int EK(){
	int ans = 0 ;
	while( true ){
		memset( V , 0 , sizeof V );
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
		if( dis[T] == dis[T + 1] )return ans ;
		int maxflow = inf ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )maxflow = min( maxflow , cap[ pre[i] ] ) ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			cap[ pre[i] ] -= maxflow , cap[ pre[i] ^ 1 ] += maxflow ;
		ans += dis[T] * maxflow ;
	}
}

int main(){
	
	read_in();
	
	build_edge();
	
	printf("%d\n" , EK() );
	
	return 0 ;
}
