#include<cstdio>

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
	return ( x >= y ) ? ( false ) : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return ( x <= y ) ? ( false ) : ( x = y , true ) ;
}

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 37 ;
static const int maxm = 1e5 + 19 ;
static const int maxx = 3e6 + 17 ;

int n ;
int m ;
int mod ;

int ai[maxm] ;
int sum[maxm] ;
int cot[maxm] ;

class trie_tree {
	private :
		class node {
			public :
				bool key ;
				int tot ;
				int cotr ;
				node *son[2] ;
				node() { son[0] = son[1] = NULL ; }
		} *root ;
	
	public :
		trie_tree() { root = new node ; }
		
		inline void insert( const int& x ) {
			node *p = root ;
			FOR( i , 1 , n ) {
				bool t = x >> n - i & 1 ;
				if( !p -> son[t] )
					p -> son[t] = new node ,
					p -> son[t] -> key = t ,
					p -> son[t] -> tot =
					p -> son[t] -> cotr = 0 ;
				p = p -> son[t] ;
			}
		}
		
		void dfs( node *x , const int& dep ) {
			if( x -> son[0] && x -> son[1] ) {
				dfs( x -> son[0] , dep - 1 ) ;
				dfs( x -> son[1] , dep - 1 ) ;
				x -> cotr = max( x -> son[0] -> cotr , x -> son[1] -> cotr ) ;
				if( x -> son[0] -> cotr == x -> son[1] -> cotr )
					x -> cotr = x -> son[0] -> cotr ,
					x -> tot = x -> son[0] -> tot + x -> son[1] -> tot ;
				else if( x -> son[0] -> cotr > x -> son[1] -> cotr )
					x -> cotr = x -> son[0] -> cotr ,
					x -> tot = x -> son[0] -> tot ;
				else
					x -> cotr = x -> son[1] -> cotr ,
					x -> tot = x -> son[1] -> tot ;
			} else if( x -> son[0] ) {
				dfs( x -> son[0] , dep - 1 ) ;
				x -> cotr = x -> son[0] -> cotr | ( 1 << dep ) ;
				x -> tot = x -> son[0] -> tot ;
			} else if( x -> son[1] ) {
				dfs( x -> son[1] , dep - 1 ) ;
				x -> cotr = x -> son[1] -> cotr | ( 1 << dep ) ;
				x -> tot = x -> son[1] -> tot ;
			} else x -> tot = 1 ;
		}
		
		inline void work() { 
			dfs( root , n - 1 ) ;
			printf( "%d\n%d\n" , root -> cotr , root -> tot ) ;
		}
} trie ;

inline int change( const int& x ) {
	return ( ( x << 1 ) / ( mod + 1 ) + ( x << 1 ) ) & mod ;
}

int main() {
	
	freopen( "big.in" , "r" , stdin ) ;
	freopen( "big.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ;
	FOR( i , 1 , m ) sum[i] = sum[i - 1] ^ scanf( ai[i] ) ;
	
	mod = ( 1 << n ) - 1 ;
	FOR( i , 0 , m )
		cot[i] = change( sum[i] ) ^ sum[i] ^ sum[m] ,
		trie.insert( cot[i] ) ;
	
	trie.work() ;
	
	return 0 ;
}
