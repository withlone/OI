#include<cstdio>
#include<cstdlib>
#include<cstring>

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) \
for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

static const int maxn = 20 + 10 ;
static const int maxx = 8e2 + 10 ;
static const int maxm = maxx * 22 ;
static const int mod = ( 1 << 10 ) - 1 ;
static const int inf = ~0U >> 1 ;

int n ;
int m ;
int S ;
int T ;
int tot ;

char begin_status[maxn][maxn] ;
char end_status[maxn][maxn] ;
char swap_times[maxn][maxn] ;

int cnt ;
int num[maxn][maxn] ;

int que[mod + 10];
int dis[maxx];
int pre[maxx];
bool V[maxx];

int Ct = 1 ;
int Ht[maxx] ;
int Nt[maxm] ;
int to[maxm] ;
int Dt[maxm] ;
int cap[maxm] ;

void ins( int x , int y , int p , int q ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = p ; cap[Ct] = q ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; Dt[Ct] = -p; cap[Ct] = 0 ;
}

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )
		scanf( "%s" , begin_status[i] + 1 ) ;
	For( i , 1 , n )
		scanf( "%s" , end_status[i] + 1 ) ;
	For( i , 1 , n )
		scanf( "%s" , swap_times[i] + 1 ) ;
}

int count_point( char status[][maxn] ){
	int res = 0 ;
	For( i , 1 , n )For( j , 1 , m )
		res += status[i][j] ;
	return res ;
}

void preparation(){
	For( i , 1 , n )For( j , 1 , m )
		num[i][j] = ++cnt ;
	For( i , 1 , n )For( j , 1 , m )
		begin_status[i][j] -= '0' ,
		end_status[i][j] -= '0' ,
		swap_times[i][j] -= '0' ;
	if( ( tot = count_point( begin_status ) ) != count_point( end_status ) )
		{ puts( "-1" ) ; exit( 0 ) ; }
}

void get_S_and_T(){
	S = 0 ; T = cnt << 1 | 1 ;
}

void edge_to_oneself(){
	For( i , 1 , n )For( j , 1 , m )
		ins( num[i][j] , num[i][j] + cnt , 0 ,
		swap_times[i][j] + ( end_status[i][j] && !begin_status[i][j] ) >> 1 ) ;
}

void edge_special(){
	For( i , 1 , n )For( j , 1 , m ){
		if( begin_status[i][j] )
			ins( S , num[i][j] + cnt , 0 , 1 ) ;
		if( end_status[i][j] )
			ins( num[i][j] + cnt , T , 0 , 1 ) ;
	}
}

void edge_between(){
	For( i , 1 , n )For( j , 1 , m ){
		num[i][j] += cnt ;
		if( num[i - 1][j] )
			ins( num[i][j] , num[i - 1][j] , 1 , inf ) ;
		if( num[i + 1][j] )
			ins( num[i][j] , num[i + 1][j] , 1 , inf ) ;
		if( num[i][j - 1] )
			ins( num[i][j] , num[i][j - 1] , 1 , inf ) ;
		if( num[i][j + 1] )
			ins( num[i][j] , num[i][j + 1] , 1 , inf ) ;
		if( num[i - 1][j - 1] )
			ins( num[i][j] , num[i - 1][j - 1] , 1 , inf ) ;
		if( num[i - 1][j + 1] )
			ins( num[i][j] , num[i - 1][j + 1] , 1 , inf ) ;
		if( num[i + 1][j - 1] )
			ins( num[i][j] , num[i + 1][j - 1] , 1 , inf ) ;
		if( num[i + 1][j + 1] )
			ins( num[i][j] , num[i + 1][j + 1] , 1 , inf ) ;
		num[i][j] -= cnt ;
	}
}

void build_edge(){
	
	get_S_and_T() ;
	
	edge_to_oneself() ;
	
	edge_special() ;
	
	edge_between() ;
	
}

int EK(){
	int ans = 0 ;
	int flow = 0 ;
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
		
		if( dis[T] == dis[T + 1] )return flow == tot ? ans : -1 ;
		
		int maxflow = inf ;
		
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			maxflow = min( maxflow , cap[ pre[i] ] ) ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			cap[ pre[i] ] -= maxflow , cap[ pre[i] ^ 1 ] += maxflow ;
		
		ans += dis[T] * maxflow ;
		
		flow += maxflow ;
		
	}
}

void display(){
	printf("%d\n" , EK() ) ;
}

int main(){
	
	read_in() ;
	
	preparation() ;
	
	build_edge() ;
	
	display() ;
	
	return 0 ;
}
