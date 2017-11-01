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

static const int maxn = 1500 + 10 ;

int n ;

int f[maxn] ;
int g[maxn] ;
int seq[maxn] ;

int main() {
	
	freopen( "sequence.in" , "r" , stdin ) ;
	freopen( "sequence.out" , "w" , stdout ) ;
	
	For( i , 1 , scanf( n ) )
		seq[i] = scanf( seq[i] ) + seq[i - 1] ;
	
	memset( f , 0x3f , sizeof f ) ;
	memset( g , 0x3f , sizeof g ) ;
	
	f[0] = g[0] = 0 ;
	For( i , 1 , n ) For( j , 0 , i - 1 )
		if( seq[i] - seq[j] >= g[j] ) {
			if( f[j] + i - j - 1 < f[i]
			|| f[j] + i - j - 1 == f[i] && g[i] > seq[i] - seq[j] )
				g[i] = seq[i] - seq[j] , f[i] = f[j] + i - j - 1 ;
		}
	
	printf("%d\n" , f[n] ) ;
	
	return 0 ;
}
