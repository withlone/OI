#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

typedef long long LL;
#define Lson rt << 1 , l , mid
#define Rson rt << 1 | 1 , mid + 1 , r
static const int maxn = 4e5 +1;

int n , m;
int mx[maxn] , mn[maxn];
LL sum[maxn] , Lazy[maxn];

void Up( int rt ){
	sum[rt] = sum[ rt << 1 ] + sum[ rt << 1 | 1 ];
	mx[rt] = max( mx[ rt << 1 ] , mx[ rt << 1 | 1 ] );
	mn[rt] = min( mn[ rt << 1 ] , mn[ rt << 1 | 1 ] );
}

void Pd( int rt , int L , int R ){
	int l = rt << 1 , r = rt << 1 | 1;
	mx[l] = mn[l] = mx[r] = mn[r] = Lazy[l] = Lazy[r] = Lazy[rt];
	sum[l] = Lazy[rt] * L;sum[r] = Lazy[rt] * R;
	Lazy[rt] = -1;
}

void Build( int rt , int l , int r ){
	Lazy[rt] = -1;
	if( l == r ){
		int x;Read( x );
		sum[rt] = mx[rt] = mn[rt] = x;
		return;
	}
	int mid = l + r >> 1;
	Build( Lson );Build( Rson );
	Up( rt );
}

void modify_mod( int rt , int l , int r , int L , int R , int k ){
	if( l > R || r < L || mx[rt] < k )return;
	if( l >= L && r <= R && mx[rt] == mn[rt] ){
		mx[rt] = mn[rt] = Lazy[rt] = mx[rt] % k;
		sum[rt] = ( r - l + 1 ) * Lazy[rt];
		return;
	}
	int mid = l + r >> 1;
	if( Lazy[rt] != -1 )Pd( rt , mid - l + 1 , r - mid );
	modify_mod( Lson , L , R , k );modify_mod( Rson , L , R , k );
	Up( rt );
}

void modify( int rt , int l , int r , int x , int y ){
	if( l == r ){
		sum[rt] = mx[rt] = mn[rt] = y;
		return;
	}
	int mid = l + r >> 1;
	if( Lazy[rt] != -1 )Pd( rt , mid - l + 1 , r - mid );
	if( x <= mid )modify( Lson , x , y );else modify( Rson , x , y );
	Up( rt );
}

LL Query( int rt , int l , int r , int L , int R ){
	if( l > R || r < L )return 0;
	if( l >= L && r <= R )return sum[rt];
	int mid = l + r >> 1;
	if( Lazy[rt] != -1 )Pd( rt , mid - l + 1 , r - mid );
	return Query( Lson , L , R ) + Query( Rson , L , R );
}

int main(){
	
	Read( n );Read( m );
	Build( 1 , 1 , n );
	
	while( m-- ){
		int opt , l , r , x;
		Read( opt );Read( l );Read( r );
		if( opt == 1 )printf("%lld\n",Query( 1 , 1 , n , l , r ));
		else if( opt == 2 )Read( x ) , modify_mod( 1 , 1 , n , l , r , x );
		else modify( 1 , 1 , n , l , r );
	}
	
	return 0;
}
