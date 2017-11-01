#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >inline void swap( type &x , type &y ){ type t = x ; x = y ; y = t ; }

static const int maxn = 50 + 10;
static const int maxm = maxn * maxn;
static const int inf = ~0U >> 1;

int n;
int S;
int T;
int S1;
int T1;
int S2;
int T2;
int time1;
int time2;

char mp[maxn][maxn];

void read_in(){
	For( i , 1 , n )
		scanf( "%s" , mp[i] + 1 ) ;
}

int Ct;
int Ht[maxn];
int Nt[maxm];
int to[maxm];
int cap[maxm];

void preparation(){
	Ct = 1 ; memset( Ht , 0 , sizeof Ht );
}

void Ins( int x , int y , int p , int q ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = p ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = q ;
}

void build_edge(){
	preparation();
	S = 0 ; T = n + 1 ;
	For( i , 1 , n )For( j , i + 1 , n )
		if( mp[i][j] == 'O' )
			Ins( i , j , 2 , 2 ) ;
		else if( mp[i][j] == 'N' )
			Ins( i , j , inf , inf ) ;
	Ins( S , S1 , time1 << 1 , 0 ) ,
	Ins( T1 , T , time1 << 1 , 0 ) ,
	Ins( S , S2 , time2 << 1 , 0 ) ,
	Ins( T2 , T , time2 << 1 , 0 ) ;
}

int cur[maxn];
int dep[maxn];

bool bfs(){
	static int que[maxn];
	int head = 0 , tail = 0 ;
	memset( dep , 0 , sizeof dep ) ;
	que[ ++tail ] = S ; dep[S] = 1 ;
	while( head != tail ){
		int x = que[ ++head ] ;
		Rep( i , Ht[x] , Nt[i] )
			if( !dep[to[i]] && cap[i] ){
				dep[to[i]] = dep[x] + 1 ;
				if( to[i] == T )return true;
				que[ ++tail ] = to[i];
			}
	}
	return false;
}

int dfs( int x , int maxflow ){
	if( x == T )return maxflow;
	for( int& i = cur[x] ; i ; i = Nt[i] )
		if( dep[to[i]] == dep[x] + 1 && cap[i] ){
			int t = dfs( to[i] , min( maxflow , cap[i] ) );
			if( t )
				return cap[i] -= t , cap[i ^ 1] += t , t ;
		}
	return 0 ;
}

int dinic(){
	int res = 0 , t ;
	while( bfs() ){
		memcpy( cur , Ht , sizeof cur );
		while( t = dfs( S , inf ) ) res += t ;
	}
	return res ;
}

void display(){
	build_edge();
	if( dinic() != ( time1 + time2 << 1 ) )return puts("No") , void ();
	swap( S2 , T2 ) ;
	build_edge();
	if( dinic() != ( time1 + time2 << 1 ) )return puts("No") , void ();
	puts("Yes");
}

int main(){
	
	while( scanf( "%d%d%d%d%d%d%d" , &n , &S1 , &T1 , &time1 , &S2 , &T2 , &time2 ) != EOF ){
		
		++S1 ; ++T1 ; ++S2 ; ++T2 ;
		
		read_in();
		
		display();
		
	}
	
	return 0;
}
