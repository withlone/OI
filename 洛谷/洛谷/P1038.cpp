#include<cstdio>

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
	return x > y ? false : x = y , true ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return x < y ? false : x = y , true ;
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

static const int maxn = 1e2 + 3 ;
static const int maxm = 1e4 + 7 ;

int n ;
int m ;

int C[maxn] ;
int U[maxn] ;

int idg[maxn] ;
int odg[maxn] ;

int head ;
int tail ;

int que[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;
int Dt[maxm] ;

inline void ins( const int& x , const int& y , const int& z ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
}

int main() {
	
	scanf( n ) ; scanf( m ) ;
	
	FOR( i , 1 , n ) {
		scanf( C[i] ) ; scanf( U[i] ) ;
		if( C[i] )que[ ++tail ] = i , U[i] = 0 ;
	}
	
	FOR( i , 1 , m ) {
		register int x , y , z ;
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		ins( x , y , z ) ; idg[y]++ ; odg[x]++ ;
	}
	
	while( head != tail ) {
		int x = que[ ++head ] ; C[x] -= U[x] ;
		if( C[x] <= 0 )continue ;
		REP( i , Ht[x] , Nt[i] ) {
			C[to[i]] += Dt[i] * C[x] ;
			if( !--idg[to[i]] )
				que[ ++tail ] = to[i] ;
		}
	}
	
	bool f = false ;
	
	FOR( i , 1 , n )
		if( !odg[i] && C[i] > 0 )
			f = true , printf( "%d %d\n" , i , C[i] ) ;
	
	if( !f )puts( "NULL" ) ;
	
	return 0 ;
}
