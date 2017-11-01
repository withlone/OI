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

static const int maxn = 400 + 10 ;

int n ;
int na ;
int nb ;

int score_a ;
int score_b ;

int little_a[maxn] ;
int little_b[maxn] ;

int winner[5][5] ;

int main() {
	
	freopen( "rps.in" , "r" , stdin ) ;
	freopen( "rps.out" , "w" , stdout ) ;
	
	winner[0][1] = -1 ;
	winner[0][2] = 1 ;
	winner[0][3] = 1 ;
	winner[0][4] = -1 ;
	winner[1][2] = -1 ;
	winner[1][3] = 1 ;
	winner[1][4] = -1 ;
	winner[2][3] = -1 ;
	winner[2][4] = 1 ;
	winner[3][4] = 1 ;
	
	For( i , 0 , 4 ) For( j , 0 , i - 1 )
		winner[i][j] = -winner[j][i] ;
	
	For( i , 0 , 4 ) For( j , 0 , 4 )
		if( winner[i][j] < 0 )winner[i][j] = 0 ;
	
	scanf( n ) ; scanf( na ) ; scanf( nb ) ;
	For( i , 1 , na )scanf( little_a[i] ) ;
	For( i , 1 , nb )scanf( little_b[i] ) ;
	for( int i = na << 1 ; i - na < n ; i += na )
		For( j , i - na + 1 , i )
			little_a[j] = little_a[j - na] ;
	for( int i = nb << 1 ; i - nb < n ; i += nb )
		For( j , i - nb + 1 , i )
			little_b[j] = little_b[j - nb] ;
	
	For( i , 1 , n ) {
		score_a += winner[little_a[i]][little_b[i]] ;
		score_b += winner[little_b[i]][little_a[i]] ;
	}
	
	printf( "%d %d\n" , score_a , score_b ) ;
	
	return 0 ;
}
