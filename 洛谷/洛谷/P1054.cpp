#include<cstdio>
#include<cstring>

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
	return x >= y ? false : ( x = y , true ) ;
}
template < typename tp >
inline bool chkmin( tp& x , const tp& y ) {
	return x <= y ? false : ( x = y , true ) ;
}

template < typename tp >
inline tp scanf( tp& in ) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 111 ;
static const int mod = 998244353 ;

template < typename type >
class stack {
	private :
		type T[maxn] ;
		int tp ;
	public :
		stack() { tp = 0 ; }
		inline void push( type x ) { T[ ++tp ] = x ; }
		inline void pop() { --tp ; }
		inline bool empty() { return !tp ; }
		inline type top() { return T[tp] ; }
} ;

int n ;

int pri[331] ;

bool V[maxn] ;

int prime[] = { 0 , 1 , 2 , 3 , 5 , 7 , 11 , 13 , 17 , 19 , 23 } ;

char opt[maxn][maxn] ;

inline bool number( char x ) {
	return x >= '0' && x <= '9' ;
}

inline bool opter( char x ) {
	return x == '(' || x == ')' || x == '+' || x == '-'
			|| x == '*' || x == '^' ;
}

inline int get( char *x , int& i ) {
	int res = 0 ;
	for( ; number( x[i] ) ; ++i ) res = res * 10 + x[i] - '0' ;
	--i ;
	return res ;
}

inline int plus( int x , int y ) {
	x += y ; if( x >= mod ) x -= mod ; return x ;
}

inline int minus( int x , int y ) {
	x -= y ; if( x < 0 ) x += mod ; return x ;
}

inline int mul( int x , int y ) {
	return 1LL * x * y % mod ;
}

inline int qpow( int x , int y ) {
	int res = 1 ;
	for( ; y ; y >>= 1 , x = mul( x , x ) )
		if( y & 1 ) res = mul( res , x ) ;
	return res ;
}

inline int calc( int x , int y , char op ) {
	if( op == '+' ) return plus( x , y ) ;
	if( op == '-' ) return minus( x , y ) ;
	if( op == '*' ) return mul( x , y ) ;
	if( op == '^' ) return qpow( x , y ) ;
}

inline void calc( stack < char > &op , stack < int > &nm ) {
	int y = nm.top() ; nm.pop() ; int x = nm.top() ; nm.pop() ;
	int res = calc( x , y , op.top() ) ;
	nm.push( res ) ; op.pop() ;
}

inline int calc( char *ai , int x ) {
	static stack < char > op ;
	static stack < int >  nm ;
	op = stack < char > () ;
	nm = stack < int >  () ;
	For( i , 0 , strlen( ai ) - 1 ) {
		if( number( ai[i] ) )
			nm.push( get( ai , i ) ) ;
		else if( ai[i] == 'a' ) nm.push( x ) ;
		else if( opter( ai[i] ) ) {
			if( ai[i] == '(' ) op.push( '(' ) ;
			else if( ai[i] == ')' ) {
				while( !op.empty() && op.top() != '(' )
					calc( op , nm ) ;
				if( !op.empty() && op.top() == '(' ) op.pop() ;
			} else {
				if( op.empty() || pri[ ai[i] ] > pri[ op.top() ] )
					op.push( ai[i] ) ;
				else {
					while( !op.empty() && op.top() != '(' && op.top() != ')'
					 && pri[ ai[i] ] <= pri[ op.top() ] ) 
						calc( op , nm ) ;
					op.push( ai[i] ) ;
				}
			}
		}
	}
	while( !op.empty() )
		if( op.top() != '(' )
			calc( op , nm ) ;
		else op.pop() ;
	int res = nm.top() ;
	while( res < 0 ) res += mod ;
	return res ;
}

inline void fgets( char *x ) {
	char ch = getchar() ;
	while( ch == 10 ) ch = getchar() ;
	for( register int i = 0 ; ch != 10 ; ++i , ch = getchar() )
		x[i] = ch ;
}

int main() {
	
	pri[ '+' ] = pri[ '-' ] = 1 ;
	pri[ '*' ] = 2 ; pri[ '^' ] = 3 ;
	
	fgets( opt[0] ) ;
	scanf( n ) ;
	FOR( i , 1 , n ) fgets( opt[i] ) ;
	
	memset( V , true , sizeof V ) ;
	
	For( i , 0 , 10 ) {
		int x = prime[i] ;
		int std = calc( opt[0] , x ) ;
		FOR( j , 1 , n ) if( V[j] && std != calc( opt[j] , x ) ) V[j] = false ;
	}
	
	FOR( i , 1 , n ) if( V[i] ) printf( "%c" , i + 'A' - 1 ) ;
	
	putchar( 10 ) ;
	
	return 0 ;
}
