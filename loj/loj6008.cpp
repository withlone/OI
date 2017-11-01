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

static const int maxn = 2e3 + 10;
static const int maxm = 12 * maxn;
static const int Inf = 0x7fffffff;

int n;
int S;
int T;
int tot;
int paper;
int time1;
int time2;
int cost1;
int cost2;

int val[maxn];

void read_in(){
	scanf( n ) ; scanf( paper ) ;
	scanf( time1 ) ; scanf( cost1 ) ;
	scanf( time2 ) ; scanf( cost2 ) ;
	For( i , 1 , n )scanf( val[i] ) ;
}

int Ct = 1;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
int Dt[maxm];
int cap[maxm];

void Ins( int x , int y , int p , int q ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = p;
	cap[Ct] = q;
}

void build_edge(){
	S = 0 ; T = n << 1 | 1 ; tot = maxn - 1 ;
	For( i , 1 , n ){
		Ins( S , i , 0 , val[i] ) , Ins( i , S , 0 , 0 ) ,
		Ins( i + n , T , 0 , val[i] ) , Ins( T , i + n , 0 , 0 ) ,
		Ins( S , i + n , paper , Inf ) , Ins( i + n , S , -paper , 0 ) ;
		if( i != n )
			Ins( i , i + 1 , 0 , Inf ) , Ins( i + 1 , i , 0 , 0 ) ;
		if( i + time1 <= n )
			Ins( i , i + time1 + n , cost1 , Inf ) , Ins( i + time1 + n , i , -cost1 , 0 ) ;
		if( i + time2 <= n )
			Ins( i , i + time2 + n , cost2 , Inf ) , Ins( i + time2 + n , i , -cost2 , 0 ) ;
	}
}

int dis[maxn];
bool V[maxn];

#define y To[i]

bool spfa(){
	int ans = 0;
	static int que[maxn] , pre[maxn];
	while( true ){
		int head = 0 , tail = -1;
		memset( V , 0 , sizeof V );
		memset( dis , 127 , sizeof dis );
		que[ ++tail ] = T ; dis[T] = 0 ;
		while( head != ( tail + 1 ) % tot ){
			int x = que[ head++ ] ; V[x] = false;
			if( head == tot )head = 0;
			Rep( i , Ht[x] , Nt[i] )
				if( dis[y] > dis[x] - Dt[i] && cap[i ^ 1] ){
					dis[y] = dis[x] - Dt[i];pre[y] = i;
					if( !V[y] ){
						V[y] = true;
						if( tail == tot - 1 )que[tail = 0] = y;
						else que[ ++tail ] = y;
					}
				}
		}
		if( dis[S] == dis[maxn - 1] )break;
		int maxflow = Inf;
		for( int i = S ; i != T ; i = To[ pre[i] ^ 1 ] )
			maxflow = min( maxflow , cap[ pre[i] ^ 1 ] );
		for( int i = S ; i != T ; i = To[ pre[i] ^ 1 ] )
			cap[ pre[i] ] += maxflow , cap[ pre[i] ^ 1 ] -= maxflow ;
		ans += maxflow * dis[S];
	}
	printf("%d\n" , ans );
}

#undef y

int main(){
	
	read_in();
	
	build_edge();
	
	spfa();
	
	return 0;
}
