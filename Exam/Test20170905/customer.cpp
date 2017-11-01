#include<cstdio>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; i-- )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template< typename type >
inline void scanf( type &in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch > '9'||ch < '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch >='0'&&ch <='9';ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

static const int maxn = 1e3 + 10 ;

int n ;

int F[maxn] ;

class customer{
	
	public :
		int x ;
		int y ;
		bool operator < ( const customer& t )
			const { return x == t.x ? y < t.y : x < t.x ; }
	
}cus[maxn] ;

int main(){
	
	freopen("customer.in" , "r" , stdin) ;
	freopen("customer.out" , "w" , stdout) ;
	
	scanf( n ) ;
	
	For( i , 1 , n )
		scanf( cus[i].x ) , scanf( cus[i].y ) , F[i] = 1 ;
	
	sort( 1 + cus , 1 + n + cus ) ;
	
	For( i , 1 , n )
		For( j , 1 , i - 1 )
			if( cus[i].x >= cus[j].y )F[i] = max( F[i] , F[j] + 1 ) ;
	
	int ans = 0 ;
	For( i , 1 , n )ans = max( ans , F[i] ) ;
	
	printf("%d\n" , ans ) ;
	
	return 0 ;
}
