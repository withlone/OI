#include<cstdio>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

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

static const int maxn = 233 ;

int d ;
int n ;

int pub[maxn][maxn] ;

inline int get( int x1 , int y1 , int x2 , int y2 ) {
return pub[x2][y2] - pub[x1 - 1][y2] - pub[x2][y1 - 1] + pub[x1 - 1][y1 - 1] ;
}

int main() {
	
	register int x , y , z ;
	
	scanf( d ) ; scanf( n ) ;
	
	For( i , 1 , n ) {
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		pub[x + 20][y + 20] += z ;
	}
	
	For( i , 10 , 200 ) For( j , 10 , 200 )
		pub[i][j] += pub[i - 1][j] + pub[i][j - 1] - pub[i - 1][j - 1] ;
	
	int ans = 0 , tot = 0 ;
	For( i , 20 - d , 148 - d ) For( j , 20 - d , 148 - d ) {
		 int t = get( i , j , i + 2 * d , j + 2 * d ) ;
		 if( t > ans )
		 	ans = t , tot = 1 ;
		 else if( t == ans )
		 	++tot ;
	}
	printf( "%d %d\n" , tot , ans ) ;
	
	return 0 ;
}
