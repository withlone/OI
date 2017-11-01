#include<cstdio>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }
template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }
template < typename type >
inline void swap( type& x , type& y ){ type t = x ; x = y ; y = t ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

typedef long long LL ;
static const int hash_size = 1403641 ;
static const int maxn = 1e5 + 10 ;
static const int maxm = maxn << 1 ;

int n ;
int m ;
int tp ;
int hash_cnt = hash_size ;

int stack[maxn] ;

int dr[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

struct hash_table {
	bool id ;
	LL key ;
	int nxt ;
	hash_table(){ id = nxt = key = 0 ;}
} head[hash_size + maxn] ;

inline void ins( int x , int y ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
}

inline void hash( int x , int y ) {
	if( x > y )swap( x , y ) ;
	int id = ( x * 233 + y ) % hash_size ;
	LL key = 1LL * x * 1e6 + y ;
	if( !( head[id].id ) ) {
		head[id].id = true ;
		head[id].key = key ;
	} else {
		int t = id ;
		while( head[t].nxt )t = head[t].nxt ;
		head[t].nxt = ++hash_cnt ;
		head[hash_cnt].id = true ;
		head[hash_cnt].key = key ;
	}
}

inline bool get_hash( int x , int y ) {
	if( x > y )swap( x , y ) ;
	int id = ( x * 233 + y ) % hash_size ;
	LL key = 1LL * x * 1e6 + y ;
	int t = id ;
	while( t && head[t].key != key )t = head[t].nxt ;
	return t != 0 ? true : false ;
}

int main() {
	
	freopen( "triangle.in" , "r" , stdin ) ;
	freopen( "triangle.out" , "w" , stdout ) ;
	
	register int x , y ;
	
	scanf( n ) ; scanf( m ) ;
	
	For( i , 1 , m ) {
		scanf( x ) ; scanf( y ) ;
		ins( x , y ) ; ins( y , x ) ;
		++dr[x] ; ++dr[y] ;
		hash( x , y ) ;
	}
	
	LL tot = 1LL * n * ( n - 1 ) * ( n - 2 ) / 3 ;
	register int ans = 0 ;
	
	For( x , 1 , n ) {
		tp = 0 ;
		tot -= 1LL * dr[x] * ( n - 1 - dr[x] ) ;
		Rep( i , Ht[x] , Nt[i] )
			if( dr[x] < dr[to[i]] || dr[x] == dr[to[i]] && x < to[i] )
				stack[ ++tp ] = to[i] ;
		For( i , 1 , tp - 1 ) For( j , i + 1 , tp )
			if( get_hash( stack[i] , stack[j] ) )++ans ;
	}
	
	tot >>= 1 ;
	
	printf("%d %lld\n" , ans , tot - ans ) ;
	
	return 0 ;
}
