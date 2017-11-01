#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( register int i = (_begin) ; i ; i = (_add) )

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >
inline type chkmin( type& x , type y ){ return x < y ? x : x = y ; }
template< typename type >
inline type chkmax( type& x , type y ){ return x > y ? x : x = y ; }

static const int my_len = 1 << 15 ;
char buffer[my_len] , *Head , *Tail ;

inline char Getchar(){
	if( Head == Tail )
		Tail = ( Head = buffer ) + fread( buffer , 1 , my_len , stdin ) ;
	return Head == Tail ? EOF : *Head++ ;
}

template< typename type >
inline void scanf( type& in ){
	in = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0'; ch = Getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9'; ch = Getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

static const int maxn = 21 ;

int n ;
int tp ;

bool mp[maxn][maxn] ;

int F[maxn][2100000] ;
int user[maxn] ;
int bin[maxn] ;

int main(){
	
	freopen( "park.in" , "r" , stdin ) ;
	freopen( "park.out" , "w" , stdout ) ;
	
	memset( F , 0x3f , sizeof F ) ;
	
	scanf( n ) ;
	
	For( i , 1 , n )For( j , 1 , n )
		scanf( mp[i][j] ) ;
	
	bin[0] = 1 ;
	For( i , 1 , n )bin[i] = bin[i - 1] << 1 ;
	
	For( i , 1 , n )
		F[i][1 << i - 1] = 0 ;
	
	int limit = bin[n] - 1 ;
	
	For( status , 1 , limit ){
		tp = 0 ;
		For( i , 1 , n )if( bin[i - 1] & status )
			user[ ++tp ] = i ;
		For( i , 1 , tp ){
			register int tot = 0 ;
			register int x = user[i] ;
			For( j , 1 , tp )tot += mp[x][user[j]] ;
			For( j , 1 , tp )
				chkmin( F[x][status] , F[user[j]][status ^ bin[x - 1]] ) ;
			F[x][status] += tot ;
		}
	}
	
	int ans = F[0][0] ;
	
	For( i , 1 , n )
		chkmin( ans , F[i][limit] ) ;
	
	printf("%d\n" , ans ) ;
	
	return 0 ;
}
