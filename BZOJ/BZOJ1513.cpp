#include<cstdio>
#include<cstring>

template< typename Type >inline Type max ( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();
	for( ;ch> '9'||ch< '0';ch=getchar() );
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';
}

#define Lson rt << 1 , l , mid
#define Rson rt << 1 | 1 , mid + 1 , r
static const int maxm = 2048;

int D , S , m;

struct Segt1{
	
	int mx[maxm] , tag[maxm];
	
	Segt1(){ memset( mx , 0 , sizeof mx );memset( tag , 0 , sizeof tag ); }
	
	void modify( int rt , int l ,  int r , int L , int R , int val ){
		if( l > R || r < L )return;
		mx[rt] = max( mx[rt] , val );
		if( l >= L && r <= R )return tag[rt] = max( tag[rt] , val ) , void();
		int mid = l + r >> 1;
		modify( Lson , L , R , val );modify( Rson , L , R , val );
	}
	
	int Query( int rt , int l , int r , int L , int R ){
		if( l > R || r < L )return 0;
		if( l >= L && r <= R )return mx[rt];
		int mid = l + r >> 1;
		return max( max( Query( Lson , L , R ) , Query( Rson , L , R ) ) , tag[rt] );
	}
	
}T[maxm] , tag[maxm];

namespace Segt2{
	
	void modify( int rt , int l , int r , int L , int R , int LL , int RR , int val ){
		if( l > R || r < L )return;
		T[rt].modify( 1 , 0 , S , LL , RR , val );
		if( l >= L && r <= R )return tag[rt].modify( 1 , 0 , S , LL , RR , val );
		int mid = l + r >> 1;
		modify( Lson , L , R , LL , RR , val );modify( Rson , L , R , LL , RR , val );
	}
	
	int Query( int rt , int l , int r , int L , int R , int LL , int RR ){
		if( l > R || r < L )return 0;
		if( l >= L && r <= R )return T[rt].Query( 1 , 0 , S , LL , RR );
		int mid = l + r >> 1;
		return max( max( Query( Lson , L , R , LL , RR ) , Query( Rson , L , R , LL , RR ) ) , tag[rt].Query( 1 , 0 , S , LL , RR ) );
	}
	
}using namespace Segt2;

int main(){
	
	Read( D );Read( S );Read( m );
	
	while( m-- ){
		int d , s , w , x , y;
		Read( d );Read( s );Read( w );Read( x );Read( y );
		w += Query( 1 , 0 , D , x + 1 , x + d , y + 1 , y + s );
		modify( 1 , 0 , D , x + 1 , x + d , y + 1 , y + s , w );
	}
	
	printf("%d\n",T[1].mx[1]);
	
	return 0;
}
