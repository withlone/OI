#include<cstdio>
#include<algorithm>

using namespace std;

#define Lson rt << 1 , l , mid
#define Rson rt << 1 | 1 , mid + 1 , r
#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

static const int maxn = 2e5 +1;
static const int maxm = maxn * 5;

int n , m , Cnt;

int tag[maxm] , sum[maxm][2] , Lmax[maxm][2] , Rmax[maxm][2] , mx[maxm][2] , tot[maxm];

int Up( int rt , int l , int r ){
	if( !( l * r ) )return l ^ r;
	tot[rt] = tot[l] + tot[r];
	For( i , 0 , 1 ){
		sum[rt][i] = sum[l][i] + sum[r][i];
		Lmax[rt][i] = Lmax[l][i] + ( Lmax[l][i] == tot[l] ) * Lmax[r][i];
		Rmax[rt][i] = Rmax[r][i] + ( Rmax[r][i] == tot[r] ) * Rmax[l][i];
		mx[rt][i] = max( max( mx[l][i] , mx[r][i] ) , Rmax[l][i] + Lmax[r][i] );
	}
	return rt;
}

void Change( int rt , int l , int r , int f ){
	sum[rt][f] = Lmax[rt][f] = Rmax[rt][f] = mx[rt][f] = r - l + 1;
	sum[rt][f ^ 1] = Lmax[rt][f ^ 1] = Rmax[rt][f ^ 1] = mx[rt][f ^ 1] = 0;
}

void Pd( int rt , int l , int r ){
	int mid = l + r >> 1 , ls = rt << 1 , rs = rt << 1 | 1;
	tag[ls] = tag[rs] = tag[rt];
	Change( ls , l , mid , tag[rt] );
	Change( rs , mid + 1 , r , tag[rt] );
	tag[rt] = -1;
}

void pushdown( int rt , int l , int r , int &num ){
	if( !num )return;
	if( l == r )return Change( rt , l , r  , 0 );
	int mid = l + r >> 1;
	if( tag[rt] != -1 )Pd( rt , l , r );
	if( sum[ rt << 1 ][1] <= num )tag[rt << 1] = 0 , num -= sum[ rt << 1 ][1] , Change( Lson , 0 ) , pushdown( Rson , num );
	else pushdown( Lson , num );
	Up( rt , rt << 1 , rt << 1 | 1 );
}

void modify( int rt , int l , int r , int L , int R , int f ){
	if( l > R || r < L )return;
	if( l >= L && r <= R )return tag[rt] = f , Change( rt , l , r , f );
	int mid = l + r >> 1;
	if( tag[rt] != -1 )Pd( rt , l , r );
	modify( Lson , L , R , f );modify( Rson , L , R , f );
	Up( rt , rt << 1 , rt << 1 | 1 );
}

void modify_add( int rt , int l , int r , int L , int R , int &num ){
	if( l > R || r < L || !num )return;
	if( l >= L && r <= R ){
		if( num >= sum[rt][1] )num -= sum[rt][1] , tag[rt] = 0 , Change( rt , l , r , 0 );
		else pushdown( rt , l , r , num );
		return;
	}
	int mid = l + r >> 1;
	if( tag[rt] != -1 )Pd( rt , l , r );
	modify_add( Lson , L , R , num );modify_add( Rson , L , R , num );
	Up( rt , rt << 1 , rt << 1 | 1 );
}

int Query( int rt , int l , int r , int L , int R ){
	if( l > R || r < L )return 0;
	if( l >= L && r <= R )return rt;
	int mid = l + r >> 1;
	if( tag[rt] != -1 )Pd( rt , l , r );
	return Up( ++Cnt , Query( Lson , L , R ) , Query( Rson , L , R ) );
}

void Build( int rt , int l , int r ){
	tag[rt] = -1;
	if( l == r )return tot[rt] = 1 , Change( rt , l , r , 0 ) , void();
	int mid = l + r >> 1;
	Build( Lson );Build( Rson );
	Up( rt , rt << 1 , rt << 1 | 1 );
}

int main(){
	
	Read( n );Read( m );
	Build( 1 , 1 , n );
	
	while( m-- ){
		int opt , l0 , l1 , r0 , r1;
		Read( opt );Read( l0 );Read( r0 );Cnt = n << 2;
		if( !opt )modify( 1 , 1 , n , l0 , r0 , 1 );
		else if( opt == 1 ){
			Read( l1 );Read( r1 );
			int num = sum[ Query( 1 , 1 , n , l0 , r0 ) ][0];
			modify( 1 , 1 , n , l0 , r0 , 1 );
			if( !num )continue;
			modify_add( 1 , 1 , n , l1 , r1 , num );
		}
		else printf("%d\n",mx[ Query( 1 , 1 , n , l0 , r0 ) ][1]);
	}
	
	return 0;
}
