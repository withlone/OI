#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std ;

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) \
for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

static const int maxn = 1e5 + 10 ;
static const int maxm = 4e5 + 10 ;
static const int maxk = 80 + 10 ;

int n ;
int m ;
int k ;

int happy[maxn] ;

int F[maxn] ;
int G[maxn] ;

int id[maxn] ;

int Ct = 1 ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;

void ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ;
}

bool cmp( int x , int y ){
	return happy[x] > happy[y] ;
}

int main(){
	
	freopen("walk.in" , "r" , stdin) ;
	freopen("walk.out" , "w" , stdout) ;
	
	scanf( n ) ; scanf( m ) ; scanf( k ) ;
	
	For( i , 1 , n )
		scanf( happy[i] ) , id[i] = i ;
	
	For( i , 1 , m ){
		int x , y ;
		scanf( x ) ; scanf( y ) ;
		ins( x , y ) ;
	}
	
	sort( id + 1 , id + n + 1 , cmp ) ;
	
	For( i , 1 , n )F[i] = 1 ;
	
	For( y , 1 , n ){
		int x = id[y] ;
		Rep( i , Ht[x] , Nt[i] )
			if( happy[x] < happy[to[i]] )
				F[x] = max( F[x] , F[to[i]] + 1 ) ;
	}
	
	For( I , 1 , k ){
		For( y , 1 , n ){
			int x = id[y] ;
			Rep( i , Ht[x] , Nt[i] )
				if( happy[x] >= happy[to[i]] )
					G[x] = max( G[x] , F[to[i]] + 1 ) ;
		}
		For( y , 1 , n ){
			int x = id[y] ;
			Rep( i , Ht[x] , Nt[i] )
				if( happy[x] < happy[to[i]] )
					G[x] = max( G[x] , G[to[i]] + 1 ) ;
		}
		memcpy( F , G , sizeof( int ) * ( n + 1 ) ) ;
		memset( G , 0 , sizeof( int ) * ( n + 1 ) ) ;
		For( x , 1 , n )
			if( F[x] > 1e9 + 7 )return puts( "infinity" ) , 0 ;
	}
	
	int ans = 0 ;
	For( i , 1 , n )ans = max( ans , F[i] ) ;
	
	printf("%d\n" , ans ) ;
	
	return 0 ;
}
