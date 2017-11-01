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

static const int maxn = 40 + 10;
static const int maxm = 100 + 10;
static const int maxp = 800 + 10;
static const int maxx = maxp * ( maxm + 1 );
static const int maxe = maxp * maxn * maxm << 1;
static const int inf = ~0U >> 1;
static const int mod = ( 1 << 17 ) - 1;

int n;
int m;
int P;
int S;
int T;

int val[maxn];
int ti[maxn][maxm];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )scanf( val[i] ) ;
	For( i , 1 , n )For( j , 1 , m )
		scanf( ti[i][j] ) ;
}

int cnt;
int num[maxp][maxm];

void preparation(){
	For( i , 1 , n )P += val[i];
	cnt = n ;
	For( i , 1 , P )For( j , 1 , m )
		num[i][j] = ++cnt;
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

void build_edge(){
	S = 0 ; T = ++cnt ;
	For( i , 1 , n )
		Ins( S , i , 0 , val[i] ) ;
	For( i , 1 , P )For( j , 1 , m )
		Ins( num[i][j] , T , 0 , 1 ) ;
	For( k , 1 , n )For( j , 1 , m )
		Ins( k , num[1][j] , ti[k][j] , 1 ) ;
}

void EK(){
	int ans = 0 , top = 0;
	static int que[mod + 50];
	static int pre[maxx];
	static int dis[maxx];
	static bool V[maxx];
	while( true ){
		memset( V , 0 , sizeof V );
		memset( dis , 0x3f , sizeof dis );
		int head = 0 , tail = -1;
		que[ ++tail ] = S ; dis[S] = 0 ;
		while( head != (tail + 1) & mod ){
			int x = que[ head++ ] ; head &= mod ; V[x] = false;
			Rep( i , Ht[x] , Nt[i] )
				if( dis[to[i]] > dis[x] + Dt[i] && cap[i] ){
					dis[to[i]] = dis[x] + Dt[i] ; pre[to[i]] = i ;
					top = max( top , ( to[i] - n ) / m ) ;
					if( !V[to[i]] )
						V[to[i]] = true , que[ (++tail) &= mod ] = to[i];
				}
		}
		if( dis[T] == dis[T + 1] )break;
		int maxflow = inf , t1 , t2;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )maxflow = min( maxflow , cap[ pre[i] ] );
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			cap[ pre[i] ] -= maxflow , cap[ pre[i] ^ 1 ] += maxflow ;
		ans += maxflow * dis[T];
		int x = to[ pre[T] ^ 1 ] , y = x ;
		x = ( x - n - 1 ) / m + 2 , y = ( y - n - 1 ) % m + 1;
		For( i , 1 , n )Ins( i , num[x][y] , ti[i][y] * x , 1 ) ;
	}
	printf("%d\n" , ans );
}

int main(){
	
	read_in();
	
	preparation();
	
	build_edge();
	
	EK();
	
	return 0;
}
