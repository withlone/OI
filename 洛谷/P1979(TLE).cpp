#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template < typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }
template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }
template < typename type >
inline type abs( type x ){ return x > 0 ? x : -x ; }
template < typename type >
inline void swap( type& x , type& y ){ type t = x ; x = y ; y = t ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

template < typename type >
class heap {
	private :
		static const int heap_size = 1e6 + 10 ;
		int size ;
		type T[heap_size] ;
	public :
		heap(){ size = 0 ; }
		inline void push( const type& x ) {
			int p = ++size ;
			T[p] = x ;
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
		inline void clear() { size = 0 ; }
		inline bool empty() { return !size ; }
} ;

static const int maxn = 31 ;

int n ;
int m ;
int q ;
int ex ;
int ey ;
int sx ;
int sy ;
int tx ;
int ty ;
int ans ;

bool bd[maxn][maxn] ;
bool V[maxn][maxn][maxn][maxn] ;

int mx[] = { 0 , 0 , 1 , -1 } ;
int my[] = { 1 , -1 , 0 , 0 } ;

class node {
	public :
		int sx ;
		int sy ;
		int ex ;
		int ey ;
		int dis ;
		
		node(){ sx = sy = ex = ey = dis = 0 ; }
		node( int a , int b , int c , int d , int e )
			{ sx = a ; sy = b ; ex = c ; ey = d ; dis = e ; }
		bool operator < ( const node& x ) const {
			int t1 = abs( this -> sx - tx ) + abs( this -> sy - ty ) ;
			int t2 = abs( x.sx - tx ) + abs( x.sy - ty ) ;
			return dis + t1 < x.dis + t2 ;
		}
};

inline int bfs() {
	static heap < node > que ; que.clear() ;
	que.push( node( sx , sy , ex , ey , 0 ) ) ;
	if( sx == tx && sy == ty )return 0 ;
	V[sx][sy][ex][ey] = true ;
	while( !que.empty() ) {
		node t = que.top() , nxt = t ; que.pop() ; nxt.dis++ ;
		For( i , 0 , 3 ) {
			nxt.ex = t.ex + mx[i] ; nxt.ey = t.ey + my[i] ;
			nxt.sx = t.sx ; nxt.sy = t.sy ;
			if( nxt.ex == nxt.sx && nxt.ey == nxt.sy )
				nxt.sx = t.ex , nxt.sy = t.ey ;
			if( nxt.sx == tx && nxt.sy == ty )return nxt.dis ;
			if( !V[nxt.sx][nxt.sy][nxt.ex][nxt.ey] && bd[nxt.ex][nxt.ey] )
				V[nxt.sx][nxt.sy][nxt.ex][nxt.ey] = true , que.push( nxt ) ;
		}
	}
	return -1 ;
}

int main() {
	
	scanf( n ) ; scanf( m ) ; scanf( q ) ;
	For( i , 1 , n ) For( j , 1 , m )
		scanf( bd[i][j] ) ;
	
	while( q-- ) {
		scanf( ex ) ; scanf( ey ) ;
		scanf( sx ) ; scanf( sy ) ;
		scanf( tx ) ; scanf( ty ) ;
		if( !bd[ex][ey] || !bd[sx][sy] || !bd[tx][ty] )
			{ puts( "-1" ) ; continue ; }
		memset( V , 0 , sizeof V ) ;
		printf( "%d\n" , bfs() ) ;
	}
	
	return 0 ;
}
