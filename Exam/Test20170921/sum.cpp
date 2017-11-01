#include<cstdio>

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
static const int maxn = 3e6 + 10 ;

LL n ;
LL m ;
LL part ;
LL mod ;

inline LL qpow( LL x , LL y ) {
	register LL res = 1LL ;
	for( ; y ; y >>= 1 , x = x * x % mod )
		if( y & 1LL )res = res * x % mod ;
	return res ;
}

namespace AC {
	int cnt ;
	bool V[maxn] ;
	int pr[maxn] ;
	int pow[maxn] ;
	
	inline void main() {
		register int t ;
		register LL part = n / mod , extra_part = n % mod ;
		pow[1] = 1 ;
		For( i , 2 , mod - 1 ) {
			if( !V[i] )
				pr[ ++cnt ] = i , pow[i] = qpow( i , m ) ;
			for( int j = 1 ; j <= cnt && ( t = pr[j] * i ) < mod ; ++j ) {
				V[t] = true ;
				pow[t] = 1LL * pow[pr[j]] * pow[i] % mod ;
				if( !( i % pr[j] ) )break ;
			}
		}
		int ans = 0 ;
		++part ;
		For( i , 1 , extra_part )
			ans = ( ans + 1LL * pow[i] * part % mod ) % mod ;
		--part ;
		For( i , extra_part + 1 , min( mod - 1LL , n ) )
			ans = ( ans + 1LL * pow[i] * part % mod ) % mod ;
		printf("%d\n" , ans ) ;
	}
}

int main() {
	
	freopen( "sum.in" , "r" , stdin ) ;
	freopen( "sum.out" , "w" , stdout ) ;
	
	scanf( mod ) ; scanf( m ) ; scanf( n ) ;
	
	AC :: main() ;
	
	return 0 ;
}
