#include<bitset>
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std ;

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

template < typename tp >
inline tp max( const tp& x , const tp& y ) { return x > y ? x : y ; }
template < typename tp >
inline tp min( const tp& x , const tp& y ) { return x < y ? x : y ; }
template < typename tp >
inline bool chkmax( tp& x , const tp& y ) {
	return ( x >= y ) ? false : ( x = y , true ) ;
}
template < typename tp >
inline bool chkmin( tp& x , const tp& y ) {
	return ( x <= y ) ? false : ( x = y , true ) ;
}

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 211 ;
static const int maxm = ( 1 << 11 ) + 11 ;

int n ;
int m ;

class stringer {
	public :
		int ans ;
		bool overflow[2] ;
		string pre ;
		string suf ;
		bitset < maxm > V ;
		stringer() { overflow[0] = overflow[1] = false ; }
} si[maxn] ;

inline void modify( string x , bitset < maxm >& V ) {
	int len = x.size() ;
	For( i , 0 , len - 1 ) For( j , i , len - 1 ) {
		int t = 0 ;
		for( register int k = 1 ; k <= 10 && j + k <= len ; ++k ) {
			t = ( t << 1 ) + x[i + k - 1] - '0' ;
			V.set( t | ( 1 << k ) ) ;
		}
	}
}

stringer merge( stringer x , stringer y ) {
	stringer res ;
	res.V = x.V | y.V ;
	if( !x.overflow[0] ) {
		res.pre = x.pre + y.pre ;
		if( res.pre.size() > 10 )
			res.overflow[0] = true ,
			res.pre = res.pre.substr( 0 , 10 ) ;
	} else res.pre = x.pre , res.overflow[0] = true ;
	if( !y.overflow[1] ) {
		res.suf = x.suf + y.suf ;
		if( res.suf.size() > 10 )
			res.overflow[1] = true ,
			res.suf = res.suf.substr( res.suf.size() - 10 , 10 ) ;
	} else res.suf = y.suf , res.overflow[1] = true ;
	string ai = x.suf + y.pre ;
	modify( ai , res.V ) ;
	for( res.ans = 0 ; ; ++res.ans ) {
		int t = 1 << res.ans , i ;
		for( i = 0 ; i < t ; ++i ) if( !res.V.test( t | i ) ) break ;
		if( !res.V.test( t | i ) ) break ;
	}
	--res.ans ;
	return res ;
}

int main() {
	
	scanf( n ) ;
	FOR( i , 1 , n ) {
		cin >> si[i].pre ;
		si[i].suf = si[i].pre ;
		si[i].V.set( 1 ) ;
		modify( si[i].pre , si[i].V ) ;
	}
	
	scanf( m ) ;
	FOR( i , 1 + n , m + n ) {
		int a , b ;
		scanf( a ) ; scanf( b ) ;
		si[i] = merge( si[a] , si[b] ) ;
		printf( "%d\n" , si[i].ans ) ;
	}
	
	return 0 ;
}
