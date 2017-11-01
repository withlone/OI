#include<cstdio>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

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
static const int maxn = 1e7 + 10 ;
static const int mod = 1e8 + 9 ;

int cases ;
int n ;
int m ;
int cnt ;

bool V[maxn] ;
int pri[maxn] ;
int sum[maxn] ;

inline void init(){
	sum[1] = 1 ;
	For( i , 2 , 1e7 ){
		if( !V[i] )
			pri[ ++cnt ] = i ,
			sum[i] = ( 1LL * i * ( 1 - i ) % mod + mod ) % mod ;
		For( j , 1 , cnt ){
			int t = pri[j] * i ;
			if( t > 1e7 )break ;
			V[t] = true ;
			if( !( i % pri[j] ) ){
				sum[t] = ( 1LL * sum[i] * pri[j] % mod + mod ) % mod ;
				break ;
			}
			sum[t] = ( 1LL * sum[i] * sum[pri[j]] % mod + mod ) % mod ;
		}
	}
	For( i , 1 , 1e7 )sum[i] = ( sum[i] + sum[i - 1] ) % mod ;
}

inline int get( int x ){
	LL t1 = 1LL * ( n / x ) * ( 1 + n / x ) ;
	LL t2 = 1LL * ( m / x ) * ( 1 + m / x ) ;
	t1 >>= 1LL ; t2 >>= 1LL ;
	t1 %= mod ; t2 %= mod ;
	return t1 * t2 % mod ;
}

inline int work( int n , int m ){
	int res = 0 ;
	for( int i = 1 , nxt ; i <= n ; i = nxt + 1 ){
		nxt = min( n / ( n / i ) , m / ( m / i ) ) ;
		( res += 1LL * get( i ) * ( sum[nxt] - sum[i - 1] ) % mod ) %= mod ;
	}
	return res + mod ;
}

int main(){
	
	init() ;
	
	scanf( cases ) ;
	
	while( cases-- ){
		scanf( n ) ; scanf( m ) ;
		if( n > m )swap( n , m ) ;
		printf("%d\n" , work( n , m ) % mod ) ;
	}
	
	return 0 ;
}
