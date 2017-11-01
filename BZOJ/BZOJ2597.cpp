#include<cstdio>
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

static const int maxn = 100 + 10 ;
static const int maxx = 1e4 + 10 ;
static const int maxm = maxx * 10 ;
static const int mod = ( 1 << 14 ) - 1 ;
static const int inf = ~0U >> 1 ;

int n ;
int S ;
int T ;

int competition[maxn][maxn] ;

bool V[maxx] ;
int dis[maxx] ;
int pre[maxx] ;
int que[mod + 10] ;

int cnt ;
int num[maxn][maxn] ;

int degree[maxn];

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
	
	scanf( n ) ;
	
	For( i , 1 , n )For( j , 1 , n )
		scanf( competition[i][j] ) ;
	
}

void preparation(){
	
	cnt = n ;
	
	For( i , 1 , n )For( j , i + 1 , n )
		if( !competition[i][j] )
			++degree[j] ;
		else if( competition[i][j] == 1 )
			++degree[i] ;
		else
			num[i][j] = ++cnt ;
	
}

void get_S_and_T(){
	S = ++cnt ; T = ++cnt ;
}

void edge_about_competition(){
	
	For( i , 1 , n )For( j , i + 1 , n )
		if( num[i][j] )
			ins( S , num[i][j] , 0 , 1 ) ,
			ins( num[i][j] , i , 0 , 1 ) ,
			ins( num[i][j] , j , 0 , 1 ) ;
	
}

void edge_of_player(){
	
	For( i , 1 , n ){
	
		if( degree[i] )
			ins( S , i , 0 , degree[i] ) ;
		
		For( j , 0 , n - 2 )
			ins( i , T , j , 1 ) ;
		
	}
	
}

void build_edge(){
	
	get_S_and_T() ;
	
	edge_about_competition() ;
	
	edge_of_player() ;
	
}

int EK(){
	
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
		
		if( dis[T] == dis[T + 1] )return ans ;
		
		int maxflow = inf ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			maxflow = min( maxflow , cap[ pre[i] ] ) ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			cap[ pre[i] ] -= maxflow , cap[ pre[i] ^ 1 ] += maxflow ;
		
		ans += maxflow * dis[T] ;
		
	}
	
}

void display(){
	
	printf("%d\n" , n * ( n - 1 ) * ( n - 2 ) / 6 - EK() ) ;
	
	For( i , 1 , n )For( j , i + 1 , n )if( num[i][j] )
		Rep( k , Ht[ num[i][j] ] , Nt[k] )
			if( to[k] != S && !cap[k] ){
				
				if( to[k] == i )
					competition[i][j] = 1 ,
					competition[j][i] = 0 ;
				else
					competition[i][j] = 0 ,
					competition[j][i] = 1 ;
				
				break ;
				
			}
	
	For( i , 1 , n )For( j , 1 , n )
		printf("%d%c" , competition[i][j] , j == n ? '\n' : ' ' ) ;
	
}

int main(){
	
	read_in() ;
	
	preparation() ;
	
	build_edge() ;
	
	display() ;
	
	return 0 ;
}
