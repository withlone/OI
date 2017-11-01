#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type max( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline Type min( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void swap( Type &x , Type &y ){ Type t = x ; x = y ; y = t ; }
template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 300 + 10;
static const int maxm = maxn * maxn;

int n;
int m;
int S1;
int T1;
int S2;
int T2;

int mp[maxn][maxn];

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
int Dt[maxm];

int dis1[maxn];
int dis2[maxn];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = z;
}

void read_in(){
	Ct = 0;
	memset( mp , 0 , sizeof mp );
	memset( Ht , 0 , sizeof(int) * ( n + 1 ) );
	For( i , 1 , m ){
		int x , y , z;
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		if( !mp[x][y] || mp[x][y] > z )
			mp[x][y] = mp[y][x] = z;
	}
	For( i , 1 , n )For( j , 1 , n )
		if( mp[i][j] )Ins( i , j , mp[i][j] );
	scanf( S1 ) ; scanf( T1 ) ; scanf( S2 ) ; scanf( T2 ) ;
}

template< class type >
class priority_queue{
	
	public :
		int size;
		type T[maxm];
		
		priority_queue(){ size = 0 ; }
		
		bool empty(){ return !size ; }
		
		type top(){ return T[1] ; }
		
		void push( type x ){
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
			while( ( p << 1 ) <= size && min( T[p << 1] , T[p << 1 | 1] ) < T[p] ){
				int t = T[p << 1] < T[p << 1 | 1] ? p << 1 : p << 1 | 1;
				swap( T[p] , T[t] );
				p = t;
			}
		}
	
};

class par{
	
	public :
		int first;
		int second;
		
		par(){ first = second = 0 ; }
		par( int a , int b ){ first = a ; second = b ; }
		
		bool operator < ( par t ) const { return first < t.first ; }
	
};

par make_pair( int first , int second ){ return (par){ first , second } ; }

bool V[maxn];
priority_queue< par >que;

void spfa( int S , int *dis ){
	while( !que.empty() )que.pop();
	memset( V , 0 , sizeof( int ) * ( n + 1 ) );
	memset( dis , 0x3f , sizeof( int ) * ( n + 1 ) );
	que.push( make_pair( dis[S] = 0 , S ) );
	while( !que.empty() ){
		int x = que.top().second;que.pop();
		if( V[x] )continue;
		V[x] = true;
		Rep( i , Ht[x] , Nt[i] ){
			int y = To[i];
			if( dis[y] > dis[x] + Dt[i] && !V[y] ){
				dis[y] = dis[x] + Dt[i];
				que.push( make_pair( dis[y] , y ) );
			}
		}
	}
}

int F[maxn][maxn];

int Dfs( int x , int y ){
	if( F[x][y] != -1 )return F[x][y];
	int t = 0;
	Rep( i , Ht[x] , Nt[i] )if( dis1[ x ] - dis1[ To[i] ] == Dt[i] )
		t = max( t , Dfs( To[i] , y ) );
	Rep( i , Ht[y] , Nt[i] )if( dis2[ y ] - dis2[ To[i] ] == Dt[i] )
		t = max( t , Dfs( x , To[i] ) );
	return F[x][y] = t + ( x == y ) ;
}

int main(){
	
	while( scanf( n ) , scanf( m ) , n + m ){
		
		read_in();
		
		spfa( S1 , dis1 );
		
		spfa( S2 , dis2 );
		
		memset( F , -1 , sizeof F );
		
		F[S1][S2] = ( S1 == S2 );
		
		printf("%d\n" , Dfs( T1 , T2 ) );
		
	}
	
	return 0;
}
