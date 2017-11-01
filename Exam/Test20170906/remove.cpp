#include<cstdio>
#include<algorithm>

using namespace std ;

#define For( i , _Begin , _End ) \
for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

#define Lson rt << 1 , l , mid
#define Rson rt << 1 | 1 , mid + 1 , r

static const int maxn = 1e4 + 10 ;
static const int maxm = maxn << 1 ;
static const int maxx = maxm << 2 ;

int n = 1 ;
int m ;
int dt ;

int Li[maxn] ;
int Ri[maxn] ;
int Hi[maxn] ;

int dir[maxm] ;
int ans[maxm] ;

int T[maxx] ;
int mx[maxx] ;

void modify( int rt , int l , int r , int L , int R , int H ){
	if( l > R || r < L )return ;
	if( l >= L && r <= R )
		return T[rt] = max( T[rt] , H ) , mx[rt] = max( mx[rt] , H ) , void() ;
	int mid = l + r >> 1 ;
	modify( Lson , L , R , H ) ;
	modify( Rson , L , R , H ) ;
}

void get_tree( int rt , int l , int r , int adder ){
	if( l == r )return ans[l] = max( T[rt] , adder ) , void() ;
	int mid = l + r >> 1;
	adder = max( adder , mx[rt] ) ;
	get_tree( Lson , adder ) ;
	get_tree( Rson , adder ) ;
}

int main(){
	
	freopen( "remove.in" , "r" , stdin ) ;
	freopen( "remove.out" , "w" , stdout ) ;
	
	while( scanf( "%d%d%d" , &Li[n] , &Hi[n] , &Ri[n] ) != EOF )++n ;
	--n ;
	
	For( i , 1 , n )dir[ ++dt ] = Li[i] , dir[ ++dt ] = Ri[i] ;
	
	sort( 1 + dir , 1 + dt + dir ) ;
	dt = unique( 1 + dir , 1 + dt + dir ) - dir - 1 ;
	
	For( i , 1 , n )
		Li[i] = lower_bound( 1 + dir , 1 + dt + dir , Li[i] ) - dir ,
		Ri[i] = lower_bound( 1 + dir , 1 + dt + dir , Ri[i] ) - dir ;
	For( i , 1 , n )
		Li[i] <<= 1 , Ri[i] <<= 1 , m = max( m , Ri[i] ) ;
	
	For( i , 1 , n )
		modify( 1 , 1 , m , Li[i] , Ri[i] , Hi[i] ) ;
	
	get_tree( 1 , 1 , m , 0 ) ;
	
	For( i , 2 , m )
		if( ans[i] != ans[i - 1] )
			printf( "%d %d " , dir[i >> 1] , ans[i] ) ;
	
	printf( "%d %d\n" , dir[m >> 1] , 0 ) ;
	
	return 0 ;
}
