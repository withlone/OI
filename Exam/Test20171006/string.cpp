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
	return ( x >= y ) ? ( false ) : ( x = y , true ) ;
}
template < typename type >
inline bool chkmin( type& x , const type& y ) {
	return ( x <= y ) ? ( false ) : ( x = y , true ) ;
}

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 1e5 + 19 ;
static const int maxm = 2e5 + 17 ;
static const int maxx = 4e5 + 31 ;

int n ;
int m ;

char si[maxn] ;
char ti[maxn] ;

class segment_tree {
	private :
		int sum[maxx] ;
		short tag[maxx] ;
	public :
		
		int id ;
		
		void build( int rt , int l , int r ) {
			tag[rt] = -1 ;
			if( l == r )return sum[rt] = ( si[l] == id + 'a' ) , void() ;
			int mid = l + r >> 1 ;
			build( rt << 1 , l , mid ) ;
			build( rt << 1 | 1 ,  mid + 1 , r ) ;
			sum[rt] = sum[rt << 1] + sum[rt << 1 | 1] ;
		}
		
		inline void pushdown( int rt , int L , int R ) {
			int l = rt << 1 , r = rt << 1 | 1 ;
			tag[l] = tag[r] = tag[rt] ;
			if( !tag[rt] )
				sum[l] = sum[r] = 0 ;
			else
				sum[l] = L , sum[r] = R ;
			tag[rt] = -1 ;
		}
		
		int query( int rt , int l , int r , int L , int R ) {
			if( !sum[rt] )return 0 ;
			if( l >= L && r <= R ) {
				int ret = sum[rt] ;
				sum[rt] = tag[rt] = 0 ;
				return ret ;
			}
			int mid = l + r >> 1 , res = 0 ;
			if( tag[rt] != -1 )pushdown( rt , mid - l + 1 , r - mid ) ;
			if( mid >= L )res += query( rt << 1 , l , mid , L , R ) ;
			if( mid < R )res += query( rt << 1 | 1 , mid + 1 , r , L , R ) ;
			sum[rt] = sum[rt << 1] + sum[rt << 1 | 1] ;
			return res ;
		}
		
		void modify( int rt , int l , int r , int L , int R ) {
			if( l >= L && r <= R )
				return sum[rt] = r - l + 1 , tag[rt] = 1 , void() ;
			int mid = l + r >> 1 ;
			if( tag[rt] != -1 )pushdown( rt , mid - l + 1 , r - mid ) ;
			if( mid >= L )modify( rt << 1 , l , mid , L , R ) ;
			if( mid < R )modify( rt << 1 | 1 , mid + 1 , r , L , R ) ;
			sum[rt] = sum[rt << 1] + sum[rt << 1 | 1] ;
		}
		
		void travel( int rt , int l , int r ) {
			if( l == r ) {
				if( sum[rt] )ti[l] = id + 'a' ;
				return ;
			}
			int mid = l + r >> 1 ;
			if( tag[rt] != -1 )pushdown( rt , mid - l + 1 , r - mid ) ;
			travel( rt << 1 , l , mid ) ;
			travel( rt << 1 | 1 , mid + 1 , r ) ;
		}
		
} tree[26] ;

int main() {
	
	freopen( "string.in" , "r" , stdin ) ;
	freopen( "string.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( m ) ;
	scanf( "%s" , si + 1 ) ;
	
	FOR( i , 0 , 25 )
		tree[i].id = i , tree[i].build( 1 , 1 , n ) ;
	
	while( m-- ) {
		int l , r , x , t ;
		int lst = scanf( l ) ; scanf( r ) ; scanf( x ) ;
		if( x ) {
			FOR( i , 0 , 25 )
				if( t = tree[i].query( 1 , 1 , n , l , r ) ) {
					tree[i].modify( 1 , 1 , n , lst , lst + t - 1 ) ;
					lst += t ;
				}
		} else {
			LOP( i , 25 , 0 )
				if( t = tree[i].query( 1 , 1 , n , l , r ) ) {
					tree[i].modify( 1 , 1 , n , lst , lst + t - 1 ) ;
					lst += t ;
				}
		}
	}
	
	FOR( i , 0 , 25 )
		tree[i].travel( 1 , 1 , n ) ;
	
	FOR( i , 1 , n )
		putchar( ti[i] ) ;
	
	putchar( 10 ) ;
	
	return 0 ;
}
