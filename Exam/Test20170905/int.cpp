#include<cstdio>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; i-- )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template< typename type >
inline void scanf( type &in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch > '9'||ch < '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch >='0'&&ch <='9';ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

static const int maxn = 1e4 + 10 ;

int n ;
int m ;

int T[maxn] ;

bool flag[maxn] ;

int nxt[maxn] ;
int lst[maxn] ;

class INT{
	public :
		int x ;
		int y ;
		bool operator < ( const INT& t )
			const { return y == t.y ? x < t.x : y < t.y ; }
}TIT[maxn] ;

int Lowbit( int x ){ return x & -x ; }

void add( int x ){
	for( int i = x ; i <= m ; i += Lowbit( i ) )
		++T[i] ;
}

int query( int x ){
	int res = 0 ;
	for( int i = x ; i ; i -= Lowbit( i ) )res += T[i] ;
	return res ;
}

int query( int x , int y ){
	return query( y ) - query( x - 1 ) ;
}

int main(){
	
	freopen("int.in" , "r" , stdin) ;
	freopen("int.out" , "w" , stdout) ;
	
	scanf( n ) ;
	
	For( i , 1 , n )
		scanf( TIT[i].x ) , scanf( TIT[i].y ) ,
		++TIT[i].x , ++TIT[i].y , 
		m = max( m , TIT[i].y ) ;
	
	sort( 1 + TIT , 1 + n + TIT ) ;
	
	int ans = 0 ;
	
	For( i , 1 , n )
		lst[i] = i - 1 , nxt[i] = i + 1 ;
	nxt[n] = 0 ;
	
	For( i , 1 , n ){
		int t = query( TIT[i].x , TIT[i].y ) ;
		if( !t ){
			add( TIT[i].y - 1 ) ;
			add( TIT[i].y ) ;
			flag[ TIT[i].y - 1 ] = flag[ TIT[i].y ] = true ;
			nxt[ lst[ TIT[i].y - 1 ] ] = nxt[ TIT[i].y ] ;
			lst[ nxt[ TIT[i].y ] ] = lst[ TIT[i].y - 1 ] ;
			lst[ TIT[i].y ] = lst[ TIT[i].y - 1 ] ;
			nxt[ TIT[i].y - 1 ] = nxt[ TIT[i].y ] ;
			ans += 2 ;
		}
		else if( t == 1 ){
			if( !flag[ TIT[i].y ] ){
				flag[ TIT[i].y ] = true , add( TIT[i].y ) ;
				lst[ nxt[ TIT[i].y ] ] = lst[ TIT[i].y ] ;
				nxt[ lst[ TIT[i].y ] ] = nxt[ TIT[i].y ] ;
			}
			else{
				add( lst[ TIT[i].y ] ) ;
				int t = lst[ TIT[i].y ] ;
				flag[t] = true ;
				lst[ nxt[t] ] = lst[t] ;
				nxt[ lst[t] ] = nxt[t] ;
			}
			++ans ;
		}
	}
	
	printf("%d\n" , ans ) ;
	
	return 0 ;
}
