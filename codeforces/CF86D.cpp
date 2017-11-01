#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

typedef long long LL;
static const int maxn = 2e5 +1;
static const int maxm = 1e6 +1;

int n , m , Fac;
int A[maxn] , num[maxm];
LL ans[maxn] , sum;

struct Query{
	int l , r , id;
	bool operator < ( Query t ) const { return l/Fac < t.l/Fac || l/Fac == t.l/Fac && r < t.r; }
}Q[maxn];

int main(){
	
	Read( n );Read( m );Fac = sqrt( n + 0.5 );
	For( i , 1 , n )Read( A[i] );
	For( i , 1 , m )Read( Q[i].l ) , Read( Q[i].r ) , Q[i].id = i;
	
	sort( 1 + Q , 1 + m + Q );
	
	int l = 1 , r = 0;
	For( i , 1 , m ){
		while( r < Q[i].r )++r , sum += 1LL * ( ( num[ A[r] ] << 1 ) + 1 ) * A[r] , ++num[ A[r] ];
		while( l > Q[i].l )--l , sum += 1LL * ( ( num[ A[l] ] << 1 ) + 1 ) * A[l] , ++num[ A[l] ];
		while( r > Q[i].r )sum -= 1LL * ( ( num[ A[r] ] << 1 ) - 1 ) * A[r] , --num[ A[r] ] , --r;
		while( l < Q[i].l )sum -= 1LL * ( ( num[ A[l] ] << 1 ) - 1 ) * A[l] , --num[ A[l] ] , ++l;
		ans[ Q[i].id ] = sum;
	}
	
	For( i , 1 , m )printf("%I64d\n",ans[i]);
	
	return 0;
}
