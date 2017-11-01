#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std ;

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; i-- )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template< typename type >inline void scanf( type &in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ; ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ; ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

static const int maxn = 50 + 10 ;

int n;

int P[maxn] ;
int times[maxn] ;

int win[maxn] ;
int tie[maxn] ;
int lose[maxn] ;

void read_in(){
	scanf( n ) ;
	For( i , 1 , n )
		scanf( P[i] ) ;
}

bool chk( int top ){
	int win_tot = n - top + 1 << 2 ;
	
	static int file[maxn] ;
	memcpy( file , tie , sizeof file ) ;
	
	For( i , 2 , top )
		For( j , 2 , top )if( i != j ){
			if( tie[i] > tie[j] )
				tie[i] -= tie[j] , tie[j] = 0 ;
			else
				tie[j] -= tie[i] , tie[i] = 0 ;
		}
	int tie_tot = 0 , lose_tot = 0 ;
	For( i , 2 , top )
		tie_tot += tie[i] , lose_tot += lose[i] ;
	memcpy( tie , file , sizeof tie ) ;
	return win_tot >= tie_tot + lose_tot ;
}

int diver( int l , int r ){
	int res = 1 ;
	while( l <= r ){
		int mid = l + r >> 1;
		if( chk( mid ) )res = mid , l = mid + 1 ;
		else r = mid - 1 ;
	}
	return res ;
}

void run(){
	sort( 2 + P , 1 + n + P ) ;
	int l = 2 , r = n ;
	For( i , 2 , n )
		if( P[1] + 12 < P[i] ){ r = i - 1 ; break ; }
	win[1] = 4 ;
	For( i , r + 1 , n )
		win[i] = 4 ;
	For( i , l , r ){
		int t = P[1] + 12 - P[i] ;
		if( t <= 4 )
			tie[i] = t , lose[i] = 4 - t ;
		else if( t < 6 )
			tie[i] = 4 ;
		else if( t < 8 )
			win[i] = 1 , tie[i] = 3 ;
		else if( t < 10 )
			win[i] = 2 , tie[i] = 2 ;
		else if( t < 12 )
			win[i] = 3 , tie[i] = 1 ;
		else win[i] = 4 ;
	}
	printf("%d\n" , n - diver( l , r ) + 1 ) ;
}

int main(){
	
	freopen("football.in" , "r" , stdin) ;
	freopen("football.out" , "w" , stdout) ;
	
	read_in() ;
	
	run() ;
	
	return 0 ;
}
