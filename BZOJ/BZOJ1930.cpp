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

static const int maxn = 2e3 + 10;
static const int maxx = maxn << 1;
static const int maxm = 4e6 + 10;
static const int mod = ( 1 << 12 ) - 1;
static const int inf = ~0U >> 1;

int n;
int S;
int T;
int _S;

struct point{
	int x;
	int y;
	bool operator < ( point t ) const { return x == t.x ? y < t.y : x < t.x ; }
}pt[maxn];

void read_in(){
	scanf( n ) ;
	For( i , 1 , n )
		scanf( pt[i].x ) , scanf( pt[i].y ) ;
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

void build_edge(){
	S = 0 ; T = n << 1 | 1 ; _S = T + 1 ;
	Ins( S , _S , 0 , 2 ) ;
	sort( 1 + pt , 1 + n + pt );
	For( i , 1 , n ){
		int top = inf;
		For( j , i + 1 , n )
			if( pt[i].y <= pt[j].y && pt[j].y < top )
				Ins( i , j + n , 0 , inf ) , top = pt[j].y ;
		Ins( i + n , i , 1 , 1 ) ,
		Ins( i + n , i , 0 , 1 ) ,
		Ins( _S , i + n , 0 , inf ) ,
		Ins( i , T , 0 , inf ) ;
	}
}

int EK(){
	static int que[mod + 50];
	static int pre[maxx];
	static int dis[maxx];
	static bool V[maxx];
	int ans = 0 ;
	while( true ){
		memset( V , 0 , sizeof V ) ;
		memset( dis , -0x3f , sizeof dis ) ;
		int head = 0 , tail = 0 ;
		que[ ++tail ] = S ; dis[S] = 0 ;
		while( head != tail ){
			int x = que[ ++head &= mod ] ; V[x] = false ;
			Rep( i , Ht[x] , Nt[i] )
				if( dis[to[i]] < dis[x] + Dt[i] && cap[i] ){
					dis[to[i]] = dis[x] + Dt[i] ; pre[to[i]] = i ;
					if( !V[to[i]] )
						V[to[i]] = true , que[ ++tail &= mod ] = to[i] ;
				}
		}
		if( dis[T] == dis[T + 2] )return ans ;
		int maxflow = inf ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )maxflow = min( maxflow , cap[ pre[i] ] ) ;
		for( int i = T ; i != S ; i = to[ pre[i] ^ 1 ] )
			cap[ pre[i] ] -= maxflow , cap[ pre[i] ^ 1 ] += maxflow ;
		ans += dis[T] * maxflow ;
	}
	return ans;
}

void display(){
	printf("%d\n" , EK() );
}

int main(){
	
	read_in();
	
	build_edge();
	
	display();
	
	return 0;
}
