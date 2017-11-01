#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type max( type x , type y ) { return x > y ? x : y ; }
template < typename type >
inline type min( type x , type y ) { return x < y ? x : y ; }
template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }
template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }
template < typename type >
inline void swap( type& x , type& y ){ type t = x ; x = y ; y = t ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

#define lson rt << 1 , l , mid
#define rson rt << 1 | 1 , mid + 1 , r
static const int maxn = 1e5 + 10 ;

int n ;
int N ;
int cnt ;

int fa[10] ;
int find( int t ){ return t == fa[t] ? t : fa[t] = find( fa[t] ) ; }
inline void link( int x , int y ){ fa[ find( x ) ] = find( y ) ; }

class data {
	public :
		bool dis[6] ;
		bool sit[6] ;
		data(){
			memset( dis , 0 , sizeof dis ) ;
			memset( sit , 0 , sizeof sit ) ;
		}
		inline void update() {
			memcpy( dis , sit , sizeof dis ) ;
			dis[1] |= dis[0] && dis[5] || dis[4] && dis[2] ;
			dis[3] |= dis[4] && dis[0] || dis[2] && dis[5] ;
			dis[0] |= dis[1] && dis[5] ;
			dis[2] |= dis[3] && dis[5] ;
			dis[4] |= dis[0] && dis[3] || dis[2] && dis[1] ;
			dis[5] |= dis[0] && dis[1] || dis[2] && dis[3] ;
		}
}T[maxn << 2] ;

inline data merge( data l , data r ) {
	data res ;
	res.dis[0] = l.dis[0] && r.dis[0] || l.dis[1] && r.dis[3] ;
	res.dis[1] = l.dis[0] && r.dis[1] || l.dis[1] && r.dis[2] ;
	res.dis[2] = l.dis[2] && r.dis[2] || l.dis[3] && r.dis[1] ;
	res.dis[3] = l.dis[2] && r.dis[3] || l.dis[3] && r.dis[0] ;
	res.dis[4] = l.dis[4] || res.dis[0] && res.dis[3] || res.dis[1] && res.dis[2] ;
	res.dis[5] = r.dis[5] || res.dis[0] && res.dis[1] || res.dis[2] && res.dis[3] ;
	return res ;
}

void modify1( int rt , int l , int r , int x , int y , bool f ) {
	if( l == r ) {
		if( x == 1 )T[rt].sit[0] = f ;
		else T[rt].sit[2] = f ;
		return T[rt].update() ;
	}
	int mid = l + r >> 1 ;
	if( y <= mid )modify1( lson , x , y , f ) ;
	else modify1( rson , x , y , f ) ;
	T[rt] = merge( T[rt << 1] , T[rt << 1 | 1] ) ;
}

void modify2( int rt , int l , int r , int y , bool f , int x ) {
	if( l == r )
		return T[rt].sit[x] = f , T[rt].update() ;
	int mid = l + r >> 1 ;
	if( y <= mid )modify2( lson , y , f , x ) ;
	else modify2( rson , y , f , x ) ;
	T[rt] = merge( T[rt << 1] , T[rt << 1 | 1] ) ;
}

data query( int rt , int l , int r , int L , int R ) {
	if( l >= L && r <= R )return T[rt] ;
	int mid = l + r >> 1 ;
	if( mid >= L && mid < R )
		return merge( query( lson , L , R ) , query( rson , L , R ) ) ;
	if( mid >= L )return query( lson , L , R ) ;
	return query( rson , L , R ) ; 
}

inline void printf( bool f ) {
	puts( f ? "Y" : "N" ) ;
}

int main() {
	
	char opt[10] ; bool f ; data ans , t1 , t2 ;
	register int x1 , y1 , x2 , y2 ;
	
	N = scanf( n ) - 1 ;
	
	while( scanf( "%s" , opt ) , strcmp( opt , "Exit" ) ) {
		scanf( x1 ) ; scanf( y1 ) ; scanf( x2 ) ; scanf( y2 ) ;
		if( y1 > y2 )swap( x1 , x2 ) , swap( y1 , y2 ) ;
		if( !strcmp( opt , "Ask" ) ) {
			if( x1 == x2 && y1 == y2 ){ puts( "Y" ) ; continue ; }
			if( N <= 0 ){ puts( !N ? "N" : "Y" ) ; continue ; }
			f = 0 ;
			if( y1 == y2 && y1 == n )f = 1 ;
			ans = query( 1 , 1 , N , y1 - f , y2 - ( y1 != y2 ) - f ) ;
			if( y1 - f > 1 )t1 = query( 1 , 1 , N , 1 , y1 - 1 - f ) ;
			else t1 = data() ;
			if( y2 - ( y1 != y2 ) + 1 - f <= N )
				t2 = query( 1 , 1 , N , y2 - ( y1 != y2 ) + 1 - f , N ) ;
			else t2 = data() ;
			if( t1.dis[5] )ans.dis[4] = true ;
			if( t2.dis[4] )ans.dis[5] = true ;
			memcpy( ans.sit , ans.dis , sizeof ans.sit ) ;
			ans.update() ;
			if( f )printf( ans.dis[5] ) ;
			else if( y1 == y2 )printf( ans.dis[4] ) ;
			else {
				if( x1 == x2 ) {
					if( x1 == 1 )printf( ans.dis[0] ) ;
					else printf( ans.dis[2] ) ;
				}
				else {
					if( x1 == 1 )printf( ans.dis[1] ) ;
					else printf( ans.dis[3] ) ;
				}
			}
		}
		else {
			f = !strcmp( opt , "Open" ) ;
			if( N <= 0 ){ N = f ? -1 : 0 ; continue ; }
			if( x1 == x2 )modify1( 1 , 1 , N , x1 , y1 , f ) ;
			else if( y1 == 1 )
				 modify2( 1 , 1 , N , 1 , f , 4 ) ;
			else if( y1 == n )
				 modify2( 1 , 1 , N , N , f , 5 ) ;
			else modify2( 1 , 1 , N , y1 - 1 , f , 5 ) ,
				 modify2( 1 , 1 , N , y1 , f , 4 ) ;
		}
	}
	
	return 0 ;
}
