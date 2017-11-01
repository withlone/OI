#include<cstdio>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

static const int _len = 1 << 15 ;
char buffer[_len] , *S_T , *T_S ;

char Getchar(){
	if( S_T == T_S )
		T_S = ( S_T = buffer ) + fread( buffer , 1 , _len , stdin ) ;
	return T_S == S_T ? EOF : *S_T++ ;
}

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >
inline void swap( type& x , type& y ){ type t = x ; x = y ; y = t ; }

template< typename type >
inline void scanf( type&in ){
	in = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

typedef long long LL ;
static const int maxn = 2e5 + 10 ;
static const int mod1 = 233 ;
static const int mod2 = 149999957 ;

int n ;

int col[maxn] ;
int ans[maxn] ;
int hash1[maxn] ;
int hash2[maxn] ;
int getup[maxn] ;

bool V[mod2 + 10] ;

int qpow( int x , int y , int mod ){
	int res = 1 ;
	for( ; y ; y >>= 1 , x = 1LL * x * x % mod )
		if( y & 1 )res = 1LL * res * x % mod ;
	return res ;
}

int get1( int x , int y ){
	--x ;
	return
	1LL * ( hash1[y] - 1LL * hash1[x] * getup[y - x] % mod2 + mod2 ) % mod2 ;
}

int get2( int x , int y ){
	++y ;
	return
	1LL * ( hash2[x] - 1LL * hash2[y] * getup[y - x] % mod2 + mod2 ) % mod2 ;
}

int get_num( int k ){
	int res = 0 ;
	for( int i = 1 ; i + k - 1 <= n ; i += k ){
		int t = get1( i , i + k - 1 ) ;
		if( V[t] )continue ;
		V[t] = true ;
		t = get2( i , i + k - 1 ) ;
		V[t] = true ;
		++res ;
	}
	for( int i = 1 ; i + k - 1 <= n ; i += k ){
		int t = get1( i , i + k - 1 ) ;
		V[t] = false ;
		t = get2( i , i + k - 1 ) ;
		V[t] = false ;
	}
	return res ;
}

int main(){
	
	freopen( "beads.in" , "r" , stdin ) ;
	freopen( "beads.out" , "w" , stdout ) ;
	
	scanf( n ) ;
	getup[0] = 1 ;
	For( i , 1 , n ){
		scanf( col[i] ) ;
		getup[i] = 1LL * getup[i - 1] * mod1 % mod2 ;
		hash1[i] = ( 1LL * hash1[i - 1] * mod1 % mod2 + col[i] ) % mod2 ;
	}
	Lop( i , n , 1 )
		hash2[i] = ( 1LL * hash2[i + 1] * mod1 % mod2 + col[i] ) % mod2 ;
	
	int mx = 0 ;
	For( k , 1 , n ){
		int t = get_num( k ) ;
		if( t > mx )
			mx = t , ans[ ans[0] = 1 ] = k ;
		else if( t == mx )
			ans[ ++ans[0] ] = k ;
	}
	
	printf("%d %d\n" , mx , ans[0] ) ;
	
	For( i , 1 , ans[0] )printf("%d " , ans[i] ) ;
	
	putchar( 10 ) ;
	
	return 0 ;
}
