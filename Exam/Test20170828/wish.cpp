#include<cstdio>

#define For( i , _begin , _end ) for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )
#define Rep( i , _begin , _add ) for( int i = (_begin) ; i ; i = (_add) )

template< typename type >inline type max ( type x , type y ){ return x > y ? x : y ; }
template< typename type >inline type min ( type x , type y ){ return x < y ? x : y ; }
template< typename type >inline void scanf( type &in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ; ch > '9' || ch < '0' ; ch = getchar() )if( ch == '-' )f = -1 ;
	for( ; ch >='0' && ch <='9' ; ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

typedef long long LL;
static const int maxn = 1e5 + 10;
static const int maxx = maxn << 2;

int n;
int r[maxn];
int d[maxn];

void read_in(){
	scanf( n ) ;
	For( i , 1 , n )
		scanf( r[i] ) , scanf( d[i] ) ;
}

namespace Segment_tree{
	
	LL T[maxx];
	
	#define Lson rt << 1 , l , mid
	#define Rson rt << 1 | 1 , mid + 1 , r
	
	void modify( int rt , int l , int r , int x , LL y ){
		if( l == r )return T[rt] = max( T[rt] , y ) , void();
		int mid = l + r >> 1;
		if( x <= mid )modify( Lson , x , y ) ;
		else modify( Rson , x , y ) ;
		T[rt] = max( T[rt << 1] , T[rt << 1 | 1] ) ;
	}
	
	LL query( int rt , int l , int r , int L , int R ){
		if( l > R || r < L )return 0;
		if( l >= L && r <= R )return T[rt];
		int mid = l + r >> 1;
		return max( query( Lson , L , R ) , query( Rson , L , R ) ) ;
	}
	
}using namespace Segment_tree;

LL F[maxn];

void DP(){
	LL ans = 0;
	For( i , 1 , n ){
		F[i] = query( 1 , 1 , n , 1 , i - 1 ) + r[i] ;
		modify( 1 , 1 , n , min( i + d[i] , n ) , F[i] ) ;
		ans = max( ans , F[i] ) ;
	}
	printf("%lld\n" , ans ) ;
}

int main(){
	
	freopen("wish.in","r",stdin);
	freopen("wish.out","w",stdout);
	
	read_in();
	
	DP();
	
	return 0;
}
