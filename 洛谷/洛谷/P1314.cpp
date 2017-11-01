#include<cstdio>

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
inline bool chkmax( type& x , const type& y ) {
	return x > y ? false : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x < y ? false : ( x = y , true ) ;
}
template < typename type >
inline void swap( type& x , type& y ) { type t = x ; x = y ; y = t ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 2e5 + 3 ;

int n ;
int m ;
LL S ;

int wi[maxn] ;
int vi[maxn] ;

int Li[maxn] ;
int Ri[maxn] ;

int sum1[maxn] ;
LL sum2[maxn] ;

inline LL chk( int x ) {
	FOR( i , 1 , n ) {
		sum1[i] = sum1[i - 1] + ( wi[i] >= x ) ;
		sum2[i] = sum2[i - 1] + ( wi[i] >= x ) * vi[i] ;
	}
	LL res = 0 ;
	FOR( i , 1 , m )
		res += ( sum2[Ri[i]] - sum2[Li[i] - 1] )
				* ( sum1[Ri[i]] - sum1[Li[i] - 1] ) ;
	return res ;
}

int main() {
	
	scanf( n ) ; scanf( m ) ; scanf( S ) ;
	
	FOR( i , 1 , n )scanf( wi[i] ) , scanf( vi[i] ) ;
	FOR( i , 1 , m )scanf( Li[i] ) , scanf( Ri[i] ) ;
	
	int l = 0 , r = 1e6 ;
	
	LL ans = 1e15 ;
	
	while( l <= r ) {
		int mid = l + r >> 1 ;
		LL chker = chk( mid ) ;
		if( chker == S )return puts( "0" ) , 0 ;
		if( chker < S )chkmin( ans , S - chker ) , r = mid - 1 ;
		else chkmin( ans , chker - S ) , l = mid + 1 ;
	}
	
	printf( "%lld\n" , ans ) ;
	
	return 0 ;
}
