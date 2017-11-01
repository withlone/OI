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

static const int maxn = 5e2 + 10;
static const int maxm = 3e3 + 10;
static const int maxx = maxm << 1;

int n;
int m;
int q;
int cases;

int Ct;
int Ht[maxn];
int Nt[maxx];
int To[maxx];
int Dt[maxx];

bool V[maxn];
int dis[maxn];

void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = z;
}

void read_in(){
	scanf( n ) ; scanf( m ) ; scanf( q ) ;
	Ct = 0;
	For( i , 1 , n )Ht[i] = 0;
	For( i , 1 , m ){
		int x , y , z ;
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		Ins( x , y , z ) ; Ins( y , x , z ) ;
	}
	For( i , 1 , q ){
		int x , y , z ;
		scanf( x ) ; scanf( y ) ; scanf( z ) ;
		Ins( x , y , -z ) ;
	}
}

bool flag;

void spfa( int x ){
	V[x] = true;
	Rep( i , Ht[x] , Nt[i] ){
		int y = To[i];
		if( dis[y] > dis[x] + Dt[i] ){
			dis[y] = dis[x] + Dt[i];
			if( !V[y] )spfa( y );
			else flag = true;
			if( flag )return;
		}
	}
	V[x] = false;
}

bool dfs_spfa(){
	flag = false;
	For( i , 1 , n )dis[i] = V[i] = 0;
	For( i , 1 , n ){
		spfa( i );
		if( flag )return true;
	}
	return false;
}

int main(){
	
	scanf( cases );
	
	while( cases-- ){
		
		read_in();
		
		puts( dfs_spfa() ? "YES" : "NO" );
		
	}
	
	return 0;
}
