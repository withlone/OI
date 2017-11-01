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

static const int maxn = 60 + 10;
static const int maxm = 9 + 10;
static const int maxx = maxn * ( 1 + maxm );
static const int maxe = 1e6 + 10;
static const int inf = ~0U >> 1;
static const int mod = ( 1 << 11 ) - 1 ;

int n;
int m;
int S;
int T;

int ti[maxn][maxm];

void read_in(){
	scanf( m ) ; scanf( n ) ;
	For( i , 1 , n )For( j , 1 , m )
		scanf( ti[i][j] ) ;
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

int cnt;
int num[maxn][maxm];

void Lable(){
	cnt = n;
	For( i , 1 , n )For( j , 1 , m )
		num[i][j] = ++cnt;
}

void build_edge(){
	S = 0 ; T = ++cnt ;
	For( i , 1 , n )
		Ins( S , i , 0 , 1 ) ;
	For( i , 1 , n )For( j , 1 , m )
		Ins( num[i][j] , T , 0 , 1 ) ;
	For( car , 1 , n )For( i , 1 , n )For( j , 1 , m )
		Ins( car , num[i][j] , i * ti[car][j] , 1 ) ;
}

void EK(){
	int ans = 0;
	static bool V[maxx];
	static int dis[maxx];
	static int pre[maxx];
	static int que[mod + 50];
	while( true ){
		memset( V , 0 , sizeof V );
		memset( dis , 0x3f , sizeof dis );
		int head = 0 , tail = -1 ;
		que[ ++tail ] = S ; dis[S] = 0 ;
		while( head != ( tail + 1 ) & mod ){
			int x = que[ head++ ] ; head &= mod ; V[x] = false;
			Rep( i , Ht[x] , Nt[i] )
				if( dis[to[i]] > dis[x] + Dt[i] && cap[i] ){
					dis[to[i]] = dis[x] + Dt[i] ; pre[to[i]] = i ;
					if( !V[to[i]] )
						V[to[i]] = true , que[ ( ++tail ) &= mod ] = to[i];
				}
		}
		if( dis[T] == dis[T + 1] )break;
		int maxflow = inf ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )maxflow = min( maxflow , cap[ pre[i] ] );
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			cap[ pre[i] ] -= maxflow , cap[ pre[i] ^ 1 ] += maxflow ;
		ans += dis[T] * maxflow ;
	}
	printf("%.2lf\n" , ans * 1.0 / n );
}

int main(){
	
	read_in();
	
	Lable();
	
	build_edge();
	
	EK();
	
	return 0;
}
