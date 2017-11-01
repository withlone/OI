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
inline type scanf( type& in ) {
    in = 0 ; char ch = getchar() ; type f = 1 ;
    for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
    for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
    return in *= f ;
}

static const int maxn = 1e4 + 10 ;
static const int maxm = 2e5 + 10 ;

int n ;
int m ;
int S ;
int T ;

int dis[maxn] ;
bool V[maxn] ;
bool Vis[maxn] ;

int A[maxm] ;
int B[maxm] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

inline void ins( int x , int y ) {
    Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

inline void get() {
    static int que[maxm] ;
    int head = 0 , tail = 0 ;
    que[ ++tail ] = T ;
    while( head != tail ) {
        int x = que[ ++head ] ; V[x] = true ;
        Rep( i , Ht[x] , Nt[i] )
            if( !V[to[i]] )
                que[ ++tail ] = to[i] ;
    }
}

inline bool chk( int x ) {
    Rep( i , Ht[x] , Nt[i] )
        if( !V[to[i]] )return false ;
    return true ;
}

inline void rebuild() {
    Ct = 0 ; memset( Ht , 0 , sizeof Ht ) ;
    For( i , 1 , m )
        ins( A[i] , B[i] ) ;
    For( i , 1 , n )
        Vis[i] = chk( i ) ;
    memcpy( V , Vis , sizeof V ) ;
}

inline int bfs() {
    static int que[maxm * 10] ;
    int head = 0 , tail = 0 ;
    que[ ++tail ] = S ; dis[S] = 1 ;
    while( head != tail ) {
        int x = que[ ++head ] ; V[x] = false ;
        Rep( i , Ht[x] , Nt[i] ) if( V[to[i]] && !dis[to[i]]) {
            dis[to[i]] = dis[x] + 1 ;
            if( to[i] == T )return dis[to[i]] - 1 ;
            que[ ++tail ] = to[i] ;
        }
    }
    return -1 ;
}

int main() {
    
    freopen( "road.in" , "r" , stdin ) ;
    freopen( "road.out" , "w" , stdout ) ;
    
    register int x , y ;
    
    scanf( n ) ; scanf( m ) ;
    
    for( int i = 1 ; i <= m ; ++i ) {
        A[i] = scanf( x ) ; B[i] = scanf( y ) ;
        if( x == y ){ --i , --m ; continue ; }
        ins( y , x ) ;
    }
    
    scanf( S ) ; scanf( T ) ;
    
    if( S == T )return puts( "0" ) , 0 ;
    
    get() ;
    
    rebuild() ;
    
    printf( "%d\n" , bfs() ) ;
    
    return 0 ;
}
