#include<cstdio>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

typedef double DB;
static const int maxn = 100 + 10;
static const int maxm = maxn << 1;
static const int maxx = 1e5 + 10;
static const DB eps = 1e-10;

DB abs( DB x ){ return x > 0 ? x : -x ; }
int cmp( DB x , DB y ){ return abs( x - y ) < eps ? 0 : x - y > 0 ? 1 : -1 ; }

int n;
int m;
int S;
DB Vt;

int Ct;
int Ht[maxn];
int Nt[maxm];
int To[maxm];
DB Rt[maxm];
DB Cn[maxm];

void Ins( int x , int y , DB p , DB q ){
	Nt[ ++Ct ] = Ht[x];
	Ht[x] = Ct;
	To[Ct] = y;
	Rt[Ct] = p;
	Cn[Ct] = q;
}

void read_in(){
	scanf( "%d%d%d%lf" , &n , &m , &S , &Vt );
	For( i , 1 , m ){
		int x , y;DB p , q;
		scanf( "%d%d%lf%lf" , &x , &y , &p , &q );
		Ins( x , y , p , q );
		scanf( "%lf%lf" , &p , &q );
		Ins( y , x , p , q );
	}
}

DB dis[maxn];
bool V[maxn];
int in[maxn];

bool spfa(){
	int que[maxn] , H = 0 , T = -1;
	que[ ++T ] = S;
	dis[S] = Vt;
	while( H != ( T + 1 ) % n ){
		int x = que[ H++ ] ;V[x] = false;
		if( H == n )H = 0;
		Rep( i , Ht[x] , Nt[i] ){
			int y = To[i];
			if( -1 == cmp( dis[y] , ( dis[x] - Cn[i] ) * Rt[i] ) ){
				dis[y] = ( dis[x] - Cn[i] ) * Rt[i];
				if( !V[y] ){
					if( ++in[y] > n )return true;
					V[y] = true;
					if( T == n - 1 )que[T = 0] = y;
					else que[ ++T ] = y;
				}
			}
		}
	}
	DB ans = 0;
	For( i , 1 , n )if( i != S && cmp( ans , dis[i] ) == 1 )
		ans = dis[i];
	return cmp( ans , dis[S] ) == 1;
}

int main(){
	
	read_in();
	
	puts( spfa() ? "YES" : "NO" ) ;
	
	return 0;
}
