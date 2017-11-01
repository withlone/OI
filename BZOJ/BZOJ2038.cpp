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
static const int maxn = 5e4 +1;

int n , m , Fac;
int A[maxn] , num[maxn];
LL sum , ans[2][maxn];

struct Query{
	int l , r , id;
	bool operator < ( Query tmp ) const { return l / Fac < tmp.l / Fac || l / Fac == tmp.l / Fac && r < tmp.r ; }
}Q[maxn];

LL Sqr( LL x ){ return x * ( x - 1 ) >> 1 ; }

void modify( int x , int f ){
	sum -= Sqr( num[ A[x] ] );
	num[ A[x] ] += f;
	sum += Sqr( num[ A[x] ] );
}

LL Gcd( LL x , LL y ){ return !y ? x : Gcd( y , x % y ) ; }

int main(){
	
	Read( n );Read( m );Fac = ( int )sqrt( n + 0.5 );
	For( i , 1 , n )Read( A[i] );
	For( i , 1 , m )Read( Q[i].l ) , Read( Q[i].r ) , Q[i].id = i;
	
	sort( 1 + Q , 1 + m + Q );
	
	int l = 1 , r = 0;
	For( i , 1 , m ){
		while( r < Q[i].r )modify( ++r , 1 );
		while( l > Q[i].l )modify( --l , 1 );
		while( r > Q[i].r )modify( r-- , -1 );
		while( l < Q[i].l )modify( l++ , -1 );
		ans[0][ Q[i].id ] = sum;ans[1][ Q[i].id ] = ( LL )( r - l + 1 ) * ( r - l ) >> 1;
		LL gcd = Gcd( ans[0][ Q[i].id ] , ans[1][ Q[i].id ] );
		ans[0][ Q[i].id ] /= gcd;ans[1][ Q[i].id ] /= gcd;
	}
	
	For( i , 1 , m )printf("%lld/%lld\n",ans[0][i],ans[1][i]);
	
	return 0;
}
