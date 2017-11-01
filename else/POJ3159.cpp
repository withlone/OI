#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

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

static const int maxn = 3e4 + 10;
static const int maxm = 15e4 + 10;

int n;
int m;

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
int Dt[maxm];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = z;
}

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , m ){
		int x , y , z ;
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		Ins( x , y , z ) ;
	}
}

struct par{
	int first , second;
	bool operator < ( par t ) const {
		return first == t.first ? second < t.second : first < t.first ; }
	bool operator > ( par t ) const {
		return first == t.first ? second > t.second : first > t.first ; }
};

par make_pair( int x , int y ){ return (par){ x , y } ; }

template< typename Type >inline void swap( Type &x , Type &y ){ Type t = x ; x = y ; y = t ; }
template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }

struct heap{
	
	int size;
	par T[maxm];
	
	void push( par t ){
		T[ ++size ] = t;
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
 	
 	int top(){ return T[1].second ; }
	
	bool empty(){ return !size ; }
	
	void clear(){ size = 0 ; }
	
}Hp;

void dijkstra(){
	Hp.clear();
	int dis[maxn];
	bool V[maxn];
	For( i , 1 , n )dis[i] = 1e9 , V[i] = false;
	dis[1] = 0;
	Hp.push( make_pair( 0 , 1 ) );
	while( !Hp.empty() ){
		int x = Hp.top();Hp.pop();
		if( V[x] )continue;
		V[x] = true;
		Rep( i , Ht[x] , Nt[i] ){
			int y = To[i];
			if( dis[y] > dis[x] + Dt[i] && !V[y] ){
				dis[y] = dis[x] + Dt[i];
				Hp.push( make_pair( dis[y] , y ) );
			}
		}
	}
	
	printf( dis[n] ) , putchar( '\n' );
}

int main(){
	
	read_in();
	
	dijkstra();
	
	return 0;
}
