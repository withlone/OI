#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )
#define FOR( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define LOP( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define REP( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type max( const type& x , const type& y ) { return x > y ? x : y ; }
template < typename type >
inline type min( const type& x , const type& y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , const type& y ) {
	return x > y ? false : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x < y ? false : ( x = y , true ) ;
}
template < typename type >
inline void swap( type& x , type& y ) { type t = x ; x = y ; y = t ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 5e5 + 29 ;
static const int maxm = 1e6 + 33 ;

int n ;
int s ;
int S ;
int T ;

int pre[maxn] ;
LL dis[maxn] ;

bool V[maxn] ;

LL f[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;
int Dt[maxm] ;

inline void ins( const int& x , const int& y , const int& z ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
}

inline int bfs( const int& S ) {
	static int que[maxn] ;
	int head = 0 , tail = 0 , res = 0 ;
	memset( pre , 0 , sizeof(int) * (n + 1) ) ;
	memset( dis , -1 ,  sizeof(LL) * (n + 1) ) ;
	que[ ++tail ] = S ; dis[S] = 0 ;
	while( head != tail ) {
		int x = que[ ++head ] ;
		REP( i , Ht[x] , Nt[i] )
			if( dis[to[i]] == -1 ) {
				pre[to[i]] = x ;
				dis[to[i]] = dis[x] + Dt[i] ;
				que[ ++tail ] = to[i] ;
				if( dis[res] < dis[to[i]] )
					res = to[i] ;
			}
	}
	return res ;
}

void dfs( int x ) {
	V[x] = true ;
	REP( i , Ht[x] , Nt[i] ) if( !V[to[i]] ) {
		dfs( to[i] ) ;
		chkmax( f[x] , f[to[i]] + Dt[i] ) ;
	}
}

int main() {
	
	scanf( n ) ; scanf( s ) ;
	FOR( i , 1 , n - 1 ) {
		register int x , y , z ;
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		ins( x , y , z ) ; ins( y , x , z ) ;
	}
	
	S = bfs( 1 ) ;
	T = bfs( S ) ;
	
	REP( i , T , pre[i] )V[i] = true ;
	REP( i , T , pre[i] )dfs( i ) ;
	
	LL ans = 1e18 ;
	
	static int que[maxn] ;
	int head = 0 , tail = 0 ;
	que[ ++tail ] = T ;
	
	for( int l = T , r = T ; pre[r] ; l = pre[l] ) {
		while( pre[r] && dis[l] - dis[pre[r]] <= s ) {
			r = pre[r] ;
			while( head < tail && f[ que[tail] ] <= f[r] )
				--tail ;
			que[ ++tail ] = r ;
		}
		chkmin( ans ,
		max( f[ que[ ++head ] ] ,
		max( dis[T] - dis[l] , dis[r] ) ) ) ;
	}
	
	printf( "%lld\n" , ans ) ;
	
	return 0 ;
}
