#include<cstdio>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template < typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e9 + 10 ;
static const int maxx = 1e6 + 10 ;

int cnt ;

bool V[maxx] ;
int pr[maxx] ;
int phi[maxx] ;

inline void init( int n ) {
	int t ; phi[1] = 1 ;
	For( i , 2 , n ) {
		if( !V[i] )pr[ ++cnt ] = i , phi[i] = i - 1 ;
		for( int j = 1 ; j <= cnt && ( t = pr[j] * i ) <= n ; ++j ) {
			V[t] = true ;
			phi[t] = ( pr[j] - 1 ) * phi[i] ;
			if( !( i % pr[j] ) ) {
				phi[t] = pr[j] * phi[i] ;
				break ;
			}
		}
	}
}

inline int get_phi( int x ) {
	if( x <= 1e6 )return phi[x] ;
	int res = x ;
	for( int i = 1 ; i <= cnt && pr[i] * pr[i] <= x ; ++i )
		if( !( x % pr[i] ) ) {
			while( !( x % pr[i] ) )x /= pr[i] ;
			res = res / pr[i] * ( pr[i] - 1 ) ;
		}
	if( x != 1 )res = res / x * ( x - 1 ) ;
	return res ;
}

int n ;
int k ;
int cases ;

inline int solve() {
	if( !k ){
		int ans = 0 ;
		for( ; n != 1 ; ++ans ) n = get_phi( n ) ;
		return ans ;
	}
	static int que[maxx] , steps[maxx] , times[maxx] ;
	int head = 0 , tail = 0 ;
	que[ ++tail ] = n ; times[tail] = k ;
	while( head != tail ) {
		int x = que[ ++head ] ;
		que[ ++tail ] = get_phi( x ) ;
		steps[tail] = steps[head] + 1 ;
		times[tail] = times[head] ;
		if( que[tail] == 1 )return steps[tail] ;
		if( times[head] ) {
			que[ ++tail ] = ( x >> 1 ) + 1 ;
			steps[tail] = steps[head] + 1 ;
			times[tail] = times[head] - 1 ;
			if( que[tail] == 1 )return steps[tail] ;
		}
	}
}

int main() {
	
	freopen( "func.in" , "r" , stdin ) ;
	freopen( "func.out" , "w" , stdout ) ;
	
	init( 1e6 ) ;
	
	scanf( cases ) ;
	
	while( cases-- ) {
		scanf( n ) ; scanf( k ) ;
		printf( "%d\n" , solve() ) ;
	}
	
	return 0 ;
}
