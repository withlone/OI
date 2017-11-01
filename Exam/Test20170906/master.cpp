#include<cmath>
#include<cstdio>

using namespace std ;

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

typedef double DB ;
static const int maxn = 1e4 + 10 ;
static const DB eps = 1e-5 ;

int cmp( DB x , DB y ){ return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ; }

DB max( DB x , DB y ){ return cmp( x , y ) == 1 ? x : y ; }
DB min( DB x , DB y ){ return cmp( x , y ) == -1 ? x : y ; }

int n ;
int k ;

int mid ;

DB mas[maxn] ;

bool chk(){
	int tot = 0 ;
	For( i , 1 , n ){
		tot += floor( mas[i] / mid ) ;
		if( tot >= k )return true ;
	}
	return false ;
}

int main(){
	
	freopen( "master.in" , "r" , stdin ) ;
	freopen( "master.out" , "w" , stdout ) ;
	
	int l = 0 , r = 1e9 ;
	
	scanf( "%d%d" , &n , &k ) ;
	
	For( i , 1 , n )
		scanf( "%lf" , &mas[i] ) , mas[i] *= 100 ;
	
	int ans = 0 ;
	
	while( l <= r ){
		mid = ( l + r ) >> 1 ;
		if( chk() )ans = mid , l = mid + 1 ;
		else r = mid - 1 ;
	}
	
	printf("%.2lf\n" , ans / 100.0 ) ;
	
	return 0 ;
}
