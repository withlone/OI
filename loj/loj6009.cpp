#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename type >inline void scanf( type &In ){
	In = 0;char ch = getchar();type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

static const int maxn = 20 + 1;
static const int maxm = 100 + 1;

int n;
int m;

int cost[maxm];

char B[maxm][maxn];
char F[maxm][maxn];

void read_in(){
	scanf( n ) ; scanf( m ) ;
	For( i , 1 , m )
		scanf( cost[i] ) , scanf( "%s%s" , B[i] , F[i] ) ;
}

int dis[1 << maxn];
bool V[1 << maxn];
int que[1 << maxn];

bool chk( int x , int y ){
	For( i , 0 , n - 1 )
		if( B[x][n - i - 1] == '-' && !( ( 1 << i ) & y ) )return false;
		else if( B[x][n - i - 1] == '+' && ( ( 1 << i ) & y ) )return false;
	return true;
}

int make( int x , int y ){
	For( i , 0 , n - 1 )
		if( F[x][n - i - 1] == '-' )y |= ( 1 << i );
		else if( F[x][n - i - 1] == '+' )y |= ( 1 << i ) , y ^= ( 1 << i );
	return y;
}

void spfa(){
	
	int tot = 1 << n;
	
	For( i , 0 , 1 << n )dis[i] = 1e9;
	
	int head = 0 , tail = -1;
	que[ ++tail ] = 0 ; dis[0] = 0 ;
	while( head != ( tail + 1 ) % tot ){
		int x = que[ head++ ];V[x] = false;
		if( head == tot )head = 0;
		For( i , 1 , m )
			if( chk( i , x ) ){
				int y = make( i , x );
				if( dis[y] > dis[x] + cost[i] ){
					dis[y] = dis[x] + cost[i];
					if( !V[y] ){
						V[y] = true;
						if( tail == tot - 1 )que[tail = 0] = y;
						else que[ ++tail ] = y;
					}
				}
			}
	}
	
	printf("%d\n" , dis[1 << n] ^ dis[ ( 1 << n ) - 1 ] ? dis[ ( 1 << n ) - 1 ] : 0 );
}

int main(){
	
	read_in();
	
	spfa();
	
	return 0;
}
