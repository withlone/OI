#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }

static const int maxn = 1e4 + 10 ;
static const int maxm = 1000 ;

int n ;

char mRNA[maxn] ;
char key[maxm][4] ;

int F[maxn] ;

bool chk( int x ){
	For( i , 1 , n ){
		bool f = false ;
		For( j , x , x + 2 )
			if( key[i][j - x] != mRNA[j] )f = true ;
		if( !f )return true ;
	}
	return false ;
}

int main(){
	
	freopen( "cell.in" , "r" , stdin ) ;
	freopen( "cell.out" , "w" , stdout ) ;
	
	scanf( "%s" , mRNA + 1 ) ;
	
	for( n = 1 ; scanf( "%s" , key[n] ) != EOF ; ++n ) ;
	--n ;
	
	int mx = 0 ;
	For( i , 3 , strlen( mRNA + 1 ) )
		if( chk( i - 2 ) )F[i] = F[i - 3] + 1 , mx = max( mx , F[i] ) ;
		else F[i] = mx ;
	
	printf("%d\n" , mx ) ;
	
	return 0 ;
}
