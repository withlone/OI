#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }

static const int maxn = 1e6 + 10 ;
static const int maxm = 5e3 + 10 ;

char a[maxn] ;
char s[maxn] ;
char tmp[maxn] ;
char ans[maxn] ;

int t ;
int k ;

bool flag ;

int len1 ;
int len2 ;
int len_a ;
int len_b ;
int len_s ;

bool chk(){
	For( i , 1 , len1 )
		if( tmp[i] != ans[i] )
			return tmp[i] < ans[i] ;
	return false ;
}

bool chk1( int x ){
	For( i , 1 , k )
		if( a[ ( i - 1 ) * len_b + x ] != s[ ( i - 1 ) * len2 + t ] )
			return false ;
	return true ;
}

bool chk2( int x ){
	if( k * len_b + x > len_a || k * len2 + t > len_s )return false ;
	return chk1( x ) && a[ k * len_b + x ] == s[ k * len2 + t ] ;
}

int main(){
	
	freopen("string.in" , "r" , stdin) ;
	freopen("string.out" , "w" , stdout) ;
	
	scanf( "%s" , a + 1 ) ;
	scanf( "%s" , s + 1 ) ;
	scanf( "%d" , &len_b ) ;
	
	len_a = strlen( a + 1 ) ; len_s = strlen( s + 1 ) ;
	
	len1 = min( len_a , len_b ) ;
	
	k = len_a / len1 ;
	
	For( i , 1 , len1 )ans[i] = 2 ;
	
	For( len , 0 , len1 )
		if( !( ( len_s - len ) % k ) && len <= ( len_s - len ) / k ){
			
			For( i , 1 , len1 )tmp[i] = 0 ;
			
			t = len2 = ( len_s - len ) / k ;
			
			Lop( i , len1 , 1 ){
				if( t > len ){
					if( chk1( i ) )
						tmp[i] = 1 , --t ;
				}
				else if( chk2( i ) )
					tmp[i] = 1 , --t ;
			}
			
			if( !t ){
				if( chk() )memcpy( ans , tmp , sizeof ans ) ;
				flag = true ;
			}
			
		}
	
	if( flag ){
		For( i , 1 , len1 )printf("%d" , ans[i] ) ;
		For( i , len1 + 1 , len_b )putchar( '0' ) ;
		putchar( 10 ) ;
	}
	else puts( "-1" ) ;
	
	return 0 ;
}
