#include<cstdio>
#include<cstring>

#define For( i , _begin , _end ) \
for( register int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )

static const int LEN = 1 << 15 ;
char buffer[LEN] , *S_T , *T_S ;

char Getchar(){
	if( S_T == T_S )T_S = ( S_T = buffer ) + fread( buffer , 1 , LEN , stdin ) ;
	return S_T == T_S ? EOF : *S_T++ ;
}

template< typename type >
inline void scanf( type &In ){
	In = 0 ; char ch = Getchar() ; type f = 1 ;
	for( ;ch> '9'||ch< '0';ch = Getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch>='0'&&ch<='9';ch = Getchar() )In = In * 10 + ch - '0' ; In *= f ;
}

static const int maxn = 1e5 + 10 ;
static const int maxm = maxn << 2 ;

int n ;
int q ;
int seq ;
int ans ;

class segment_tree{
	private :
		int T[maxm] ;
		int add[maxm] ;
	public :
		segment_tree(){
			memset( T , 0 , sizeof(int) * (n << 1 | 1) ) ;
			memset( add , -1 , sizeof(int) * (n << 1 | 1) ) ;
		}
		void pushdown( int rt , int l , int r ){
			int mid = l + r >> 1 ;
			int lc = rt << 1 , rc = lc | 1 ;
			add[lc] = add[rc] = add[rt] ;
			if( add[rt] )
				T[lc] = mid - l + 1 , T[rc] = r - mid ;
			else
				T[lc] = T[rc] = 0 ;
			add[rt] = -1 ;
		}
		void modify( int rt , int l , int r , int L , int R ){
			if( l >= L && r <= R )
				return T[rt] = r - l + 1 , add[rt] = 1 , void() ;
			if( add[rt] != -1 )pushdown( rt , l , r ) ;
			int mid = l + r >> 1 ;
			if( mid >= L )modify( rt << 1 , l , mid , L , R ) ;
			if( mid < R )modify( rt << 1 | 1 , mid + 1 , r , L , R ) ;
			T[rt] = T[rt << 1] + T[rt << 1 | 1] ;
		}
		void query( int rt , int l , int r , int L , int R ){
			if( l >= L && r <= R )
				return ans += T[rt] , T[rt] = 0 , add[rt] = 0 , void() ;
			if( add[rt] != -1 )pushdown( rt , l , r ) ;
			int mid = l + r >> 1 ;
			if( mid >= L )query( rt << 1 , l , mid , L , R ) ;
			if( mid < R )query( rt << 1 | 1 , mid + 1 , r , L , R ) ;
			T[rt] = T[rt << 1] + T[rt << 1 | 1] ;
		}
}T[8] ;

int main(){
	
	freopen( "c.in" , "r" , stdin ) ;
	freopen( "c.out" , "w" , stdout ) ;
	
	scanf( n ) ; scanf( q ) ;
	
	For( i , 1 , n )
		scanf( seq ) ,
		T[seq].modify( 1 , 1 , n , i , i ) ;
	
	register int l , r , opt , t ;
	while( q-- ){
		scanf( l ) ; scanf( r ) ; scanf( opt ) ;
		t = l ;
		for( int i = !opt ? 1 : 7 ; !opt ? i <= 7 : i >= 1 ; !opt ? ++i : --i ){
			ans = 0 ;
			T[i].query( 1 , 1 , n , l , r ) ;
			if( !ans )continue ;
			T[i].modify( 1 , 1 , n , t , t + ans - 1 ) ;
			t += ans ;
		}
	}
	For( i , 1 , n )
		For( j , 1 , 7 )
			if( ans = 0 , T[j].query( 1 , 1 , n , i , i ) , ans == 1 )
				{ putchar( j + '0' ) ; putchar( 32 ) ; break ; }
	putchar( 10 ) ;
	return 0 ;
}
