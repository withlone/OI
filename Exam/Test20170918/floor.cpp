#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;

LL n ;
int mod ;

class matrix {
	public :
		int n ;
		int m ;
		int s[4][4] ;
		matrix(){ memset( s , 0 , sizeof s ) ; n = m = 0 ; }
		
		matrix operator * ( const matrix& x ) {
			matrix y ;
			y.n = n ; y.m = x.m ;
			For( i , 0 , y.n )For( j , 0 , y.m )For( k , 0 , m )
				( y.s[i][j] += 1LL * s[i][k] * x.s[k][j] % mod ) %= mod ;
			return y ;
		}
};

matrix base ;
matrix ans ;

int main() {
	
	freopen( "floor.in" , "r" , stdin ) ;
	freopen( "floor.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( mod ) ;
	
	ans.n = 0 ; ans.m = 3 ;
	ans.s[0][0] = 1 % mod ; ans.s[0][1] = 2 % mod ;
	ans.s[0][2] = 1 ; ans.s[0][3] = 1 ;
	
	base.n = base.m = 3 ;
	base.s[0][1] = base.s[1][0] = base.s[1][1] = base.s[2][1] =
	base.s[3][2] = base.s[3][3] = 1 ;
	base.s[2][2] = -1 ;
	
	for( --n ; n > 0 ; n >>= 1 , base = base * base )
		if( n & 1 )ans = ans * base ;
	
	printf("%d\n" , ans.s[0][0] ) ;
	
	return 0 ;
}
