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
inline bool chkmax( type& x , const type& y )
	{ return x > y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , const type& y )
	{ return x < y ? false : x = y , true ; }
template < typename type >
inline void swap( type& x , type& y ) { type t = x ; x = y ; y = t ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 75017 ;
static const int maxm = 200003 ;

class heap {
	private :
		int T[maxm] ;
		int mark[maxn] ;
		int size ;
	public :
		heap(){ size = 0 ; memset( mark , 0 , sizeof mark ) ; }
		inline void insert( int x ) {
			if( mark[x] )return mark[x]-- , void() ;
			T[ ++size ] = x ;
			int p = size ;
			while( p != 1 && T[p] > T[p >> 1] ) {
				swap( T[p] , T[p >> 1] ) ;
				p >>= 1 ;
			}
		}
		inline void pop() {
			T[1] = T[ size-- ] ;
			int p = 1 ;
			while( ( p << 1 ) <= size
				&& max( T[p << 1] , T[p << 1 | 1] ) > T[p] ) {
					int t = T[p << 1] > T[p << 1 | 1] ? p << 1 : p << 1 | 1 ;
					swap( T[p] , T[t] ) ;
					p = t ;
				}
		}
		inline void del( int x ) {
			if( T[1] == x )return pop() ;
			mark[x]++ ;
		}
		inline int top() {
			while( size && mark[T[1]] )mark[T[1]]-- , pop() ;
			return T[1] ;
		}
		inline bool empty() { return !size ; }
} ;

int n ;
int m ;

int f[maxn] ;
int g[maxn] ;

int idg[maxn] ;
int que[maxn] ;

int Ct ;
int ht[maxn] ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins( int x , int y ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; ++idg[y] ;
	Nt[ ++Ct ] = ht[y] ; ht[y] = Ct ; to[Ct] = x ;
}

inline void tuopo() {
	int head = 0 , tail = 0 ;
	FOR( i , 1 , n )if( !idg[i] )que[ ++tail ] = i ;
	while( head != tail ) {
		int x = que[ ++head ] ;
		REP( i , Ht[x] , Nt[i] )
			if( !--idg[to[i]] )que[ ++tail ] = to[i] ;
	}
}

int main() {
	
	freopen( "chronosphere.in" , "r" , stdin ) ;
	freopen( "chronosphere.out" , "w" , stdout ) ;
	
	register int x , y ;
	
	scanf( n ) ; scanf( m ) ;
	
	FOR( i , 1 , m ) {
		scanf( x ) ; scanf( y ) ;
		ins( x , y ) ;
	}
	
	tuopo() ;
	
	FOR( I , 1 , n ) {
		x = que[I] ;
		REP( i , ht[x] , Nt[i] )
			chkmax( f[x] , f[to[i]] + 1 ) ;
	}
	
	Lop( I , n , 1 ) {
		x = que[I] ;
		REP( i , Ht[x] , Nt[i] )
			chkmax( g[x] , g[to[i]] + 1 ) ;
	}
	
	static heap Hp ;
	
	FOR( i , 1 , n )Hp.insert( g[i] ) ;
	int ans = ~0U >> 1 , answer = n ;
	
	For( I , 1 , n ) {
		x = que[I] ;
		Hp.del( g[x] ) ;
		REP( i , ht[x] , Nt[i] )
			Hp.del( f[to[i]] + g[x] + 1 ) ;
		if( Hp.top() < ans )
			ans = Hp.top() , answer = x ;
		else if( Hp.top() == ans )
			chkmin( answer , x ) ;
		Hp.insert( f[x] ) ;
		REP( i , Ht[x] , Nt[i] )
			Hp.insert( f[x] + g[to[i]] + 1 ) ;
	}
	
	printf( "%d %d\n" , answer , ans ) ;
	
	return 0 ;
}
