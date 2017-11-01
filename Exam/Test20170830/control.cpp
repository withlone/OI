#include<cstdio>

#define For( i , _begin , _end ) for( int i = (_begin) , i##end = (_end) ; i <= (i##end) ; i++ )

template< typename type >inline type max ( type x , type y ){ return x > y ? x : y ; }
template< typename type >inline type min ( type x , type y ){ return x < y ? x : y ; }
template< typename type >inline void swap( type&x , type&y ){ type t = x ; x = y ; y = t ; }
template< typename type >inline void scanf( type &in ){
	in = 0 ; char ch = getchar() ; type f = 1 ;
	for( ;ch > '9' || ch < '0' ; ch = getchar() )if( ch == '-' ) f = -1 ;
	for( ;ch >='0' && ch <='9' ; ch = getchar() )in = in * 10 + ch - '0' ; in *= f ;
}

static const int maxn = 1e3 + 10;

int n;

int A[maxn][maxn];

void read_in(){
	scanf( n ) ;
	For( i , 1 , n )For( j , 1 , n )
		scanf( A[i][j] ) ;
}

int F_play[maxn];
int S_play[maxn];

void F_time(){
	For( i , 1 , n ){
		F_play[i] = 1 ;
		For( j , 2 , n )
			if( A[i][F_play[i]] < A[i][j] )F_play[i] = j ;
		F_play[0] += A[i][F_play[i]];
	}
}

void S_time(){
	For( i , 1 , n ){
		S_play[i] = 1 ;
		For( j , 2 , n )
			if( A[S_play[i]][i] < A[j][i] )S_play[i] = j ;
		S_play[0] += A[S_play[i]][i];
	}
}

void Run(){
	F_time();
	S_time();
	if( F_play[0] > S_play[0] ){
		printf("%d\n" , F_play[0] ) ;
		For( i , 1 , n )printf("%d %d\n" , i , F_play[i] );
	}
	else{
		printf("%d\n" , S_play[0] ) ;
		For( i , 1 , n )printf("%d %d\n" , S_play[i] , i );
	}
}

int main(){
	
	freopen( "control.in" , "r" , stdin );
	freopen( "control.out" , "w" , stdout );
	
	read_in();
	
	Run();
	
	return 0;
}
