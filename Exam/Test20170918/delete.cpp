#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 64e3 + 10 ;

int n ;

int a[maxn] ;
int c[maxn] ;
int t1[maxn] ;
int t2[maxn] ;
int t3[maxn] ;
int t4[maxn] ;
int at[maxn] ;
int pos[maxn] ;

bool V[maxn] ;

int size[maxn] ;
int ans[501][maxn] ;

inline int div( int x ) {
	int l = 1 , r = n , res = 0 ;
	while( l <= r ) {
		int mid = l + r >> 1 ;
		if( x > c[mid] )res = mid , l = mid + 1 ;
		else r = mid - 1 ;
	}
	return res ;
}

inline int lis1( int *x , int n , int *pre , int *len ) {
	memset( c , 0x3f , sizeof(int) * ( n + 1 ) );
	int inf = c[0] , res = 0 ;
	For( i , 1 , n ) {
		int t = div( x[i] ) ;
		pre[i] = at[ ( c[t] == inf ? 0 : c[t] ) ] ;
		len[i] = t + 1 ;
		if( len[i] > len[res] )
			res = i ;
		c[t + 1] = min( c[t + 1] , x[i] ) ;
	}
	return res ;
}

inline int lis2( int *x , int n , int *pre , int *len ) {
	memset( c , 0x3f , sizeof(int) * ( n + 1 ) );
	int inf = c[0] , res = 0 ;
	Lop( i , n , 1 ) {
		int t = div( x[i] ) ;
		pre[i] = at[ ( c[t] == inf ? 0 : c[t] ) ] ;
		len[i] = t + 1 ;
		if( len[i] > len[res] )
			res = i ;
		c[t + 1] = min( c[t + 1] , x[i] ) ;
	}
	return res ;
}

int main() {
	
	freopen( "delete.in" , "r" , stdin ) ;
	freopen( "delete.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	
	For( i , 1 , n )
		pos[i] = at[ scanf( a[i] ) ] = i ;
	
	register int steps = 0 , mx1 , mx2 , t , p1 , p2 , tot ;
	
	while( n ) {
		mx1 = lis1( a , n , t1 , t2 ) ;
		mx2 = lis2( a , n , t3 , t4 ) ;
		++steps ;
		if( t2[ mx1 ] >= t4[ mx2 ] ) {
			for( t = mx1 ; t ; V[t] = true , t = t1[t] )++size[steps] ;
			tot = size[steps] ;
			for( t = mx1 ; t ; V[t] = true , t = t1[t] )
				ans[steps][ tot-- ] = a[t] ;
		}
		else {
			t = mx2 ;
			while( t ) {
				ans[steps][ ++size[steps] ] = a[t] ;
				V[t] = true ; t = t3[t] ;
			}
		}
		p1 = 1 , p2 = 1 ;
		while( true ) {
			while( !V[p1] && p1 <= n )++p1 ;
			p2 = p1 + 1 ;
			while( V[p2] && p2 <= n )++p2 ;
			if( p1 > n || p2 > n )break ;
			swap( a[p1] , a[p2] ) ;
			swap( V[p1] , V[p2] ) ;
			swap( pos[p1] , pos[p2] ) ;
			swap( at[a[p1]] , at[a[p2]] ) ;
		}
		while( n && V[n] )--n ;
	}
	
	printf("%d\n" , steps ) ;
	
	For( i , 1 , steps ) {
		printf("%d" , size[i] ) ;
		For( j , 1 , size[i] )
			printf(" %d" , ans[i][j] ) ;
		putchar( 10 ) ;
	}
	return 0 ;
}
