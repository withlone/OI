#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline Type max( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline void scanf( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch = getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch = getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 1e5 + 10;
static const int maxm = 1e6 + 10;

int n;
int m;
int val[maxn];

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
int Idg[maxn];
int Odg[maxn];

void Ins( int x , int y ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Odg[x]++ ; Idg[y]++;
}

void read_in(){
	Ct = 0;
	For( i , 1 , n )scanf( val[i] ) , Odg[i] = Ht[i] = Idg[i] = 0;
	For( i , 1 , m ){
		int x , y ;
		scanf( x ) ; scanf( y ) ;
		Ins( x , y ) ;
	}
}

LL tuopu(){
	int que[maxn] , H = 0 , T = -1;
	LL F[maxn];
	For( i , 1 , n )F[i] = -1e13;
	For( i , 1 , n )if( !Idg[i] )F[ que[ ++T ] = i ] = 0;
	while( H <= T ){
		int x = que[ H++ ];
		F[x] += val[x];
		Rep( i , Ht[x] , Nt[i] ){
			int y = To[i];
			if( !--Idg[y] )que[ ++T ] = y;
			F[y] = max( F[y] , F[x] );
		}
	}
	LL res = -1e13;
	For( i , 1 , n )if( !Odg[i] )res = max( res , F[i] );
	return res;
}

int main(){
	
	while( scanf( "%d%d" , &n , &m ) != EOF ){
		
		read_in();
		
		printf("%lld\n" , tuopu() );
		
	}
	
	return 0;
}
