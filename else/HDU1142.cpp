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

typedef long long LL;
static const int Inf = 2147483647;
static const int maxn = 1e3 + 10;
static const int maxm = maxn * maxn;

int n;
int m;

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
int Dt[maxm];

bool mp[maxn][maxn];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = z;
}

void read_in(){
	scanf( m );
	Ct = 0;
	For( i , 1 , n )Ht[i] = 0;
	For( i , 1 , n )For( j , 1 , n )mp[i][j] = 0;
	For( i , 1 , m ){
		int x , y , z ;
		scanf( "%d%d%d" , &x , &y , &z );
		Ins( x , y , z ) ; Ins( y , x , z ) ;
		mp[x][y] = mp[y][x] = true;
	}
}

struct par{ int f , s; };
bool operator < ( par x , par y ){ return x.f < y.f ; }
bool operator > ( par x , par y ){ return x.f > y.f ; }
par make_pair( int f , int s ){ return (par){ f , s } ; }

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
	
	int top(){ return T[1].s; }
	
	bool empty(){ return !size ; }
	
	void clear(){ size = 0 ; }
	
}Hp;

LL dis[maxn];bool V[maxn];
void dijkstra(){
	Hp.clear();
	For( i , 1 , n )V[i] = false , dis[i] = Inf;
	dis[2] = 0;
	Hp.push( make_pair( 0 , 2 ) );
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
}

void add_edge(){
	Ct = 0;
	For( i , 1 , n )Ht[i] = 0;
	For( i , 1 , n )
		For( j , 1 , n )
			if( dis[i] > dis[j] && mp[i][j] )Ins( i , j , 0 );
}

int F[maxn];
int Idg[maxn];

void Dfs( int x ){
	V[x] = true;
	Rep( i , Ht[x] , Nt[i] ){
		Idg[ To[i] ]++;
		if( !V[ To[i] ] )Dfs( To[i] );
	}
}

void tuopu(){
	int que[maxn] , H = 0 , T = -1;
	que[ ++T ] = 1;
	while( H <= T ){
		int x = que[ H++ ];
		Rep( i , Ht[x] , Nt[i] ){
			int y = To[i];
			if( !--Idg[y] )que[ ++T ] = y;
			F[y] += F[x];
		}
	}
}

void calc(){
	For( i , 1 , n )Idg[i] = V[i] = F[i] = 0;
	F[1] = 1;
	Dfs( 1 );
	tuopu();
	printf( F[2] ) , putchar( '\n' ) ;
}

int main(){
	
	while( scanf( n ) , n ){
		
		read_in();
		
		dijkstra();
		
		add_edge();
		
		calc();
		
	}
	
	return 0;
}
