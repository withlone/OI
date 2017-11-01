#include<cstdio>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )
#define Rep( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i >= (i##END) ; i-- )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In*10 + ch-'0';
}

#define Lson rt << 1 , l , mid
#define Rson rt << 1 | 1 , mid + 1 , r
typedef long long LL;
static const int maxm = 2e5 +1;

int n , m , Ct;LL p , c;
LL A[maxm] , mod[maxm];

LL sum[maxm] , aux[maxm];

LL Get_mod( LL );
LL pow( LL , LL , LL );
LL calc( LL , LL );
LL Query( int , int , int , int , int );
void Up( int );
void Build( int , int , int );
void modify( int , int , int , int , int );

int main(){
	
	Read( n );Read( m );Read( p );Read( c );
	For( i , 1 , n )Read( A[i] );
	
	mod[0] = p;
	for( ;p != 1; p = mod[ Ct ] )mod[ ++Ct ] = Get_mod( p );
	mod[ ++Ct ] = 1;
	
	Build( 1 , 1 , n );
	
	while( m-- ){
		int opt , x , y;
		Read( opt );Read( x );Read( y );
		if( !opt )modify( 1 , 1 , n , x , y );
		else printf("%lld\n",Query( 1 , 1 , n , x , y ));
	}
	
	return 0;
}

LL Get_mod( LL x ){
	LL Res = x;
	for( int i = 2 ; i * i <= x ; i++ ){
		if( x % i )continue;
		Res = Res / i * ( i - 1 );
		while( !( x % i ) )x /= i;
	}
	if( x != 1 )Res = Res / x * ( x - 1 );
	return Res;
}

LL pow( LL x , LL y , LL Mod ){
	LL Res = 1;
	for( ; y ; y >>= 1 , x = ( x * x ) % Mod )
		if( y & 1 )Res = ( Res * x ) % Mod;
	return Res;
}

LL calc( LL x , LL y ){
	LL Res = y;
	Rep( i , x , 1 ){
		if( Res > mod[i] )Res = Res % mod[i] + mod[i];
		Res = pow( c , Res , mod[i-1] );
		if( !Res )Res += mod[i-1];
	}
	return Res % mod[0];
}

void Up( int rt ){
	sum[rt] = ( sum[ rt<<1 ] + sum[ rt<<1|1 ] ) % mod[0];
	aux[rt] = min( aux[ rt<<1 ] , aux[ rt<<1|1 ] );
}

void Build( int rt , int l , int r ){
	if( l == r )return sum[rt] = A[l] % mod[0] , void();
	int mid = l + r >> 1;
	Build( Lson );Build( Rson );
	Up( rt );
}

void modify( int rt , int l , int r , int L , int R ){
	if( l > R || r < L || aux[rt] >= Ct )return;
	if( l == r )return sum[rt] = calc( ++aux[rt] , A[l] ) , void();
	int mid = l + r >> 1;
	modify( Lson , L , R );modify( Rson , L , R );
	Up( rt );
}

LL Query( int rt , int l , int r , int L , int R ){
	if( l > R || r < L )return 0;
	if( l >= L && r <= R )return sum[rt];
	int mid = l + r >> 1;
	return ( Query( Lson , L , R ) + Query( Rson , L , R ) ) % mod[0];
}
