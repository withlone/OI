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
#define Lson rt << 1 , l , mid
#define Rson rt << 1 | 1 , mid + 1 , r
static const int maxn = 1e5 +1;
static const int maxm = maxn * 5;

int n , m , Cnt;
int A[maxn];

bool Rev[maxm];int tag[maxm] , tot[maxm];
LL sum[maxm][2] , Lmax[maxm][2] , Rmax[maxm][2] , mx[maxm][2];

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

void rever( int rt ){
	swap( sum[rt][0] , sum[rt][1] );
	swap( Lmax[rt][0] , Lmax[rt][1] );
	swap( Rmax[rt][0] , Rmax[rt][1] );
	swap( mx[rt][0] , mx[rt][1] );
}

void Change( int rt , int l , int r , int f ){
	sum[rt][f] = Lmax[rt][f] = Rmax[rt][f] = mx[rt][f] = r - l + 1;
	sum[rt][f ^ 1] = Lmax[rt][f ^ 1] = Rmax[rt][f ^ 1] = mx[rt][f ^ 1] = 0;
}

void Pd( int rt , int l , int r ){
	int mid = l + r >> 1;
	if( tag[rt] != -1 ){
		Change( rt << 1 , l , mid , tag[rt] );
		Change( rt << 1 | 1 , mid + 1 , r , tag[rt] );
		tag[ rt << 1 ] = tag[ rt << 1 | 1 ] = tag[rt];
		Rev[ rt << 1 ] = Rev[ rt << 1 | 1 ] = 0;
		tag[rt] = -1;
	}
	if( Rev[rt] ){
		if( tag[ rt << 1 ] != -1 )tag[ rt << 1 ] ^= 1;
		else Rev[ rt << 1 ] ^= 1;
		if( tag[ rt << 1 | 1 ] != -1 )tag[ rt << 1 | 1 ] ^= 1;
		else Rev[ rt << 1 | 1 ] ^= 1;
		rever( rt << 1 );rever( rt << 1 | 1 );
		Rev[rt] = 0;
	}
}

void modify( int rt , int l , int r , int L , int R , int f ){
	if( l > R || r < L )return;
	if( l >= L && r <= R ){
		tag[rt] = f;Rev[rt] = 0;
		Change( rt , l , r , f );
		return;
	}
	int mid = l + r >> 1;
	Pd( rt , l , r );
	modify( Lson , L , R , f );modify( Rson , L , R , f );
	Up( rt , rt << 1 , rt << 1 | 1 );
}

void Flip( int rt , int l , int r , int L , int R ){
	if( l > R || r < L )return;
	if( l >= L && r <= R ){
		if( tag[rt] != -1 )Change( rt , l , r , tag[rt] ^= 1 );
		else Rev[rt] ^= 1 , rever( rt );
		return;
	}
	int mid = l + r >> 1;
	Pd( rt , l , r );
	Flip( Lson , L , R );Flip( Rson , L , R );
	Up( rt , rt << 1 , rt << 1 | 1 );
}

int Query( int rt , int l , int r , int L , int R ){
	if( l > R || r < L )return 0;
	if( l >= L && r <= R )return rt;
	int mid = l + r >> 1;
	Pd( rt , l , r );
	return Up( ++Cnt , Query( Lson , L , R ) , Query( Rson , L , R ) );
}

void Build( int rt , int l , int r ){
	tag[rt] = -1;
	if( l == r )return tot[rt] = sum[rt][ A[l] ] = Lmax[rt][ A[l] ] = Rmax[rt][ A[l] ] = mx[rt][ A[l] ] = 1 , void();
	int mid = l + r >> 1;
	Build( Lson );Build( Rson );
	Up( rt , rt << 1 , rt << 1 | 1 );
}

int main(){
	
	Read( n );Read( m );
	For( i , 1 , n )Read( A[i] );
	Build( 1 , 1 , n );
	
	while( m-- ){
		int opt , x , y;
		Read( opt );Read( x );Read( y );x++;y++;Cnt = n << 2;
		if( opt <= 1 )modify( 1 , 1 , n , x , y , opt );
		else if( opt == 2 )Flip( 1 , 1 , n , x , y );
		else if( opt == 3 )printf("%lld\n",sum[ Query( 1 , 1 , n , x , y ) ][1]);
		else printf("%lld\n",mx[ Query( 1 , 1 , n , x , y ) ][1]);
	}
	
	return 0;
}
