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

static const int maxn = 100 + 10;
static const int maxx = maxn << 1;
static const int maxm = 1e5 + 10;
static const int Inf = 0x7fffffff;

int n;
int m;
int S;
int T;
int tot;

int a[maxn];
int b[maxn];
int c[maxn][maxn];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )scanf( a[i] ) ;
	For( i , 1 , m )scanf( b[i] ) ;
	For( i , 1 , n )For( j , 1 , m )
		scanf( c[i][j] ) ;
}

int Ct = 1;
int Ht[maxx];
int Nt[maxm];
int to[maxm];
int Dt[maxm];
int cap[maxm];
int tmp[maxm];

void Ins( int x , int y , int p , int q ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	to[Ct] = y;
	Dt[Ct] = p;
	tmp[Ct] = q;
}

void build_edge(){
	S = 0 ; T = n + m + 1 ; tot = T + 2 ;
	For( i , 1 , n )
		Ins( S , i , 0 , a[i] ) , Ins( i , S , 0 , 0 ) ;
	For( i , n + 1 , n + m )
		Ins( i , T , 0 , b[i - n] ) , Ins( T , i , 0 , 0 ) ;
	For( i , 1 , n )For( j , 1 , m )
		Ins( i , j + n , c[i][j] , b[j] ) ,
		Ins( j + n , i , -c[i][j] , 0 ) ;
}

bool V[maxx];
int dis[maxx];
int que[maxx];
int pre[maxx];

void EK( bool f ){
	int ans = 0;
	memcpy( cap , tmp , sizeof cap );
	while( true ){
		memset( V , 0 , sizeof( bool ) * tot );
		memset( dis , f ? -0x3f : 0x3f , sizeof( int ) * tot );
		int head = 0 , tail = -1;
		que[ ++tail ] = S ; dis[S] = 0 ;
		while( head != ( tail + 1 ) % tot ){
			int x = que[ head++ ] ; V[x] = false;
			if( head == tot )head = 0;
			Rep( i , Ht[x] , Nt[i] )
				if( dis[to[i]] > dis[x] + Dt[i] && cap[i] && !f ||
					dis[to[i]] < dis[x] + Dt[i] && cap[i] && f ){
					dis[to[i]] = dis[x] + Dt[i];pre[to[i]] = i;
					if( !V[to[i]] ){
						V[to[i]] = true;
						if( tail == tot - 1 )que[tail = 0] = to[i];
						else que[ ++tail ] = to[i];
					}
				}
		}
		if( dis[T] == dis[tot - 1] )break;
		int maxflow = Inf;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )maxflow = min( maxflow , cap[ pre[i] ] );
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			cap[ pre[i] ] -= maxflow , cap[ pre[i] ^ 1 ] += maxflow;
		ans += maxflow * dis[T];
	}
	printf("%d\n" , ans );
}

int main(){
	
	read_in();
	
	build_edge();
	
	EK( 0 );
	EK( 1 );
	
	return 0;
}
