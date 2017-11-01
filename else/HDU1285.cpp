#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void swap( Type &x , Type &y ){ Type t = x ; x = y ; y = t ; }
template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}
template< typename Type >inline void printf( Type x ){
	if( x < 0 )putchar( '-' ) , x = -x;
	if( x > 9 )printf( x / 10 );
	putchar( x % 10 + '0' );
}

static const int maxn = 500 + 10;
static const int maxm = maxn * maxn;

int n;
int m;

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
}

int Idg[maxn];

void read_in(){
	Ct = 0;
	For( i , 1 , n )Idg[i] = Ht[i] = 0;
	For( i , 1 , m ){
		int x , y ;
		scanf( x ) ; scanf( y ) ;
		Ins( x , y ) ; Idg[y]++ ;
	}
}

struct heap{
	
	int size;
	int T[maxn];
	
	void push( int x ){
		T[ ++size ] = x;
		int p = size;
		while( p != 1 && T[p] < T[p >> 1] ){
			swap( T[p] , T[p >> 1] );
			p >>= 1;
		}
	}
	
	void pop(){
		T[1] = T[ size-- ];
		int p = 1;
		while( ( p << 1 ) <= size && T[p] > min( T[p << 1] , T[p << 1 | 1] ) ){
			int t = T[p << 1] < T[p << 1 | 1] ? p << 1 : p << 1 | 1;
			swap( T[p] , T[t] );
			p = t;
		}
	}
	
	int top(){ return T[1] ; }
	
	bool empty(){ return !size ; }
	
	void clear(){ size = 0 ; }
	
}Hp;

void tuopu(){
	Hp.clear();int cnt = 0;
	For( i , 1 , n )if( !Idg[i] )Hp.push( i );
	while( !Hp.empty() ){
		int x = Hp.top();Hp.pop();
		printf( x ) , putchar( ++cnt == n ? '\n' : ' ' );
		Rep( i , Ht[x] , Nt[i] )
			if( !--Idg[ To[i] ] )Hp.push( To[i] );
	}
}

int main(){
	
	while( scanf( "%d%d" , &n , &m ) != EOF ){
		
		read_in();
		
		tuopu();
		
	}
	
	return 0;
}
