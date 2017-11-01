#include<cstdio>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )

static const int maxn = 1e5 + 10 ;

int n ;
double A ;

double Mi[maxn] ;
double sum[maxn] ;

int main() {
	
	scanf( "%d%lf" , &n , &A ) ;
	
	For( i , 1 , n )
		scanf( "%lf" , &Mi[i] ) , sum[i] = Mi[i] + sum[i - 1] ;
	
	register int t ;
	double ans ;
	
	For( i , 1 , n ) {
		ans = 0.0 ;
		t = (int)( A * i + 1e-8 ) ;
		if( i <= 1000 )
			For( j , 1 , t )
				ans += Mi[i] * Mi[j] / ( i - j ) ;
		else
			ans = Mi[i] * sum[t] / ( (double)i - 0.5 * t ) ;
		printf("%.6lf\n" , ans ) ;
	}
	
	return 0 ;
}
