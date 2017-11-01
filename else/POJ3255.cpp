#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _Add ) for( int i = (_Begin) ; i ; i = (_Add) )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
typedef pair< int , int > par;
static const int maxn = 5e3 + 10;
static const int maxm = 1e5 + 10;

int n , m;
int A[maxm] , B[maxm] , C[maxm];

int H[maxn] , Nt[maxm << 1] , To[maxm << 1] , Dt[maxm << 1] , Ct;
void Ins( int x , int y , int z ){
	Nt[ ++Ct ] = H[x];
	H[x] = Ct;
	To[Ct] = y;
	Dt[Ct] = z;
}

struct heap{
	
	int size;
	par T[maxm];
	
	bool empty(){ return !size ; }
	
	void clear(){ memset( T , 0 , sizeof T ) ; size = 0 ; }
	
	void push( par x ){
		T[ ++size ] = x;
		int p = size;
		while( p != 1 && T[p] < T[p >> 1] ){
			swap( T[p] , T[p >> 1] );
			p >>= 1;
		}
	}
	
	par top(){ return T[1] ; }
	
	void pop(){
		T[1] = T[ size-- ];
		int p = 1;
		while( ( p << 1 ) <= size && T[p] > min( T[p << 1] , T[p << 1 | 1] ) ){
			int t = ( T[p << 1] < T[p << 1 | 1] ? p << 1 : p << 1 | 1 );
			swap( T[p] , T[t] );
			p = t;
		}
	}
	
}Hp;

bool V[maxn];
LL dis1[maxn] , disn[maxn];
void Dijkstra( int S , LL *dis ){
	For( i , 1 , n )dis[i] = 1e15 , V[i] = false;
	dis[S] = 0;
	Hp.clear();
	Hp.push( make_pair( 0 , S ) );
	while( !Hp.empty() ){
		int x = Hp.top().second;Hp.pop();
		V[x] = true;
		Rep( j , H[x], Nt[j] ){
			int y = To[j];
			if( V[y] || dis[y] < dis[x] + Dt[j] )continue;
			dis[y] = dis[x] + Dt[j];
			Hp.push( make_pair( dis[y] , y ) );
		}
	}
}

int main(){
	
	Read( n );Read( m );
	
	For( i , 1 , m ){
		int x , y , z;
		Read( x );Read( y );Read( z );
		Ins( x , y , z );Ins( y , x , z );
		A[i] = x;B[i] = y;C[i] = z;
	}
	
	Dijkstra( 1 , dis1 );
	Dijkstra( n , disn );
	
	LL ans = 1e15;
	For( i , 1 , m ){
		LL t1 = dis1[ A[i] ] + disn[ B[i] ] + C[i];
		LL t2 = dis1[ B[i] ] + disn[ A[i] ] + C[i];
		if( t1 > dis1[n] )ans = min( ans , t1 );
		if( t2 > disn[1] )ans = min( ans , t2 );
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
