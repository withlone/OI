#include<cstdio>
#include<cstring>
#include<algorithm>

using std :: max ;
using std :: sort ;

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
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e3 + 13 ;
static const int ten = 1e4 ;

int n ;

class people {
	public :
		int a ;
		int b ;
		
		bool operator < ( const people& x )
			const { return a * b < x.a * x.b ; }
} pe[maxn] ;

class bint {
	public :
		int len ;
		int s[maxn] ;
		
		bint() { len = 1 ; memset( s , 0 , sizeof s ) ; }
		bint( const int& x ) {
			len = 1 ; memset( s , 0 , sizeof s ) ;
			if( x == 1e4 )s[2] = 1 ;
			else s[1] = x ;
		}
		
		bool operator < ( const bint& x ) const {
			if( len != x.len )return len < x.len ;
			LOP( i , len , 1 )
				if( s[i] != x.s[i] )return s[i] < x.s[i] ;
			return false ;
		}
		
} ans , mul ;

bint operator * ( const bint& x , const bint& y ) {
	bint res ;
	res.len = x.len + y.len + 1 ;
	For( i , 1 , x.len ) FOR( j , 1 , y.len ) {
		res.s[i + j - 1] += x.s[i] * y.s[j] ;
		res.s[i + j] += res.s[i + j - 1] / ten ;
		res.s[i + j - 1] %= ten ;
	}
	while( !res.s[ res.len ] && res.len > 1 )res.len-- ;
	return res ;
}

bint operator / ( const bint& x , const int y ) {
	bint res ;
	res.len = x.len ; memcpy( res.s , x.s , sizeof res.s ) ;
	LOP( i , res.len , 1 ) {
		res.s[i - 1] += ten * ( res.s[i] % y ) ;
		res.s[i] /= y ;
	}
	res.s[0] = 0 ;
	while( !res.s[ res.len ] && res.len > 1 )res.len-- ;
	return res ;
}

inline void display( const bint& x ) {
	printf( "%d" , x.s[x.len] ) ;
	LOP( i , x.len - 1 , 1 )printf( "%04d" , x.s[i] ) ;
	putchar( 10 ) ;
}

int main() {
	
	freopen( "game.in" , "r" , stdin ) ;
	freopen( "game.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	FOR( i , 0 , n )scanf( pe[i].a ) , scanf( pe[i].b ) ;
	
	sort( 1 + pe , 1 + n + pe ) ;
	
	mul = pe[0].a ;
	
	FOR( i , 1 , n ) {
		ans = max( ans , mul / pe[i].b ) ;
		mul = mul * pe[i].a ;
	}
	
	display( ans ) ;
	
	return 0 ;
}
