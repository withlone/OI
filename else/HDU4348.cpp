#include<cstdio>
#include<cstring>

#define For( i , _Begin , _End ) for( int i = (_Begin) , i##END = (_End) ; i <= (i##END) ; i++ )

template< typename Type >inline Type max ( Type x , Type y ){ return x > y ? x : y ; }
template< typename Type >inline Type min ( Type x , Type y ){ return x < y ? x : y ; }
template< typename Type >inline void Read( Type &In ){
	In = 0;char ch = getchar();Type f = 1;
	for( ;ch> '9'||ch< '0';ch=getchar() )if( ch == '-' ) f = -1;
	for( ;ch>='0'&&ch<='9';ch=getchar() )In = In * 10 + ch - '0';In *= f;
}

typedef long long LL;
static const int maxn = 1e5 +1;
static const int maxx = 3e6;

int n , m;
int A[maxn];

namespace president_tree{
	
	int Cnt;
	int root[maxn] , Ch[maxx][2] , add[maxx];
	LL sum[maxx];
	
	#define Lson Ch[rt][0] , l , mid
	#define Rson Ch[rt][1] , mid + 1 , r
	
	void Up( int rt , int len ){ sum[rt] = sum[ Ch[rt][0] ] + sum[ Ch[rt][1] ] + (LL)add[rt] * len; }
	
	void Build( int &rt , int l , int r ){
		rt = ++Cnt;
		if( l == r )return sum[rt] = A[l] , void();
		int mid = l + r >> 1;
		Build( Lson );Build( Rson );
		Up( rt , r - l + 1 );
	}
	
	void modify( int pt , int &rt , int l , int r , int L , int R , LL val ){
		if( l > R || r < L )return;
		rt = ++Cnt;Ch[rt][0] = Ch[pt][0];Ch[rt][1] = Ch[pt][1];
		sum[rt] = sum[pt];add[rt] = add[pt];
		if( l >= L && r <= R )return add[rt] += val , sum[rt] += (LL)( r - l + 1 ) * val , void();
		int mid = l + r >> 1;
		modify( Ch[pt][0] , Lson , L , R , val );modify( Ch[pt][1] , Rson , L , R , val );
		Up( rt , r - l + 1 );
	}
	
	LL Query( int rt , int l , int r , int L , int R ){
		if( l > R || r < L || !rt )return 0;
		if( l >= L && r <= R )return sum[rt];
		int mid = l + r >> 1;
		return Query( Lson , L , R ) + Query( Rson , L , R ) + ( min( R , r ) - max( L , l ) + 1 ) * add[rt];
	}
	
}using namespace president_tree;

int main(){
	
	while( scanf("%d%d",&n,&m) != EOF ){
		memset( Ch , 0 , sizeof Ch );
		memset( add , 0 , sizeof add );
		memset( sum , 0 , sizeof sum );
		Cnt = 0;
		For( i , 1 , n )Read( A[i] );
		int pos = 0;
		Build( root[0] , 1 , n );
		while( m-- ){
			char opt = getchar();
			int x , y , z;
			while( opt != 'C' && opt != 'Q' && opt != 'H' && opt != 'B' )opt = getchar();
			if( opt == 'C' )pos++ , Read( x ) , Read( y ) , Read( z ) , modify( root[pos - 1] , root[pos] , 1 , n , x , y , z );
			else if( opt == 'Q' )Read( x ) , Read( y ) , printf("%lld\n",Query( root[pos] , 1 , n , x , y ));
			else if( opt == 'H' )Read( x ) , Read( y ) , Read( z ) , printf("%lld\n",Query( root[z] , 1 , n , x , y ));
			else Read( pos );
		}
	}
	
	return 0;
}
