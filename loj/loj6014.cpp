#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 1e3 + 10;
static const int maxm = maxn * 10;
static const int maxk = 4;
static const int Inf = 0x7fffffff;

int n;
int k;
int S;
int T;
int tot;

int dct;
int A[maxn];
int B[maxn];
int C[maxn];
int dir[maxn << 1];

void read_in(){
	scanf( n ) ; scanf( k ) ;
	For( i , 1 , n ){
		scanf( A[i] ) , scanf( B[i] ) ;
		if( A[i] > B[i] )swap( A[i] , B[i] ) ;
		C[i] = B[i] - A[i] , dir[ ++dct ] = A[i] , dir[ ++dct ] = B[i] ;
	}
}

void discretization(){
	sort( 1 + dir , 1 + dct + dir ) ;
	dct = unique( 1 + dir , 1 + dct + dir ) - dir - 1;
	For( i , 1 , n )
		A[i] = lower_bound( 1 + dir , 1 + dct + dir , A[i] ) - dir ,
		B[i] = lower_bound( 1 + dir , 1 + dct + dir , B[i] ) - dir ;
}

int Ct = 1;
int Ht[maxn];
int Nt[maxm];
int to[maxm];
int Dt[maxm];
int cap[maxm];

void Ins( int x , int y , int p , int q ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	to[Ct] = y;
	Dt[Ct] = p;
	cap[Ct] = q;
}

void build_edge(){
	S = 0 ; T = dct + 1 ; tot = T + 2;
	Ins( S , 1 , 0 , k ) , Ins( 1 , S , 0 , 0 ) ,
	Ins( dct , T , 0 , k ) , Ins( T , dct , 0 , 0 ) ;
	For( i , 1 , dct - 1 )
		Ins( i , i + 1 , 0 , Inf ) , Ins( i + 1 , i , 0 , 0 ) ;
	For( i , 1 , n )
		Ins( A[i] , B[i] , C[i] , 1 ) , Ins( B[i] , A[i] , -C[i] , 0 ) ;
}

bool V[maxn];
int dis[maxn];
int que[maxn];
int pre[maxn];

void EK(){
	int ans = 0 ;
	while( true ){
		memset( V , 0 , sizeof( bool ) * tot );
		memset( dis , -0x3f , sizeof( int ) * tot );
		int head = 0 , tail = -1;
		que[ ++tail ] = S ; dis[S] = 0 ;
		while( head != ( tail + 1 ) % tot ){
			int x = que[ head++ ] ; V[x] = false ;
			if( head == tot )head = 0;
			Rep( i , Ht[x] , Nt[i] )
				if( dis[to[i]] < dis[x] + Dt[i] && cap[i] ){
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
			cap[ pre[i] ] -= maxflow , cap[ pre[i] ^ 1 ] += maxflow ;
		ans += maxflow * dis[T];
	}
	printf("%d\n" , ans );
}

int main(){
	
	read_in();
	
	discretization();
	
	build_edge();
	
	EK();
	
	return 0;
}
