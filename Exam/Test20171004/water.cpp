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
inline void swap( type& x , type& y ) { type t = x ; x = y ; y = t ; }
template < typename type >
inline type max( const type& x , const type& y ) { return x > y ? x : y ; }
template < typename type >
inline type min( const type& x , const type& y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , const type& y ) {
	return x >= y ? false : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x <= y ? false : ( x = y , true ) ;
}

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 311 ;
static const int maxm = 1e5 + 19 ;

class node {
	public :
		int val ;
		int x ;
		int y ;
		
		node() { val = x = y = 0 ; }
		node( const int& a , const int& b , const int& c )
			{ val = a ; x = b ; y = c ; }
		
		bool operator < ( const node& t )
			const { return val < t.val ; }
} ;

template < typename type >
class heap {
	private :
		int size ;
		type T[maxm] ;
	public :
		heap() { size = 0 ; }
		
		inline void push( const type& x ) {
			T[ ++size ] = x ;
			int p = size ;
			while( p != 1 && T[p] < T[p >> 1] ) {
				swap( T[p] , T[p >> 1] ) ;
				p >>= 1 ;
			}
		}
		inline void pop() {
			T[1] = T[ size-- ] ;
			int p = 1 ;
			while( ( p << 1 ) <= size
				&& min( T[p << 1] , T[p << 1 | 1] ) < T[p] ) {
					int t = T[p << 1] < T[p << 1 | 1] ? p << 1 : p << 1 | 1 ;
					swap( T[p] , T[t] ) ;
					p = t ;
				}
		}
		inline type top() { return T[1] ; }
		inline bool empty() { return !size ; }
} ;

int n ;
int m ;

int mx[] = { 1 , -1 , 0 , 0 } ;
int my[] = { 0 , 0 , 1 , -1 } ;

int hi[maxn][maxn] ;
int water[maxn][maxn] ;

bool V[maxn][maxn] ;

heap < node > que ;

int main() {
	
	freopen( "water.in" , "r" , stdin ) ;
	freopen( "water.out" , "w" , stdout ) ;
	
	memset( V , true , sizeof V ) ;
	
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n ) FOR( j , 1 , m ) {
		hi[i][j] = scanf( water[i][j] ) ;
		if( i == 1 || j == 1 || i == n || j == m ) {
			chkmax( hi[i][j] , 0 ) ;
			que.push( node( hi[i][j] , i , j ) ) ;
		} else V[i][j] = false ;
	}
	
	while( !que.empty() ) {
		node nw = que.top() ; que.pop() ;
		FOR( i , 0 , 3 ) {
			int x = nw.x + mx[i] , y = nw.y + my[i] ;
			if( !V[x][y] ) {
				V[x][y] = true ;
				chkmax( hi[x][y] , hi[nw.x][nw.y] ) ;
				que.push( node( hi[x][y] , x , y ) ) ;
			}
		}
	}
	
	For( i , 1 , n ) {
		FOR( j , 1 , m )
			printf( "%d " , hi[i][j] - water[i][j] ) ;
		putchar( 10 ) ;
	}
	
	return 0 ;
}
