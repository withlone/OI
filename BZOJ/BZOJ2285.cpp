#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef double DB ;
static const int maxn = 700 + 10;
static const int maxm = 1e5 + 10;
static const int maxe = maxm << 2;
static const DB inf = 1e9;
static const int mod = ( 1 << 10 ) - 1;
static const DB eps = 1e-5 ;

int cmp( DB x , DB y ){ return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ; }

DB min( DB x , DB y ){ return cmp( x , y ) == -1 ? x : y ; }

int n;
int m;
int n1;
int m1;

int start_point[maxm];
int end_point[maxm];
int time_path[maxm];
int safe_path[maxm];

int one_side[maxm];
int other_side[maxm];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , m )
		scanf( start_point[i] ) , scanf( end_point[i] ) , scanf( time_path[i] ) , scanf( safe_path[i] ) ;
	scanf( m1 ) ; scanf( n1 ) ;
	For( i , 1 , m1 )
		scanf( one_side[i] ) , scanf( other_side[i] ) ;
}

DB val[maxn];

namespace get_ans{
	
	int Ct = 1;
	int Ht[maxn];
	int Nt[maxe];
	int to[maxe];
	DB cap[maxe];
	
	void Ins( int x , int y , DB z ){
		Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
		Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
	}
	
	int S;
	int T;
	
	void get_S_and_T(){
		S = 0 ; T = n1 + 1 ;
	}
	
	void edge_val_get(){
		For( i , 1 , n1 )
			if( i & 1 )
				Ins( S , i , val[i] ) ;
			else
				Ins( i , T , val[i] );
	}
	
	void edge_point_to_point(){
		For( i , 1 , m1 )
			Ins( one_side[i] , other_side[i] , inf );
	}
	
	void build_edge(){
		
		get_S_and_T();
		
		edge_val_get();
		
		edge_point_to_point();
		
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
					que[ ++tail ] = to[i] ;
				}
		}
		return false;
	}
	
	DB dfs( int x , DB maxflow ){
		if( x == T )return maxflow ;
		for( int& i = cur[x] ; i ; i = Nt[i] )
			if( dep[to[i]] == dep[x] + 1 && cap[i] > eps ){
				DB t = dfs( to[i] , min( maxflow , cap[i] ) ) ;
				if( t > eps )
					return cap[i] -= t , cap[i ^ 1] += t , t ;
			}
		return 0 ;
	}
	
	DB dinic(){
		DB res = 0 , t ;
		while( bfs() ){
			memcpy( cur , Ht , sizeof cur ) ;
			while( ( t = dfs( S , inf ) ) > eps ) res += t ;
		}
		return res ;
	}
	
	void main(){
		
		build_edge();
		
		printf("%.1lf\n" , dinic() ) ;
		
	}
	
}

int Ct = 1 ;
int Ht[maxn];
int Nt[maxm];
int to[maxm];
DB time[maxm];
DB safe[maxm];

void Ins( int x , int y , DB p , DB q ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; time[Ct] = p ; safe[Ct] = q ;
}

void build_edge(){
	For( i , 1 , m )
		Ins( start_point[i] , end_point[i] , time_path[i] , safe_path[i] ) ;
}

DB mid ;

bool chk( int T ){
	static int que[mod + 10];
	static DB dis[maxn];
	static bool V[maxn];
	int head = 0 , tail = 0 ;
	For( i , 0 ,  n )dis[i] = 1e9 , V[i] = false;
	que[ ++tail ] = n ; dis[n] = 0 ;
	while( head != tail ){
		int x = que[ ++head &= mod ] ; V[x] = false ;
		Rep( i , Ht[x] , Nt[i] )
			if( dis[to[i]] > dis[x] + time[i] - mid * safe[i] ){
				dis[to[i]] = dis[x] + time[i] - mid * safe[i] ;
				if( to[i] == T && dis[T] < eps )return true;
				if( !V[to[i]] )
					V[to[i]] = true , que[ ++tail &= mod ] = to[i] ;
			}
	}
	return dis[T] < eps ;
}

DB get_val( int x ){
	DB l = 0 , r = 7e4 ;
	while( r - l > eps ){
		mid = ( l + r ) / 2.0 ;
		if( chk( x ) )r = mid ;
		else l = mid ;
	}
	return l ;
}

void check_every_target_can_get(){
	For( i ,  1 , m1 )
		if( !cmp( val[ one_side[i] ] , val[ other_side[i] ] ) && !cmp( val[ one_side[i] ] , 7e4 ) )
			{ puts("-1") ; exit( 0 ) ; }
}

void get_shortest_path(){
	For( i , 1 , n1 ){
		val[i] = get_val( i ) ;
	}
	check_every_target_can_get();
}

int main(){
	
	read_in();
	
	build_edge();
	
	get_shortest_path();
	
	get_ans :: main();
	
	return 0 ;
}
