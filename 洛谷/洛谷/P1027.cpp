#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>

using std :: pair ;
using std :: make_pair ;

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; ++i )
#define Lop( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i >= (i##end) ; --i )
#define Rep( i , _begin , _add ) \
for( int i = (_begin) ; i ; i = (_add) )

template < typename type >
inline type min( type x , type y ){ return x < y ? x : y ; }
template < typename type >
inline type max( type x , type y ){ return x > y ? x : y ; }
template < typename type >
inline bool chkmin( type& x , type y ){ return x < y ? false : x = y , true ; }
template < typename type >
inline bool chkmax( type& x , type y ){ return x > y ? false : x = y , true ; }
template < typename type >
inline type sqr( type x ){ return x * x ; }
template < typename type >
inline type abs( type x ){ return x > 0 ? x : -x ; }

template < typename type >
inline type scanf( type& in ) {
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' )f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = getchar() )in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 400 + 10 ;
static const int maxm = 4e4 + 10 ;
static const int mod = ( 1 << 9 ) - 1 ;
static const double eps = 1e-5 ;

inline int cmp( double x , double y ){
	return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ;
}

int n ;
int A ;
int B ;
int cnt ;
int cases ;
int prize ;

int Ti[maxn] ;

int num[maxn][maxn] ;

pair < int , int > at[maxn] ;

double dis[maxn] ;
bool V[maxn] ;

int xi[maxn][5] ;
int yi[maxn][5] ;

int Ct ;
int Ht[maxn] ;
int Nt[maxm] ;
int to[maxm] ;
double dt[maxm] ;

inline void ins( int x , int y , double z ) {
	Nt[ ++Ct ] = Ht[x] ; Ht[x] = Ct ; to[Ct] = y ; dt[Ct] = z ;
	Nt[ ++Ct ] = Ht[y] ; Ht[y] = Ct ; to[Ct] = x ; dt[Ct] = z ;
}

inline int get_point( int x ) {
	if( yi[x][1] == yi[x][2] || yi[x][2] == yi[x][3] || yi[x][1] == yi[x][3] )
		return 0 ;
	static double k[4] ;
	k[1] = ( xi[x][1] - xi[x][2] ) * 1.0 / ( yi[x][1] - yi[x][2] ) ;
	k[2] = ( xi[x][2] - xi[x][3] ) * 1.0 / ( yi[x][2] - yi[x][3] ) ;
	k[3] = ( xi[x][1] - xi[x][3] ) * 1.0 / ( yi[x][1] - yi[x][3] ) ;
	if( !cmp( -1 , k[1] * k[3] ) )return 1 ;
	if( !cmp( -1 , k[1] * k[2] ) )return 2 ;
	if( !cmp( -1 , k[2] * k[3] ) )return 3 ;
}

inline void adjust() {
	For( i , 1 , n ) {
		int t1 = get_point( i ) , t2 = t1 % 3 + 1 , t3 = 6 - t1 - t2 ;
		if( !t1 ) {
			if( xi[i][1] == xi[i][2] )xi[i][4] = xi[i][3] ;
			else xi[i][4] = xi[i][1] + xi[i][2] - xi[i][3] ;
			if( yi[i][1] == yi[i][2] )yi[i][4] = yi[i][3] ;
			else yi[i][4] = yi[i][1] + yi[i][2] - yi[i][3] ;
		} else {
			xi[i][4] = xi[i][t2] - xi[i][t1] + xi[i][t3] ;
			yi[i][4] = yi[i][t2] - yi[i][t1] + yi[i][t3] ;
		}
	}
}

inline double dist( int x , int y ) {
	double t1 = sqr( 1.0 * ( at[x].first - at[y].first ) ) ;
	double t2 = sqr( 1.0 * ( at[x].second - at[y].second ) ) ;
	return sqrt( t1 + t2 ) ;
}

inline void build_edge() {
	cnt = Ct = 0 ;
	memset( Ht , 0 , sizeof Ht ) ;
	memset( num , 0 , sizeof num ) ;
	For( i , 1 , n ) For( j , 1 , 4 )
		num[i][j] = ++cnt , at[cnt] = make_pair( xi[i][j] , yi[i][j] ) ;
	For( i , 1 , n ) For( j , 1 , 3 ) For( k , j + 1 , 4 )
		ins( num[i][j] , num[i][k] , dist( num[i][j] , num[i][k] ) * Ti[i] ) ;
	For( i , 1 , n ) For( j , 1 , 4 ) For( I , i + 1 , n ) For( J , 1 , 4 )
		ins( num[i][j] , num[I][J] , dist( num[i][j] , num[I][J] ) * prize ) ;
}

inline double spfa( int S , int T ) {
	if( S == T )return 0.0 ;
	static int que[mod + 10] ;
	int head = 0 , tail = 0 ;
	memset( dis , 0x7f , sizeof dis ) ;
	For( i , num[S][1] , num[S][4] )
		que[ ++tail ] = i , dis[i] = 0 ;
	while( head != tail ) {
		int x = que[ ++head &= mod ] ; V[x] = false ;
		Rep( i , Ht[x] , Nt[i] )
			if( cmp( dis[to[i]] , dis[x] + dt[i] ) == 1 ) {
				dis[to[i]] = dis[x] + dt[i] ; 
				if( !V[to[i]] )
					V[to[i]] = true , que[ ++tail &= mod ] = to[i] ;
			}
	}
	double ans = dis[0] ;
	For( i , num[T][1] , num[T][4] )
		if( cmp( ans , dis[i] ) == 1 )ans = dis[i] ;
	return ans ;
}

inline void solve() {
	adjust() ;
	build_edge() ;
	printf( "%.1lf\n" , spfa( A , B ) ) ;
}

int main() {
	
	scanf( cases ) ;
	
	while( cases-- ) {
		scanf( n ) ; scanf( prize ) ; scanf( A ) ; scanf( B ) ;
		For( i , 1 , n ) {
			For( j , 1 , 3 )
				scanf( xi[i][j] ) , scanf( yi[i][j] ) ;
			scanf( Ti[i] ) ;
		}
		solve() ;
	}
	
	return 0 ;
}
