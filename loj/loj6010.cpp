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

static const int maxn = 20 + 10;
static const int maxx = 500 + 10;
static const int maxm = 8e5 + 10;
static const int Inf = 0x7fffffff;

int n;
int m;
int S;
int T;
int tot;

int cnt;
int A[maxn][maxn];
int num[maxn][maxn];

void read_in(){
	scanf( m ) ; scanf( n ) ;
	For( i , 1 , n )For( j , 1 , m + i - 1 )
		scanf( A[i][j] ) , num[i][j] = ++cnt;
}

int Ct = 1;
int Ht[maxx];
int Nt[maxm];
int to[maxm];
int Dt[maxm];
int cap[maxm];
int tmp[maxm];

int point1;
int point2;
int point3;

void Ins( int x , int y , int p , int q ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	to[Ct] = y;
	Dt[Ct] = p;
	tmp[Ct] = q;
}

void build_edge1(){
	S = 0 ; T = cnt << 1 | 1 ; tot = T + 1 ;
	For( i , 1 , m )
		Ins( S , num[1][i] , A[1][i] , 1 ) , Ins( num[1][i] , S , -A[1][i] , 0 ) ;
	point1 = Ct;
	For( i , 1 , m + n - 1 )
		Ins( num[n][i] , T , 0 , 1 ) , Ins( T , num[n][i] , 0 , 0 ) ;
	point2 = Ct;
	For( i , 1 , n - 1 )For( j , 1 , m + i - 1 )
		Ins( num[i][j] , num[i + 1][j] + cnt , 0 , 1 ) ,
		Ins( num[i + 1][j] + cnt , num[i][j] , 0 , 0 ) ,
		Ins( num[i][j] , num[i + 1][j + 1] + cnt , 0 , 1 ) ,
		Ins( num[i + 1][j + 1] + cnt , num[i][j] , 0 , 0 ) ;
	point3 = Ct;
	For( i , 2 , n )For( j , 1 , m + i - 1 )
		Ins( num[i][j] + cnt , num[i][j] , A[i][j] , 1 ) ,
		Ins( num[i][j] , num[i][j] + cnt , -A[i][j] , 0 ) ;
}

void build_edge2(){
	For( i , point1 + 1 , point2 )
		tmp[i++] = Inf;
	For( i , point3 + 1 , Ct )
		tmp[i++] = Inf;
}

void build_edge3(){
	For( i , point2 + 1 , point3 )
		tmp[i++] = Inf;
}

int dis[maxx];
int pre[maxx];
bool V[maxx];

#define y to[i]

void EK(){
	int ans = 0 ;
	static int que[maxx];
	memcpy( cap , tmp , sizeof cap );
	while( true ){
		memset( V , 0 , sizeof( bool ) * tot ) ;
		memset( dis , 0 , sizeof( int ) * tot ) ;
		int head = 0 , tail = -1 ;
		que[ ++tail ] = S;
		while( head != ( tail + 1 ) % tot ){
			int x = que[ head++ ] ; V[x] = false;
			if( head == tot )head = 0;
			Rep( i , Ht[x] , Nt[i] )
				if( dis[y] < dis[x] + Dt[i] && cap[i] ){
					dis[y] = dis[x] + Dt[i];pre[y] = i;
					if( !V[y] ){
						V[y] = true;
						if( tail == tot - 1 )que[tail = 0] = y;
						else que[ ++tail ] = y;
					}
				}
		}
		if( !dis[T] )break;
		int maxflow = Inf;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )maxflow = min( maxflow , cap[ pre[i] ] ) ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			cap[ pre[i] ] -= maxflow , cap[ pre[i] ^ 1 ] += maxflow ;
		ans += maxflow * dis[T];
	}
	printf("%d\n" , ans );
}

#undef y

int main(){
	
	read_in();
	
	build_edge1();
	
	EK();
	
	build_edge2();
	
	EK();
	
	build_edge3();
	
	EK();
	
	return 0;
}
