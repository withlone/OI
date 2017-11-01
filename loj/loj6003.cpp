#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int top = 2e3;
static const int maxn = 4e3 + 10;
static const int maxm = 1e6 + 10;
static const int Inf = 0x7fffffff;

int n;
int S;
int T;
int mid;

int Ct = 1;
int Ht[maxn];
int Nt[maxm];
int Cm[maxm];
int To[maxm];
int cap[maxm];
int tmp[maxm];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	Cm[Ct] = x;
	To[Ct] = y;
	tmp[Ct] = cap[Ct] = z;
}

void build_edge(){
	S = 0 ; T = top << 1 | 1 ;
	For( i , 1 , top )
		Ins( S , i , 1 ) , Ins( i , S , 0 ) ,
		Ins( i + top , T , 1 ) , Ins( T , i + top , 0 ) ;
	For( i , 1 , top )
		For( j , 1 , top )
			if( j * j - i > top )break;
			else if( j * j - i <= i )continue;
			else Ins( i , j * j - i + top , 1 ) , Ins( j * j - i + top , i , 0 ) ;
}

int dep[maxn];
int cur[maxn];

#define y To[i]

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = -1;
	que[ ++tail ] = S;
	memset( dep , 0 , sizeof dep );
	dep[S] = 1;
	while( head <= tail ){
		int x = que[ head++ ];
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[y] && cap[i] && ( y <= mid || y == S || y == T || y > top && y - top <= mid ) ){
				dep[y] = dep[x] + 1;
				if( y == T )return true;
				que[ ++tail ] = y;
			}
	}
	return false;
}

int Dfs( int x , int maxflow ){
	if( x == T )return maxflow;
	Rep( i , Ht[x] , Nt[i] )
		if( dep[y] == dep[x] + 1 && cap[i] && ( y <= mid || y == S || y == T || y > top && y - top <= mid ) ){
			int t = Dfs( y , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t;
		}
	return 0;
}

#undef y

bool chk(){
	int res = 0 , t;
	memcpy( cap , tmp , sizeof cap );
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = Dfs( S , Inf ) )res += t ;
	}
	return mid - res <= n ;
}

int div( int l , int r ){
	int res;
	while( l <= r ){
		mid = l + r >> 1;
		if( chk() )res = mid , l = mid + 1;
		else r = mid - 1;
	}
	return res;
}

int Nxt[maxn];
bool Vis[maxn];

void display(){
	int ans ;
	printf("%d\n" , ans = div( 1 , top ) );
	mid = ans;chk();
	For( i , top << 2 | 2 , Ct ){
		if( !cap[i] )Nxt[ Cm[i] ] = To[i] - top;
		i++;
	}
	For( i , 1 , ans )if( !Vis[i] ){
		int t = i;
		while( Nxt[t] )
			Vis[t] = true , printf("%d " , t ) , t = Nxt[t];
		printf("%d\n" , t );Vis[t] = true;
	}
}

int main(){
	
	scanf( n ) ;
	
	build_edge();
	
	display();
	
	return 0;
}
