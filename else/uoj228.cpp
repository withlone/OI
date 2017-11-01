#include<algorithm>
#include<cstdio>
#include<cmath>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##End = (_End) ; i <= (i##End) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

#define Lson rt<<1 , l , mid
#define Rson rt<<1|1 , mid + 1 , r
#define sqr( x ) ( int )sqrt( x )
typedef long long LL;
static const int maxn = 1e5 +1;
static const int maxm = maxn << 2;

int n , m;
int A[maxn];

LL sum[maxm] , mn[maxm] , mx[maxm] , Lazy[maxm];

LL Query( int , int , int , int , int );
void Up( int );
void Pd( int , int , int );
void Build( int , int , int );
void modify( int , int , int , int , int , int );

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Read( A[i] );
	Build( 1 , 1 , n );
	while( m-- ){
		int opt , l , r , x;
		Read( opt );Read( l );Read( r );
		if( opt == 1 )Read( x ) , modify( 1 , 1 , n , l , r , x );
		else if( opt == 2 )modify( 1 , 1 , n , l , r , 0 );
		else printf("%lld\n",Query( 1 , 1 , n , l , r ));
	}
	return 0;
}

void Up( int rt ){
	sum[rt] = sum[ rt<<1 ] + sum[ rt<<1|1 ];
	mn[rt] = min( mn[ rt<<1 ] , mn[ rt<<1|1 ] );
	mx[rt] = max( mx[ rt<<1 ] , mx[ rt<<1|1 ] );
}
void Pd( int rt , int L , int R ){
	int l = rt << 1 , r = rt << 1 | 1;
	Lazy[l] += Lazy[rt];Lazy[r] += Lazy[rt];
	mn[l] += Lazy[rt];mn[r] += Lazy[rt];
	mx[l] += Lazy[rt];mx[r] += Lazy[rt];
	sum[l] += L * Lazy[rt];sum[r] += R * Lazy[rt];
	Lazy[rt] = 0;
}
void Build( int rt , int l , int r ){
	if( l == r ){
		sum[rt] = mn[rt] = mx[rt] = A[l];
		return;
	}
	int mid = l + r >> 1;
	Build( Lson );Build( Rson );
	Up( rt );
}
void modify( int rt , int l , int r , int L , int R , int k ){
	if( l > R || r < L )return;
	if( l >= L && r <= R ){
		bool f = 0;LL tmp;
		if( k )f = 1 , tmp = k;
		else if( mx[rt] - mn[rt] == sqr( mx[rt] ) - sqr( mn[rt] ) )f = 1 , tmp = sqr( mx[rt] ) - mx[rt];
		if( f ){
			sum[rt] += ( r - l + 1 ) * tmp;
			mn[rt] += tmp;mx[rt] += tmp;
			Lazy[rt] += tmp;
			return;
		}
	}
	int mid = l + r >> 1;
	if( Lazy[rt] )Pd( rt , mid - l + 1 , r - mid );
	modify( Lson , L , R , k );modify( Rson , L , R , k );
	Up( rt );
}
LL Query( int rt , int l , int r , int L , int R ){
	if( l > R || r < L )return 0;
	if( l >= L && r <= R )return sum[rt];
	int mid = l + r >> 1;
	if( Lazy[rt] )Pd( rt , mid - l + 1 , r - mid );
	return Query( Lson , L , R ) + Query( Rson , L , R );
}
