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

static const int maxn = 50 + 10;
static const int maxx = maxn << 1;
static const int maxm = 5500	;
static const int inf = ~0U >> 1;

int cases;
int n;
int S;
int T;

int sleep_number;

bool relation_graph[maxn][maxn];
bool Is_school_student[maxn];
bool Go_home[maxn];

void read_case_number(){
	scanf( cases ) ;
}

void read_in(){
	scanf( n ) ;
	For( i , 1 , n )
		scanf( Is_school_student[i] ) ;
	For( i , 1 , n )
		scanf( Go_home[i] ) ;
	For( i , 1 , n )For( j , 1 , n )
		scanf( relation_graph[i][j] ) ;
}

int Ct;
int Ht[maxx];
int Nt[maxm];
int to[maxm];
int cap[maxm];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; cap[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; cap[Ct] = 0 ;
}

void init_edge(){
	Ct = 1 ; memset( Ht , 0 , sizeof Ht ) ;
	S = 0 ; T = n << 1 | 1 ;
}

int calc_number_of_sleep_at_school(){
	int res = n ;
	For( i , 1 , n )
		res -= Is_school_student[i] * Go_home[i] ;
	return res ;
}

void edge_S_to_sleep_at_school(){
	For( i , 1 , n )
		if( !( Is_school_student[i] * Go_home[i] ) )
			Ins( S , i , 1 ) ;
}

void edge_bed_to_T(){
	For( i , 1 , n )
		if( Is_school_student[i] )
			Ins( i + n , T , 1 ) ;
}

void edge_usable_bed(){
	For( i , 1 , n )relation_graph[i][i] = true ;
	For( i , 1 , n )For( j , 1 , n )
		if( relation_graph[i][j] && !( Is_school_student[i] * Go_home[i] ) )
			Ins( i , j + n , 1 );
}

void build_edge(){
	
	init_edge();
	
	sleep_number = calc_number_of_sleep_at_school();
	
	edge_S_to_sleep_at_school();
	
	edge_bed_to_T();
	
	edge_usable_bed();
	
}

namespace get_maxflow{
	
	int cur[maxx];
	int dep[maxx];
	
	bool bfs(){
		static int que[maxx];
		int head = 0 , tail = 0 ;
		memset( dep , 0 , sizeof dep ) ;
		que[ ++tail ] = S ; dep[S] = 1 ;
		while( head != tail ){
			int x = que[ ++head ] ;
			Rep( i , Ht[x] , Nt[i] )
				if( !dep[to[i]] && cap[i] ){
					dep[to[i]] = dep[x] + 1 ;
					if( to[i] == T )return true ;
					que[ ++tail ] = to[i] ;
				}
		}
		return false;
	}
	
	int dfs( int x , int maxflow ){
		if( x == T )return maxflow ;
		for( int& i = cur[x] ; i ; i = Nt[i] )
			if( dep[to[i]] == dep[x] + 1 && cap[i] ){
				int t = dfs( to[i] , min( maxflow , cap[i] )  );
				if( t )
					return cap[i] -= t , cap[i ^ 1] += t , t ;
			}
		return 0 ;
	}
	
	int dinic(){
		int res = 0 , t ;
		while( bfs() ){
			memcpy( cur , Ht , sizeof cur ) ;
			while( t = dfs( S, inf ) ) res += t ;
		}
		return res ;
	}
	
}

int main(){
	
	read_case_number();
	
	while( cases-- ){
		
		read_in();
		
		build_edge();
		
		puts( get_maxflow :: dinic() == sleep_number ? "^_^" : "T_T" ) ;
		
	}
	
	return 0;
}
