#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

static const int maxn = 1e3 + 10 ;
static const int maxm = maxn << 1 ;
static const int mod = 1e9 ;

char number[maxn] ;

int size ;
int vec[maxm] ;

int F[maxm][2] ;
int G[maxm][2] ;

void get_four( char *x ){
	int n = strlen( x ) - 1 ;
	For( i , 0 , n )x[i] -= '0' ;
	int t = 0 , start = 0 ;
	while( start <= n ){
		t = 0 ;
		For( i , start , n ){
			x[i] += 10 * t ;
			t = x[i] % 4 ;
			x[i] >>= 2 ;
		}
		while( !x[start] && start <= n )++start ;
		vec[ ++size ] = t ;
	}
}

void DP(){
	G[0][0] = G[0][1] = 1 ;
	For( i , 1 , size ){
		F[i][0] = F[i - 1][0] + vec[i] ;
		F[i][1] = F[i - 1][1] + 3 + ( i == 1 ) - vec[i] ;
		G[i][0] = G[i - 1][0] ;
		G[i][1] = G[i - 1][1] ;
		if( F[i][0] > F[i][1] ){
			G[i][0] = G[i][1] ;
			if( F[i][0] == F[i][1] + 1 )
				G[i][0] = ( G[i][0] + G[i - 1][0] ) % mod ;
			else
				F[i][0] = F[i][1] + 1 ;
		}
		else if( F[i][0] < F[i][1] ){
			G[i][1] = G[i][0] ;
			if( F[i][1] == F[i][0] + 1 )
				G[i][1] = ( G[i][1] + G[i - 1][1] ) % mod ;
			else
				F[i][1] = F[i][0] + 1 ;
		}
	}
	printf("%d\n" , G[size][0] ) ;
}

int main(){
	
	freopen("wag.in" , "r" , stdin) ;
	freopen("wag.out" , "w" , stdout) ;
	
	scanf( "%s" , number ) ;
	
	get_four( number ) ;
	
	DP() ;
	
	return 0 ;
}
