#include<cmath>
#include<cstdio>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

static const int len = 1 << 15 ;
char buffer[len] , *beginer , *ender ;

char Getchar(){
	if( beginer == ender )
		ender = ( beginer = buffer ) + fread( buffer , 1 , len , stdin ) ;
	return beginer == ender ? EOF : *beginer++ ;
}

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >
inline void swap( type& x , type& y ){ type t = x ; x = y ; y = t ; }
template< typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }
template< typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }

template< typename type >
inline type scanf( type& in ){
	in = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 4e6 + 10 ;
static const int mod = 998244353 ;
static const double eps = 1e-2 ;

LL n ;
LL m ;
int cnt ;

bool V[maxn] ;
int mu[maxn] ;
int pri[maxn] ;

inline void init( int n ){
	mu[1] = 1 ;
	register int t ;
	For( i , 2 , n ){
		if( !V[i] )pri[ ++cnt ] = i , mu[i] = -1 ;
		For( j , 1 , cnt ){
			if( ( t = pri[j] * i ) > n )break ;
			V[t] = true ;
			if( !( i % pri[j] ) )break ;
			mu[t] = -mu[i] ;
		}
	}
	For( i , 1 , n )mu[i] += mu[i - 1] ;
}

inline int work( LL n , LL m ){
	int res = 0 ;
	for( LL i = 1 , nxt ; i <= n ; i = nxt + 1 ){
		nxt = min( n / ( n / i ) , m / ( m / i ) ) ;
		LL t1 = ( ( ( n / i ) % mod ) * ( ( m / i ) % mod ) ) % mod ;
		if( t1 < 0 )throw ;
		LL t2 = mu[(LL)sqrt(nxt)] - mu[(LL)sqrt(i - 1)] ;
		res = ( res + t1 * t2 % mod ) % mod ;
	}	
	return res + mod ;
}

int main(){
	
	scanf( n ) ; scanf( m ) ;
	
	if( n > m )swap( n , m ) ;
	
	init( sqrt( n ) + 1 ) ;
	
	printf("%d\n" , work( n , m ) % mod ) ;
	
	return 0 ;
}
