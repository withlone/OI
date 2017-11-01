#include<cstdio>

#define For( i , _begin , _end ) for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )
#define Lop( i , _begin , _end ) for( int i = (_begin) , i##end = (_end) ; i >= (i##end) ; i-- )

template< typename type >inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >inline void scanf( type &in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch > '9' || ch < '0' ; ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch >='0' && ch <='9' ; ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

static const int maxn = 1e6 + 10;
static const int maxm = maxn << 1;

int n;

int A[maxn];
int B[maxn];

void read_in(){
	scanf( n ) ;
	For( i , 1 , n )
		scanf( A[i] ) ;
	For( i , 1 , n )
		scanf( B[i] ) ;
}

int pos[maxn];
int que[maxm];

void preparation(){
	For( i , 1 , n )
		pos[ B[i] ] = i ;
	For( i , 0 , n )
		que[i] = n - i ;
}

void Run(){
	int head = 0 , tail = n ;
	Lop( i , n , 1 ){
		int t = pos[ A[i] ] ;++head ;
		que[ head + t - 1 ] = min( que[ head + t - 2 ] , que[ head + t ] + 1 );
		++tail;
	}
	printf("%d\n" ,  que[head] + n );
}

int main(){
	
	freopen( "permu.in" , "r" , stdin );
	freopen( "permu.out" , "w" , stdout );
	
	read_in();
	
	preparation();
	
	Run();
	
	return 0;
}
