#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }

static const int maxn = 1e6 + 10 ;

int n ;
char s[maxn] ;

int sum[3] ;

int wrong[3][3] ;

int main(){
	
	freopen( "process.in" , "r" , stdin ) ;
	freopen( "process.out" , "w" , stdout ) ;
	
	scanf( "%d" , &n ) ;
	scanf( "%s" , s + 1 ) ;
	
	For( i , 1 , n )
		++sum[s[i] - 'A'] ;
	
	For( i , 1 , n )
		if( i <= sum[0] ){
			if( s[i] != 'A' )++wrong[s[i] - 'A'][0] ;
		}
		else if( i <= sum[0] + sum[1] ){
			if( s[i] != 'B' )++wrong[s[i] - 'A'][1] ;
		}
		else{
			if( s[i] != 'C' )++wrong[s[i] - 'A'][2] ;
		}
	
	int t1 = min( wrong[0][1] , wrong[1][0] ) ;
	int t2 = min( wrong[1][2] , wrong[2][1] ) ;
	int t3 = min( wrong[2][0] , wrong[0][2] ) ;
	wrong[0][1] -= t1 , wrong[1][0] -= t1 ;
	wrong[1][2] -= t2 , wrong[2][1] -= t2 ;
	wrong[2][0] -= t3 , wrong[0][2] -= t3 ;
	
	int ans = 0 ;
	
	For( i , 0 , 2 )For( j , 0 , 2 )
		ans += wrong[i][j] ;
	
	printf("%d\n" , ans / 3 * 2 + t1 + t2 + t3 ) ;
	
	return 0 ;
}
