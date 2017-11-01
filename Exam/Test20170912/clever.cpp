#include<cstdio>

#define For( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

static const int _len = 1 << 15 ;
char buffer[_len] , *S_T , *T_S ;

char Getchar(){
	if( S_T == T_S )
		T_S = ( S_T = buffer ) + fread( buffer , 1 , _len , stdin ) ;
	return T_S == S_T ? EOF : *S_T++ ;
}

template< typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >
inline void swap( type& x , type& y ){ type t = x ; x = y ; y = t ; }


template< typename type >
inline void scanf( type&in ){
	in = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

static const int maxn = 1e2 + 10 ;
static const int maxm = 1e5 + 10 ;
static const int mod = ( 1 << 8 ) - 1 ;
static const double eps = 1e-6 ;

template< typename type >
inline type abs( type x ){ return x > 0 ? x : -x ; }
double sqrt( double x ){
	double res = x ;
	while( abs( res * res - x ) > eps )
		res = ( res + x / res ) / 2.0 ;
	return res ;
}
int cmp( double x , double y ){
	return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ;
}

int n ;
double v ;

bool V[maxn] ;
double dis[maxn] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;
double Dt[maxm] ;

class tree{
	public :
		double x ;
		double y ;
		int fa ;
		tree(){ x = y = 0.0 ; fa = 0 ; }
}T[maxn] ;

void ins( int x , int y , double z ){
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; Dt[Ct] = z ;
}

double sqr( double x ){ return x * x ; }
double dist( int x , int y ){
	return sqrt( sqr( T[x].x - T[y].x ) + sqr( T[x].y - T[y].y ) ) ;
}

void spfa( int S , int T ){
	static int que[mod + 10] ;
	int head = 0 , tail = 0 ;
	For( i , 1 , n )dis[i] = 1e13 ;
	dis[S] = 0.0 ; que[ ++tail ] = S ;
	while( head != tail ){
		int x = que[ ++head &= mod ] ; V[x] = false ;
		Rep( i , Ht[x] , Nt[i] )
			if( cmp( dis[to[i]] , dis[x] + Dt[i] ) == 1 ){
				dis[to[i]] = dis[x] + Dt[i] ;
				if( !V[to[i]] )
					V[to[i]] = true , que[ ++tail &= mod ] = to[i] ;
			}
	}
	printf("%.2lf\n" , dis[T] ) ;
}

int main(){
	
	freopen( "clever.in" , "r" , stdin ) ;
	freopen( "clever.out" , "w" , stdout ) ;
	
	scanf( "%d%lf" , &n , &v ) ;
	For( i , 1 , n )
		scanf( "%lf%lf%d" , &T[i].x , &T[i].y , &T[i].fa ) ;
	
	For( i , 1 , n )if( T[i].fa )
		ins( i , T[i].fa , dist( i , T[i].fa ) / v ) ,
		ins( T[i].fa , i , dist( T[i].fa , i ) / v ) ;
	
	For( i , 1 , n )For( j , 1 , n )if( i != j )
		if( !cmp( T[i].x , T[j].x ) && cmp( T[i].y , T[j].y ) == 1 )
			ins( i , j , sqrt( ( T[i].y - T[j].y ) * 0.2 ) ) ;
	
	spfa( 1 , n ) ;
	
	return 0 ;
}
