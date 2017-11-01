#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e4 + 10 ;
static const int maxm = 2e6 + 10 ;

template < typename type > 
class heap {
	private :
		int size ;
		type T[maxm * 5] ;
	public :
		heap(){ size = 0 ; }
		void push( type x ) {
			T[ ++size ] = x ;
			int p = size ;
			while( p != 1 && T[p] > T[p >> 1] ) {
				swap( T[p] , T[p >> 1] ) ;
				p >>= 1 ;
			}
		}
		void pop() {
			T[1] = T[ size-- ] ;
			int p = 1 ;
			while( ( p << 1 ) <= size
			&& max( T[p << 1] , T[p << 1 | 1] ) > T[p] ){
				int t = T[p << 1] > T[p << 1 | 1] ? p << 1 : p << 1 | 1 ;
				swap( T[p] , T[t] ) ;
				p = t ;
			}
		}
		bool empty(){ return !size ; }
		type top(){ return T[1] ; }
};

int n ;
int m ;

bool V[maxn] ;
int qt[maxn] ;
int col[maxn] ;
int Vis[maxn] ;
int label[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins( int x , int y ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

inline void MCS() {
	static heap < pair < int , int > > que ;
	For( i , 1 , n )
		que.push( make_pair( 0 , i ) ) ;
	register int x ;
	Lop( j , n , 1 ) {
		while( V[ que.top().second ] )que.pop() ;
		qt[j] = x = que.top().second ; que.pop() ;
		V[x] = true ;
		Rep( i , Ht[x] , Nt[i] )
			if( !V[to[i]] )
				que.push( make_pair( ++label[to[i]] , to[i] ) ) ;
	}
}

inline int color() {
	register int res = 0 ;
	Lop( j , n , 1 ){
		Rep( i , Ht[qt[j]] , Nt[i] )
			Vis[ col[to[i]] ] = j ;
		for( col[qt[j]] = 1 ; Vis[ col[qt[j]] ] == j ; ++col[qt[j]] ) ;
		chkmax( res , col[qt[j]] ) ;
	}
	return res ;
}

int main() {
	
	scanf( n ) ; scanf( m ) ;
	
	register int x , y ;
	
	while( m-- ) {
		scanf( x ) ; scanf( y ) ;
		ins( x , y ) ; ins( y , x ) ;
	}
	
	MCS() ;
	
	printf("%d\n" , color() ) ;
	
	return 0 ;
}
