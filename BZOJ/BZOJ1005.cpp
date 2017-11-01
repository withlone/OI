#include<cstdio>
#include<cstring>
#include<cstdlib>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )

class bignum{
	private :
		typedef long long LL ;
		static const int maxn = 1000 ;
		static const LL ten = 1e9 ;
	public :
		int len ;
		LL s[maxn] ;
		bignum(){ memset( s , 0 , sizeof s ) ; len = 1 ; }
		bignum( const LL&x ){ *this = x ; }
				
		bignum operator = ( const LL& x ){
			len = 1 ; memset( s , 0 , sizeof s ) ;
			s[1] = x ;
			return *this ;
		}
		bignum operator * ( const bignum& x ){
			bignum y ;
			y.len = len + x.len + 1 ;
			For( i , 1 , len )For( j , 1 , x.len ){
				y.s[i + j - 1] += s[i] * x.s[j] ;
				y.s[i + j] += y.s[i + j - 1] / ten ;
				y.s[i + j - 1] %= ten ;
			}
			while( !y.s[ y.len ] && y.len > 1 )--y.len ;
			return y ;
		}
		
		void display(){
			printf("%lld" , s[len] ) ;
			Lop( i , len - 1 , 1 )printf("%09lld" , s[i] ) ;
			putchar( 10 ) ;
		}
}ans ;

static const int maxn = 1e3 + 10 ;

int n ;
int m ;
int tot ;

int d[maxn] ;

int H[maxn] ;

void div1( int x , int f ){
	for( int i = 2 ; i * i <= x ; ++i )
		while( !( x % i ) )
			x /= i , H[i] += f ;
	if( x != 1 )H[x] += f ;
}

void div2( int x , int f ){
	for( int i = 2 ; i <= x ; ++i )
		div1( i , f ) ;
}

void error(){ puts( "0" ) ; exit( 0 ) ; }

int main(){
	
	scanf( "%d" , &n ) ;
	
	For( i , 1 , n ){
		scanf( "%d" , &d[i] ) ;
		if( d[i] == -1 )++m ;
		else if( !d[i] )error() ;
		else tot += --d[i] , div2( d[i] , -1 );
	}
	
	if( n - 2 - tot < 0 )error() ;
	
	div2( n - 2 , 1 ) ;
	div1( m , n - 2 - tot ) ;
	div2( n - 2 - tot , -1 ) ;
	
	ans = 1LL ;
	
	For( i , 1 , n )For( j , 1 , H[i] )
		ans = ans * i ;
	
	ans.display() ;
	
	return 0 ;
}
