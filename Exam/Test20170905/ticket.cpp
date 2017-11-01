#include<cstdio>
#include<cstring>
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

typedef long long LL ;
static const int maxn = 5e3 + 10 ;
static const int maxx = 1e4 + 10 ;

int m ;
int n ;

struct bint{
	
	static const int ten = 1e8 ;
	
	LL s[maxx] ;
	int len ;
	
	bint(){ memset( s , 0 , sizeof s ) ; len = 1 ; }
	
	bint operator = ( char *a ){
		len = 0 ; memset( s , 0 , sizeof s ) ;
		static char t[maxx] ; int l = strlen( a ) ;
		For( i , 0 , l - 1 )t[i] = a[l - i - 1] ;
		For( i , 0 , l - 1 )a[i] = t[i] ;
		For( i , 0 , l - 1 ){
			++len ;
			Lop( j , min( l - 1 , i + 7 ) , i )
				s[len] = s[len] * 10 + a[j] - '0' ;
			i += 7 ;
		}
		return *this ;
	}
	
	bint operator = ( LL a ){
		char x[50] ;
		sprintf( x , "%lld" , a ) ;
		*this = x ;
		return *this ;
	}
	
	bint( char *a ){ bint() ; *this = a ; }
	bint( LL a ){ bint() ; *this = a ; }
	
	bint operator + ( bint x ){
		bint y ;
		y.len = max( x.len , len ) + 1 ;
		For( i , 1 , y.len ){
			y.s[i] += s[i] + x.s[i] ;
			y.s[i + 1] += y.s[i] / ten ;
			y.s[i] %= ten ;
		}
		while( !y.s[y.len] && y.len > 1 )y.len-- ;
		return y ;
	}
	
	bint operator * ( bint x ){
		bint y ;
		y.len = x.len + len + 1 ;
		For( i , 1 , len )
			For( j , 1 , x.len ){
				y.s[i + j - 1] += s[i] * x.s[j] ;
				y.s[i + j] += y.s[i + j - 1] / ten ;
				y.s[i + j - 1] %= ten ;
			}
		while( !y.s[y.len] && y.len > 1 )y.len-- ;
		return y ;
	}
	
	bint operator / ( LL x ){
		bint y ;
		LL t = 0 ;
		y.len = len ;
		Lop( i , len , 1 ){
			y.s[i] = ( t * ten + s[i] ) / x ;
			t = ( t * ten + s[i] ) % x ;
		}
		while( !y.s[y.len] && y.len > 1 )y.len-- ;
		return y ;
	}
	
	void display(){
		int get = 0 , t = s[len] ;
		while( t > 0 )t /= 10 , ++get ;
		printf("%d\n" , get + 8 * ( len - 1 ) ) ;
		printf("%lld" , s[len] ) ;
		Lop( i , len - 1 , 1 )printf("%08lld" , s[i] ) ;
		putchar( 10 ) ;
	}
	
}ans ;

int main(){
	
	freopen("ticket.in" , "r" , stdin) ;
	freopen("ticket.out" , "w" , stdout) ;
	
	scanf( n ) ; scanf( m ) ;
	
	if( n < m )return printf("1\n0") , 0 ;
	
	ans = n + 1 - m ;
	
	For( i , n + 2 , n + m )ans = ans * i ;
	For( i , 2 , m )ans = ans / i ;
	
	ans.display() ;
	
	return 0 ;
}
