#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 500 + 10;
static const int maxm = maxn * maxn << 1;
static const int Inf = 0x7fffffff;

int n;
int A[maxn];

int len;
int F[maxn];

int S;
int T;

int Ct = 1;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
int cap[maxm];
int tmp[maxm];

int Odg[maxn];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	tmp[Ct] = cap[Ct] = z;
	Odg[x]++;
}

void read_in(){
	scanf( n ) ;
	For( i , 1 , n )scanf( A[i] ) ;
}

void LIS(){
	For( i , 1 , n ){
		For( j , 1 , i - 1 )
			if( A[j] <= A[i] )F[i] = max( F[i] , F[j] );
		len = max( len , ++F[i] );
	}
}

void build_edge(){
	S = 0 ; T = n + 1 ;
	Lop( i , n , 1 ){
		if( F[i] == len )
			Ins( i , T , 1 ) , Ins( T , i , 0 );
		Lop( j , i - 1 , 1 )if( F[j] == F[i] - 1 && A[i] >= A[j] )
			Ins( j , i , 1 ) , Ins( i , j , 0 );
	}
	For( i , 1 , n )
		if( F[i] == 1 && Odg[i] )
			Ins( S , i , 1 ) , Ins( i , S , 0 );
}

int cur[maxn];
int dep[maxn];

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
			if( !dep[y] && cap[i] ){
				dep[y] = dep[x] + 1;
				if( y == T )return true;
				que[ ++tail ] = y;
			}
	}
	return false;
}

int Dfs( int x , int maxflow ){
	if( x == T )return maxflow;
	for( int i = cur[x] ; i ; i = Nt[i] )
		if( dep[y] == dep[x] + 1 && cap[i] ){
			int t = Dfs( y , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t;
		}
	return 0;
}

int Dinic(){
	int res = 0 , t ;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = Dfs( S , Inf ) )res += t;
	}
	return res;
}

#undef y

void display(){
	printf("%d\n" , len );
	printf("%d\n" , Dinic() );
	memcpy( cap , tmp , sizeof cap );
	For( i , 2 , Ct )
		if( To[i] == T && To[i ^ 1] == n )cap[i] = Inf;
		else if( To[i ^ 1] == S && To[i] == 1 )cap[i] = Inf;
	printf("%d\n" , Dinic() );
}

int main(){
	
	read_in();
	
	LIS();
	
	build_edge();
	
	display();
	
	return 0;
}
