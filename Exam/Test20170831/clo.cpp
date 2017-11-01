#include<cstdio>

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) \
for( int i = (_Begin) ; i ; i = (_Add) )

namespace FI {
	const int SIZE = 1 << 15 | 1;
	char buf[SIZE], *front, *back;
	void NextChar(char &c) {
		if(front == back) back = (front=buf) + fread(buf, 1, SIZE, stdin);
		c = front==back ? (char)EOF : *front++;
	}
	void scanf(int &x) {
		char c;
		for(NextChar(c); c>'9'||c<'0'; NextChar(c)) ;
		for(x=0; c>='0'&&c<='9'; NextChar(c)) x = x*10+c-'0';
	}
}using namespace FI ;

static const int maxn = 1e5 + 10 ;
static const int maxm = 2e5 + 10 ;
static const int maxe = maxm << 1 ;

int n ;
int m ;

int A[maxm] ;
int B[maxm] ;

bool V[maxn] ;
bool Vis[maxn] ;
bool used[maxe] ;

int degree[maxn] ;
int ans[maxn] ;
int que[maxn] ;

int Fa[maxn] ;

int Ct = 1 ;
int Ht[maxn] ;
int Nt[maxe] ;
int to[maxe] ;

inline void ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

inline void read_in(){
	
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , m )
		scanf( A[i] ) , scanf( B[i] ) ,
		ins( A[i] , B[i] ) , ins( B[i] , A[i] ) ,
		degree[ A[i] ]++ , degree[ B[i] ]++ ;
	
}

inline void dfs( int x , int f ){
	
	Vis[x] = true ;
	
	Rep( i , Ht[x] , Nt[i] )if( f != i ){
		if( Vis[to[i]] )V[ Fa[x] ] = true ;
		else Fa[to[i]] = Fa[x] , dfs( to[i] , i ^ 1 ) ;
	}
	
}

inline void dfs( int x ){
	
	Rep( i , Ht[x] , Nt[i] )if( !used[i] ){
		used[i] = used[i ^ 1] = true ;
		ans[x] = to[i] ;
		dfs( to[i] ) ;
		return ;
	}
	
}

int main(){
	
	freopen("clo.in" , "r" , stdin) ;
	freopen("clo.out" , "w" , stdout) ;
	
	read_in() ;
	
	For( i , 1 , n )if( !Vis[i] )
		Fa[i] = i , dfs( i , 0 ) ;
	
	For( i , 1 , n )if( !V[Fa[i]] )
		return puts("NIE") , 0 ;
	
	puts("TAK") ;
	
	int head = 0 , tail = 0 ;
	
	For( i , 1 , n )
		if( degree[i] == 1 )que[ ++tail ] = i ;
	
	while( head != tail ){
		int x = que[ ++head ] ;
		Rep( i , Ht[x] , Nt[i] )if( !used[i] ){
			ans[x] = to[i] ;
			used[i] = used[i ^ 1] = true ;
			if( --degree[to[i]] == 1 )que[ ++tail ] = to[i] ;
		}
	}
	
	For( i , 1 , n ){
		if( !ans[i] )
			dfs( i ) ;
		printf("%d\n" , ans[i] ) ;
	}
	
	return 0 ;
}
