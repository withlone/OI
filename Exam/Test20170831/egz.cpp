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

int n ;
int m ;
int p ;
int k ;

int lnd[maxn] ;
int rnd[maxn] ;

class road{
	
	public :
	
	int ni ;
	int mi ;
	int di ;
	
	bool operator < ( const road &t ) const {
		if( di != t.di )return di < t.di ;
		if( ni != t.ni )return ni < t.ni ;
		if( mi != t.mi )return mi < t.mi ;
	}
	
}rd[maxn] ;

void read_in(){
	scanf( n ) ; scanf( m ) ; scanf( p ) ; scanf( k ) ;
	For( i , 1 , p )
		scanf( rd[i].ni ) , scanf( rd[i].mi ) , scanf( rd[i].di ) ;
}

namespace LIS{
	
	int div[maxn] ;
	
	int get( int cmper ){
		int l = 1 , r = n ;
		while( l <= r ){
			int mid = l + r >> 1 ;
			if( cmper <= div[mid] )l = mid + 1 ;
			else r = mid - 1 ;
		}
		return l ;
	}
	
	int mine[maxn] ;
	
	void LIS1( int top ){
		memset( div , -0x3f , sizeof div ) ;
		memset( mine , 0 , sizeof mine ) ;
		Lop( i , top , 1 ){
			int j = i , y = rd[i].ni ;
			while( rd[j - 1].ni == rd[i].ni )--j ;
			For( x , j , i )
				rnd[y] = max( rnd[y] , mine[x] = get( rd[x].mi ) ) ;
			For( x , j , i )
				div[ mine[x] ] = max( div[ mine[x] ] , rd[x].mi ) ;
			i = j ;
		}
	}
	
	void LIS2( int bottom ){
		memset( div , -0x3f , sizeof div ) ;
		memset( mine , 0 , sizeof mine ) ;
		For( i , bottom , p ){
			int j = i , y = rd[i].ni ;
			while( rd[j + 1].ni == rd[i].ni )++j ;
			For( x , i , j )
				lnd[y] = max( lnd[y] , mine[x] = get( rd[x].mi ) ) ;
			For( x , i , j )
				div[ mine[x] ] = max( div[ mine[x] ] , rd[x].mi ) ;
			i = j ;
		}
	}
	
	void arrange(){
		int mx = 0 ;
		Lop( i , n , 1 ){
			int t = rnd[i] ;
			rnd[i] = n - i - max( mx , rnd[i] ) ;
			mx = max( mx , t ) ;
		}
		mx = 0 ;
		For( i , 1 , n ){
			int t = lnd[i] ;
			lnd[i] = i - 1 - max( mx , lnd[i] ) ;
			mx = max( mx , t ) ;
		}
	}
	
	void main(){
		
		int diver = p ;
		
		sort( 1 + rd , 1 + p + rd ) ;
		
		For( i , 1 , p )
			if( rd[i].di ){ diver = i - 1 ; break ; }
		
		For( i , diver + 1 , p )
			rd[i].ni++ ;
		
		LIS1( diver ) ;
		
		LIS2( diver + 1 ) ;
		
		arrange() ;
		
	}
	
}

namespace move{
	
	
	int sum[maxn] ;
	
	void main(){
		
		int ans = 0 ;
		
		For( i , 1 , n )
			if( !( lnd[i] + rnd[i] ) )sum[i] = sum[i - 1] + 1 ;
			else sum[i] = sum[i - 1] ;
		
		int ql = 1 , qr = 1 ;
		
		while( ql <= n && qr <= n ){
			
			if( qr < ql )qr = ql ;
			
			while( rnd[ql] + lnd[qr] <= k && qr <= n )
				++qr ;
			
			ans = max( ans , qr - ql - sum[qr - 1] + sum[ql - 1] ) ;
			
			++ql ;
		}
		
		printf("%d\n" , ans ) ;
		
	}
	
}

int main(){
	
	freopen("egz.in" , "r" , stdin) ;
	freopen("egz.out" , "w" , stdout ) ;
	
	read_in() ;
	
	LIS :: main() ;
	
	move :: main() ;
	
	return 0 ;
}
