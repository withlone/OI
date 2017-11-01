#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std ;


#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Lop( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

static const int maxn = 1e5 + 10 ;
static const int maxm = 32 ;

int n ;
int m ;

int cnt ;

int cap[maxn] ;
int wei[maxn] ;
int weight[maxn] ;

int can[maxm] ;

int num[maxn] ;

void read_in(){
	
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , n )
		scanf( cap[i] ) ;
	For( i , 1 , m )
		scanf( weight[i] ) ;
		
}

void preparation(){
	
	sort( 1 + weight , 1 + m + weight ) ;
	
	memcpy( wei , weight , sizeof wei ) ;
	
	cnt = unique( 1 + wei , 1 + m + wei ) - wei - 1 ;
	
	For( i , 1 , m )
		num[i] = lower_bound( 1 + wei , 1 + cnt + wei , weight[i] ) - wei ;
	
	For( i , 1 , n ){
		int t = cap[i] ;
		Lop( j , cnt , 1 ){
			int p = t / wei[j] ;
			t -= p * wei[j] ;
			can[j] += p ;
		}
	}
	
	
}

void work(){
	
	For( i , 1 , m ){
		
		bool f = 0 ;
		
		if( can[num[i]] )
			can[num[i]]-- , f = true ;
		else{
			For( j , num[i] + 1 , cnt )
				if( can[j] ){
					can[j]-- ;
					f = true ;
					can[num[i]] += wei[j] / weight[i] - 1 ;
					break ;
				}
		}
		
		if( !f )return printf("%d\n" , i - 1 ) , void() ;
		
	}
	
	printf("%d\n" , m ) ;
	
}

int main(){
	
	freopen("odw.in" , "r" , stdin) ;
	freopen("odw.out" , "w" , stdout) ;
	
	read_in() ;
	
	preparation() ;
	
	work() ;
	
	return 0 ;
}
