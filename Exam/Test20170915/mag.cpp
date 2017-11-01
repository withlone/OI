#include<cstdio>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )

template< typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int maxn = 10 ;
static const int maxm = 100 ;

int cases ;
int n ;
int N ;
int m ;
int k ;
int cnt ;
int ans ;
LL full ;

LL mat[maxm] ;
LL bin[maxm] ;
LL map[maxn][maxn] ;

int get( int x , int y , int w ){
	++x ; ++y ;
	if( !w )return ( n << 1 | 1 ) * ( x - 1 ) + y ;
	return n + ( n << 1 | 1 ) * ( x - 1 ) + y ;
}

bool chk( LL tus , int steps ){
	LL t = tus , first = 0 ; int H = 0 ;
	For( i , 1 , cnt )
		if( ( t & mat[i] ) == mat[i] ){
			++H ;
			t ^= mat[i] ;
			if( !first )
				first = mat[i] ;
		}
	if( !H )return true ;
	if( H + steps > ans )return false ;
	For( i , 1 , N )
		if( ( first & bin[i - 1] ) && chk( tus ^ bin[i - 1] , steps + 1 ) )
			return true ;
	return false ;
}

int main() {
	
	freopen( "mag.in" , "r" , stdin ) ;
	freopen( "mag.out" , "w" , stdout ) ;
	
	bin[0] = 1LL ;
	For( i , 1 , 60 )bin[i] = bin[i - 1] << 1 ;
	
	scanf( cases ) ;
	
	while( cases-- ){
		cnt = 0 ;
		scanf( n ) ; scanf( k ) ;
		N = n * ( n + 1 ) << 1 ;
		full = ( 1LL << N ) - 1LL ;
		For( i , 0 , n - 1 )For( j , 0 , n - 1 ){
			map[i][j] = bin[get( i , j , 0 ) - 1] | bin[get( i , j , 1 ) - 1]
			| bin[get( i + 1 , j , 0 ) - 1] | bin[get( i , j + 1 , 1 ) - 1] ;
			mat[ ++cnt ] = map[i][j] ;
		}
		For( i , 2 , n )
			For( x , 0 , n - i )For( y , 0 , n - i ){
				mat[ ++cnt ] = 0 ;
				For( p , 0 , i - 1 )For( q , 0 , i - 1 )
					mat[cnt] ^= map[x + p][y + q] ;
			}
		For( i , 1 , k ){
			int x ; scanf( x ) ;
			full ^= bin[x - 1] ;
		}
		for( ans = 0 ; !chk( full , 0 ) ; ++ans ) ;
		printf("%d\n" , ans ) ;
	}
	
	return 0 ;
}
