#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename type >inline type max( type x , type y ){ return x > y ? x : y ; }
template< typename type >inline type min( type x , type y ){ return x < y ? x : y ; }
template< typename type >inline void swap( type &x , type &y ){ type t = x ; x = y ; y = t ; }
template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 1e6 + 10;

int n;
int max_x;
int min_x;
int min_y;
int max_y;

int ska[maxn][3];

void read_in(){
	scanf( n ) ;
	For( i , 1 , n )
		scanf( ska[i][0] ) , scanf( ska[i][1] ) , scanf( ska[i][2] ) ;
}

void get_ans(){
	min_x = min_y = ~0U >> 1;
	For( i , 1 , n ){
		bool f = ska[i][0] < ska[i][1] ;
		if( f )swap( ska[i][0] , ska[i][1] ) ;
		max_x = max( max_x , ska[i][0] ) ,
		min_x = min( min_x , ska[i][0] ) ,
		max_y = max( max_y , ska[i][1] ) ,
		min_y = min( min_y , ska[i][1] ) ;
		if( f )swap( ska[i][0] , ska[i][1] ) ;
	}
	printf("%lld" , 1LL * ( max_x - min_x + max_y - min_y ) << 1 );
}

bool at( int x )
{ return min_x <= ska[x][0] && ska[x][0] <= max_x && min_y <= ska[x][1] && ska[x][1] <= max_y ; }

LL ans = 1e15;
bool V[maxn];
bool M[maxn];

void work(){
	LL res = 0 ;
	For( i , 1 , n )
		if( !at( i ) ){
			swap( ska[i][0] , ska[i][1] ) ;
			if( !at( i ) )return swap( ska[i][0] , ska[i][1] ) ;
			swap( ska[i][0] , ska[i][1] ) ;
			res += ska[i][2];
			V[i] = true;
		}
		else V[i] = false;
	if( ans > res )
		ans = res , memcpy( M , V , sizeof M ) ;
}

void Run_cost(){
	work();
	swap( max_x , max_y ) ;
	work();
	swap( min_x , min_y ) ;
	work();
	swap( max_x , max_y ) ;
	work();
}

void display(){
	printf(" %lld\n" , ans ) ;
	For( i , 1 , n )
		putchar( '0' + M[i] );
	putchar( '\n' ) ;
}

int main(){
	
	freopen("ska.in","r",stdin);
	freopen("ska.out","w",stdout);
	
	read_in();
	
	get_ans();
	
	Run_cost();
	
	display();
	
	return 0;
}
