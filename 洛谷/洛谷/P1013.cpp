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


static const int maxn = 13 ;

int n ;
int hex ;

char table[maxn][maxn][3] ;

int to[1000] ;

bool V[maxn] ;
bool sure[maxn] ;
int num[maxn] ;
int number[maxn][maxn] ;

int etp ;
int error[maxn] ;

inline void display() {
	FOR( i , 2 , n ) printf( "%c=%d " , table[1][i][0] , num[i] ) ;
	printf( "\n%d\n" , hex ) ;
	exit( 0 ) ;
}

inline bool is( int x ) {
	return x != -1 ;
}

inline bool chk() {
	memset( number , 0 , sizeof number ) ;
	FOR( i , 2 , n ) if( !is( num[ to[ table[1][i][0] ] ] ) ) return false ;
	For( i , 1 , n ) FOR( j , 1 , n )
		if( strlen( table[i][j] ) == 1 )
			number[i][j] = num[ to[ table[i][j][0] ] ] ;
		else
			number[i][j] = num[ to[ table[i][j][0] ] ] * hex +
							num[ to[ table[i][j][1] ] ] ;
	For( i , 2 , n ) FOR( j , 2 , n )
		if( number[1][j] + number[i][1] != number[i][j] ) return false ;
	return true ;
}

inline bool num_same() {
	bool chker[maxn] ;
	memset( chker , 0 , sizeof chker ) ;
	FOR( i , 2 , n )
		if( is( num[i] ) ) {
			if( chker[ num[i] ] ) return true ;
			chker[ num[i] ] = true ;
		}
	return false ;
}

inline bool modify() {
	etp = 0 ;
	beginer :
	bool f = false ;
	memset( number , -1 , sizeof number ) ;
	For( i , 1 , n ) FOR( j , 1 , n )
		if( strlen( table[i][j] ) == 1 )
			number[i][j] = num[ to[ table[i][j][0] ] ] ;
		else if( is( num[ to[ table[i][j][0] ] ] )
			& is( num[ to[ table[i][j][1] ] ] ) )
			number[i][j] = num[ to[ table[i][j][0] ] ] * hex +
							num[ to[ table[i][j][1] ] ] ;
	For( i , 2 , n ) FOR( j , 2 , n ) {
		int t = is( number[i][1] ) + is( number[1][j] ) + is( number[i][j] ) ;
		if( is( number[i][j] ) && !is( number[1][j] ) && 
			!strcmp( table[i][1] , table[1][j] ) ) {
			if( number[i][j] & 1 ) return false ;
			num[ to[ table[i][1][0] ] ] = number[i][j] >> 1 ;
			error[ ++etp ] = to[ table[i][1][0] ] ;
		} else if( t == 2 ) {
			if( !is( number[i][1] ) ) {
				f = true ,
				num[ to[ table[i][1][0] ] ] = number[i][j] - number[1][j] ;
				error[ ++etp ] = to[ table[i][1][0] ] ;
				if( num[ to[ table[i][1][0] ] ] < 0 ) return false ;
			} else if( !is( number[1][j] ) ) {
				f = true ,
				num[ to[ table[1][j][0] ] ] = number[i][j] - number[i][1] ;
				error[ ++etp ] = to[ table[1][j][0] ] ;
				if( num[ to[ table[1][j][0] ] ] < 0 ) return false ;
			} else {
				if( strlen( table[i][j] ) == 1 )
					f = true ,
					num[ to[ table[i][j][0] ] ] = number[i][1] + number[1][j] ,
					error[ ++etp ] = to[ table[i][j][0] ] ;
				else if( is( num[ to[ table[i][j][0] ] ] )
						^ is( num[ to[ table[i][j][1] ] ] ) ) {
						int t = number[i][1] + number[1][j] ;
						if( t < hex ) return false ;
						if( t >= ( hex << 1 ) ) return false ;
						if( is( num[ to[ table[i][j][0] ] ] ) )
							num[ to[ table[i][j][1] ] ] =
							t - num[ to[ table[i][j][0] ] ] * hex ,
							error[ ++etp ] = to[ table[i][j][1] ] ;
						else num[ to[ table[i][j][0] ] ] =
							t / hex , error[ ++etp ] = to[ table[i][j][0] ] ;
					}
				}
		} else if( t == 3 ) {
			if( number[i][j] != number[i][1] + number[1][j] ) return false ;
		}
	}
	if( num_same() ) return false ;
	if( f ) goto beginer ;
	return true ;
}

void dfs( int x ) {
	if( x == n + 1 ) return chk() ? display() : void() ;
	if( is( num[x] ) ) return dfs( x + 1 ) ;
	For( i , 0 , hex - 1 ) if( !V[i] ) {
		if( sure[x] && !i ) continue ;
		V[i] = true ;
		num[x] = i ;
		if( !modify() ) {
			while( etp ) num[ error[ etp-- ] ] = -1 ;
		}
		dfs( x + 1 ) ;
		V[i] = false ;
	}
	num[x] = -1 ;
}

int main() {
	
	scanf( n ) ;
	For( i , 1 , n ) FOR( j , 1 , n )
		scanf( "%s" , table[i][j] ) ;
	
	FOR( i , 2 , n ) to[ table[1][i][0] ] = i ;
	
	For( i , 1 , n ) FOR( j , 1 , n ) if( strlen( table[i][j] ) == 2 )
		sure[ to[ table[i][j][0] ] ] = true ;
	
	for( hex = n - 1 ; hex <= ( n << 1 ) ; ++hex )
		memset( num , -1 , sizeof num ) ,
		memset( V , 0 , sizeof V ) ,
		dfs( 2 ) ;
	
	puts( "ERROR!" ) ;
	
	return 0 ;
}
