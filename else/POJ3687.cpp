#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type max( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline void swap( Type &x , Type &y ){ Type t = x ; x = y ; y = t ; }
template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 200 + 10;
static const int maxm = 4e4 + 10;

int n;
int m;
int cases;

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];

int Idg[maxn];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Idg[y]++;
}

void read_in(){
	scanf( n ) ; scanf( m ) ;
	Ct = 0;
	For( i , 1 , n )Ht[i] = Idg[i] = 0;
	For( i , 1 , m ){
		int x , y ;
		scanf( x ) ; scanf( y ) ;
		Ins( y , x );
	}
}

struct heap{
	
	int size;
	int T[maxm];
	
	void push( int x ){
		T[ ++size ] = x;
		int p = size;
		while( p != 1 && T[p] > T[p >> 1] ){
			swap( T[p] , T[p >> 1] );
			p >>= 1;
		}
	}
	
	void pop(){
		T[1] = T[ size-- ];
		int p = 1;
		while( ( p << 1 ) <= size && T[p] < max( T[p << 1] , T[p << 1 | 1] ) ){
			int t = T[p << 1] > T[p << 1 | 1] ? p << 1 : p << 1 | 1;
			swap( T[p] , T[t] );
			p = t;
		}
	}
	
	int top(){ return T[1] ; }
	
	bool empty(){ return !size ; }
	
	void clear(){ size = 0 ; }
	
}Hp;

bool tuopu(){
	int seq[maxn] , cnt = 0;
	Hp.clear();
	For( i , 1 , n )if( !Idg[i] )Hp.push( i );
	while( !Hp.empty() ){
		int x = Hp.top();Hp.pop();
		seq[x] = ++cnt;
		Rep( i , Ht[x] , Nt[i] )
			if( !--Idg[ To[i] ] )Hp.push( To[i] );
	}
	if( cnt != n )return false;
	For( i , 1 , n )printf("%d%c", n - seq[i] + 1 , i == n ? '\n' : ' ' );
	return true;
}

int main(){
	
	scanf( cases );
	
	while( cases-- ){
		
		read_in();
		
		if( !tuopu() )puts("-1");
		
	}
	
	return 0;
}
