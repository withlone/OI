#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

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

typedef long long LL ;
static const int maxn = 5e6 + 10 ;

LL upto ;
int mpr ;
int cnt ;
LL ans ;

bool V[maxn] ;
int pr[maxn] ;
LL sqr[maxn] ;
bool Vi[maxn] ;

inline void init( int n ) {
	register LL t ;
	For( i , 2 , n ) {
		if( !V[i] )pr[ ++cnt ] = i , sqr[cnt] = 1LL * i * i ;
		for( int j = 1 ; j <= cnt && ( t = 1LL * pr[j] * i ) <= n ; ++j ) {
			V[t] = true ;
			if( !( i % pr[j] ) )break ;
		}
	}
}

inline void find( LL mul , int l , int r ) {
	int res ; ans += -l + 2 ;
	while( l <= r ) {
		int mid = l + r >> 1 ;
		if( mul * pr[mid] <= upto )res = mid , l = mid + 1 ;
		else r = mid - 1 ;
	}
	ans += res ;
}

void dfs( int x , LL mul ) {
	if( x == cnt + 1 || mul * pr[x] > upto )return ++ans , void() ;
	if( mul * sqr[x] > upto )
		return find( mul , x , cnt ) ;
	dfs( x + 1 , mul ) ;
	mul *= pr[x] ;
	for( ; mul <= upto ; mul *= sqr[x] ){
		dfs( x + 1 , mul ) ;
		if( mul * pr[x] > upto )return ;
	}
}

int main() {
	
	freopen( "aqnum.in" , "r" , stdin ) ;
	freopen( "aqnum.out" , "w" , stdout ) ;
	
	scanf( upto ) ; scanf( mpr ) ;
	
	init( mpr ) ;
	
	dfs( 1 , 1LL ) ;
	
	printf("%lld\n" , ans ) ;
	
	return 0 ;
}
