#include<cmath>
#include<cstdio>

using namespace std ;

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) \
for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >
inline void swap( type &x , type &y ){ type t = x ; x = y ; y = t ; }
template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

typedef long long LL ;
static const int maxp = 1e6 + 10 ;

LL exgcd( LL a , LL b , LL& x , LL& y ){
	if( !b )return x = 1 , y = 0 , a ;
	LL res = exgcd( b , a % b , x , y ) ;
	LL t = x ; x = y ; y = t - ( a / b ) * y ;
	return res ;
}

int T ;
LL mod ;
LL n ;
LL a ;
LL b ;
LL c ;
LL d ;

LL mul[maxp] ;

void init(){
	LL t = mul[0] = 1 ;
	For( i , 1 , mod - 1 ){
		t = ( t * i ) % mod ;
		if( !( i % 10 ) )mul[i / 10] = t ;
	}
}

LL get( int x ){
	if( x >= mod )return 0 ;
	LL t = mul[x / 10] ;
	For( i , x / 10 * 10 + 1 , x )
		t = ( t * i ) % mod ;
	return t ;
}

LL power( LL x , LL y ){
	LL res = 1 ;
	for( ; y ; y >>= 1 , x = ( x * x ) % mod )
		if( y & 1 )res = ( res * x ) % mod ;
	return res ;
}

LL muler( LL x , LL y , LL P ){
	return ( x * y - (LL)((long double)x * y / P + 1e-8 ) * P ) % P ;
}

LL C( LL n , LL m ){
	return m > n ? 0LL : !m ? 1 : m == 1 ? n % mod :
	get( n ) * power( get( m ) * get( n - m ) % mod , mod - 2 ) % mod ;
}

LL lucas( LL n , LL m ){
	return !m ? 1LL : C( n % mod , m % mod ) * lucas( n / mod , m / mod ) % mod ;
}

int main(){
	
	freopen( "math.in" , "r" , stdin ) ;
	freopen( "math.out" , "w" , stdout ) ;
	
	scanf( T ) ; scanf( mod ) ;
	
	init() ;
	
	while( T-- ){
		scanf( n ) ; scanf( a ) ; scanf( b ) ; scanf( c ) ; scanf( d ) ;
		
		LL C = b * d ;
		LL A = muler( muler( a , d , C ) , n , C ) ;
		LL B = ( b * c - a * d ) % C ;
		
		LL x0 , y0 ;
		LL gcd = exgcd( B , -C , x0 , y0 ) ;
		
		LL num , ans ;
		
		if( -A % gcd )num = 0 ;
		else{
			x0 = muler( x0 , ( -A / gcd ) , C ) ;
			LL l = -x0 , r = n - x0 ;
			LL t = -C / gcd ;
			if( t < 0 )swap( l , r ) , t = -t , l = -l , r = -r ;
			
			if( l <= 0 )l /= t ;
			else l = l / t + ( l % t != 0 ) ;
			if( r >= 0 )r /= t ;
			else r = r / t - ( r % t != 0 ) ;
			
			num = max( r - l + 1 , 0LL ) ;
		}
		
		ans = get( num ) * get( n - num + 1 ) % mod
				 * lucas( n - num + 2 , num ) % mod ;
		
		printf("%lld %lld\n" , num , ans ) ;
		
	}
	
	return 0 ;
}
