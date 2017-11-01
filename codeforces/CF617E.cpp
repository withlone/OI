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
static const int maxn = 1e5 +1;
static const int maxm = 11e5;

int n , m , k , Fac;
int A[maxn] , num[maxm];
LL ans[maxn];

struct Query{
	int l , r , id;
	bool operator < ( Query t ) const { return l/Fac < t.l/Fac || l/Fac == t.l/Fac && r < t.r; }
}Q[maxn];

int main(){
	
	Read( n );Read( m );Read( k );Fac = sqrt( n + 0.5 );
	For( i , 1 , n )Read( A[i] ) , A[i] ^= A[i - 1];
	For( i , 1 , m )Read( Q[i].l ) , Read( Q[i].r ) , Q[i].id = i , --Q[i].l;
	sort( 1 + Q , 1 + m + Q );
	
	int l = 0 , r = 0;num[0] = 1;LL sum = 0;
	For( i , 1 , m ){
		while( r < Q[i].r )++r , sum += num[ k ^ A[r] ] , ++num[ A[r] ];
		while( l > Q[i].l )--l , sum += num[ k ^ A[l] ] , ++num[ A[l] ];
		while( r > Q[i].r )--num[ A[r] ] , sum -= num[ k ^ A[r] ] , --r;
		while( l < Q[i].l )--num[ A[l] ] , sum -= num[ k ^ A[l] ] , ++l;
		ans[ Q[i].id ] = sum;
	}
	
	For( i , 1 , m )printf("%I64d\n",ans[i]);
	
	return 0;
}
