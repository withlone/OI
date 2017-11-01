#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

typedef long long LL;
static const int MAXN = 1e5 +1;
static const int mod = 1e9 +7;

int n , m;
int A[MAXN];

struct matrix{
	LL s[2][2];
	
	matrix(){ s[0][0] = s[0][1] = s[1][0] = s[1][1] = 0; }
	
	matrix operator + ( matrix x ){
		matrix c;
		For( i , 0 , 1 )For( j , 0 , 1 )
			c.s[i][j] = ( s[i][j] + x.s[i][j] ) % mod;
		return c;
	}
	matrix operator * ( matrix x ){
		matrix c;
		For( i , 0 , 1 )For( j , 0 , 1 )For( k , 0 , 1 )
			( c.s[i][j] += s[i][k] * x.s[k][j] % mod ) %= mod;
		return c;
	}
	matrix operator *=( matrix x ){
		*this = *this * x;
		return *this;
	}
	matrix operator ^ ( int x ){
		matrix c = *this , d = *this;
		for( --x; x ; x >>= 1 , c *= c )
			if( x & 1 )d *= c;
		return d;
	}
	matrix operator ^=( int x ){
		*this = *this ^ x;
		return *this;
	}
	
	bool operator != ( matrix x ){
		For( i , 0 , 1 )For( j , 0 , 1 )
			if( s[i][j] != x.s[i][j] )return true;
		return false;
	}
	
}mat[MAXN << 2] , base;

namespace Segment_tree{
	
	matrix Lz[MAXN << 2];
	#define Lson rt<<1 , l , mid
	#define Rson rt<<1|1 , mid + 1 , r
	
	void Up( int rt ){ mat[rt] = mat[ rt<<1 ] + mat[ rt<<1|1 ]; }
	void Pd( int rt ){
		Lz[ rt<<1 ] *= Lz[rt];Lz[ rt<<1|1 ] *= Lz[rt];
		mat[ rt<<1 ] *= Lz[rt];mat[ rt<<1|1 ] *= Lz[rt];
		Lz[rt].s[0][0] = Lz[rt].s[1][1] = 1;
		Lz[rt].s[0][1] = Lz[rt].s[1][0] = 0;
	}
	
	void Build( int rt , int l , int r ){
		mat[rt].s[0][1] = 1;
		Lz[rt].s[0][0] = Lz[rt].s[1][1] = 1;
		Lz[rt].s[0][1] = Lz[rt].s[1][0] = 0;
		if( l == r ){ mat[rt] *= base ^ A[l];return; }
		int mid = l + r >> 1;
		Build( Lson );Build( Rson );
		Up( rt );
	}
	
	void modify( int rt , int l , int r , int L , int R , matrix k ){
		if( l > R || r < L )return;
		if( l >= L && r <= R ){
			Lz[rt] *= k;
			mat[rt] *= k;
			return;
		}
		int mid = l + r >> 1;
		if( Lz[rt] != mat[0] )Pd( rt );
		modify( Lson , L , R , k );modify( Rson , L , R , k );
		Up( rt );
	}
	
	int Query( int rt , int l , int r , int L , int R ){
		if( l > R || r < L )return 0;
		if( l >= L && r <= R )return mat[rt].s[0][0];
		int mid = l + r >> 1;
		if( Lz[rt] != mat[0] )Pd( rt );
		return ( Query( Lson , L , R ) + Query( Rson , L , R ) ) % mod;
	}
	
}using namespace Segment_tree;

int main(){
	
	base.s[0][1] = base.s[1][0] = base.s[1][1] = 1;
	
	Read( n );Read( m );
	For( i , 1 , n )Read( A[i] );
	
	Build( 1 , 1 , n );
	
	while( m-- ){
		int opt , l , r , x;
		Read( opt );Read( l );Read( r );
		if( opt == 1 )Read( x ) , modify( 1 , 1 , n , l , r , base ^ x );
		else printf("%d\n",Query( 1 , 1 , n , l , r ));
	}
	
	return 0;
}
