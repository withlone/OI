#include<cstdio>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; i-- )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline void scanf( type &in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch > '9'||ch < '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch >='0'&&ch <='9';ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

static const int maxn = 5e4 + 10 ;
static const int maxm = 4e6 + 10 ;

int n ;
int m ;
int q ;

int sum[maxm] ;

bool cmp( int x , int y ){ return x * y ; }

int main(){
	
	freopen("prz.in" , "r" , stdin) ;
	freopen("prz.out" , "w" , stdout) ;
	
	scanf( n ) ;
	
	q = ~0U >> 1 ;
	
	For( i , 1 , n ){
		int x , y ;
		scanf( x ) ; scanf( y ) ;
		sum[x << 1]++ ; sum[y << 1 | 1]-- ;
		m = max( m , y << 1 | 1 ) ;
		q = min( q , x << 1 ) ;
	}
	
	For( i , 1 , m )
		sum[i] += sum[i - 1] ;
	
	int l = q >> 1 , r = 0 ;
	For( i , q , m )
		if( !sum[i] ){
			r = i >> 1 ;
			printf("%d %d\n" , l , r ) ;
			while( !sum[i] && i <= m )++i ;
			l = i >> 1 ;
		}
	
	return 0 ;
}
