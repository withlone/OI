#include<cstdio>
#include<cstdlib>
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

template < typename type >
inline type max( const type& x , const type& y ) { return x > y ? x : y ; }
template < typename type >
inline type min( const type& x , const type& y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , const type& y ) {
	return x >= y ? false : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x <= y ? false : ( x = y , true ) ;
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

int n ;

int mayan[5][7] ;
bool V[7][7] ;

int answer[6][3] ;

inline void display( int steps ) {
	FOR( i , 1 , steps )
		printf( "%d %d %d\n" , answer[i][0] , answer[i][1] , answer[i][2] ) ;
	exit( 0 ) ;
}

inline bool chk() {
	For( i , 0 , 4 ) FOR( j , 0 , 6 ) if( mayan[i][j] ) return false ;
	return true ;
}

inline void adjust() {
	bool f ;
	do {
		f = false ;
		memset( V , 0 , sizeof V ) ;
		For( i , 0 , 4 ) {
			int p = 0 ;
			FOR( j , 0 , 6 ) {
				while( p <= 6 && !mayan[i][p] ) ++p ;
				if( p == 7 ) mayan[i][j] = 0 ;
				else mayan[i][j] = mayan[i][ p++ ] ;
			}
		}
		For( j , 0 , 6 ) For( i , 0 , 2 ) if( mayan[i][j] ) {
			register int k = i + 1 ;
			while( k <= 4 && mayan[i][j] == mayan[k][j] ) ++k ;
			--k ;
			if( k - i + 1 >= 3 ) {
				f = true ;
				for( ; i != k + 1 ; ++i )
					V[i][j] = true ;
			}
			i = k ;
		}
		For( i , 0 , 4 ) FOR( j , 0 , 4 ) if( mayan[i][j] ) {
			register int k = j + 1 ;
			while( k <= 6 && mayan[i][j] == mayan[i][k] ) ++k ;
			--k ;
			if( k - j + 1 >= 3 ) {
				f = true ;
				for( ; j != k + 1 ; ++j )
					V[i][j] = true ;
			}
			j = k ;
		}
		For( i , 0 , 4 ) FOR( j , 0 , 6 ) if( V[i][j] ) mayan[i][j] = 0 ;
		
	} while( f ) ;
}

void dfs( const int& steps ) {
	if( steps == n + 1 ) return chk() ? display( steps - 1 ) : void() ;
	int stor[5][7] ;
	memcpy( stor , mayan , sizeof stor ) ;
	For( i , 0 , 4 ) FOR( j , 0 , 6 ) if( mayan[i][j] ) {
		answer[steps][0] = i ; answer[steps][1] = j ;
		if( i != 4 ) {
			answer[steps][2] = 1 ;
			if( mayan[i + 1][j] )
				swap( mayan[i][j] , mayan[i + 1][j] ) ;
			else {
				bool f = true ;
				LOP( k , j , 1 )
					if( mayan[i + 1][k - 1] ) {
						mayan[i + 1][k] = mayan[i][j] ,
						mayan[i][j] = 0 , f = false ;
						break ;
					}
				if( f ) mayan[i + 1][0] = mayan[i][j] , mayan[i][j] = 0 ;
			}
			adjust() ;
			dfs( steps + 1 ) ;
			memcpy( mayan , stor , sizeof mayan ) ;
		}
		if( i ) {
			answer[steps][2] = -1 ;
			if( mayan[i - 1][j] )
				continue ;
			else {
				bool f = true ;
				LOP( k , j , 1 )
					if( mayan[i - 1][k - 1] ) {
						mayan[i - 1][k] = mayan[i][j] ,
						mayan[i][j] = 0 , f = false ;
						break ;
					}
				if( f ) mayan[i - 1][0] = mayan[i][j] , mayan[i][j] = 0 ;
			}
			adjust() ;
			dfs( steps + 1 ) ;
			memcpy( mayan , stor , sizeof mayan ) ;
		}
	}
}

int main() {
	
	freopen( "mayan.in" , "r" , stdin ) ;
	freopen( "mayan.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	For( i , 0 , 4 ) {
		int t ;
		for( register int j = 0 ; scanf( t ) ; ++j )
			mayan[i][j] = t ;
	}
	
	dfs( 1 ) ;
	
	puts( "-1" ) ;
	
	return 0 ;
}
